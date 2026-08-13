# Bunker Language Test Runner
# Runs all .bkr test files and validates expected behavior

param(
    [switch]$Verbose,
    [switch]$JitOnly
)

if ($env:GITHUB_ACTIONS -ne "true") {
    Write-Error "Local test execution is disabled. Run Bunker builds/tests through GitHub Actions to protect this workstation."
    exit 1
}

$ErrorActionPreference = "Continue"
$bunker = ".\bunker-cli\target\release\bunker-cli.exe"

# Expected results for JIT Kernel tests (main() return values - integers)
$expectedResults = @{
    "01_basic_math" = 42
    "14_kernel_if_branching" = 42
    "15_kernel_defer_return" = 11
    "16_kernel_match_block_expr" = 12
    "19_kernel_match_binding" = 7
    "20_kernel_option_basic" = 15
    "21_kernel_option_if_infer" = 7
    "23_kernel_if_expr_block" = 7
    "24_comptime_factorial" = 120
    "25_comptime_fib" = 55
    "30_comptime_for_loop" = 55
    "31_comptime_loop_break" = 11
    "32_kernel_for_range" = 55
    "33_kernel_loop_break" = 5
    "34_kernel_for_continue" = 25
    "35_kernel_for_break" = 15
    "36_kernel_type_cast" = 46
    "37_kernel_string_concat" = 11
    "38_kernel_while_loop" = 55
    "39_kernel_while_break" = 15
    "40_kernel_bitwise_ops" = 42
    "41_kernel_len_builtin" = 15
    "42_kernel_ternary" = 42
    "43_kernel_modulo" = 42
    "44_kernel_unary_neg" = 42
    "45_kernel_nested_calls" = 42
    "46_kernel_struct_ops" = 42
    "47_kernel_array_ops" = 42
    "48_kernel_control_flow" = 42
    "49_kernel_bool_logic" = 42
    "50_kernel_recursive_gcd" = 42
    "51_kernel_comparisons" = 42
    "52_kernel_option_match" = 42
    "53_kernel_float_ops" = 42
    "54_kernel_i64_ops" = 42
    "55_kernel_const" = 42
    "56_kernel_early_return" = 42
    "57_kernel_multiple_structs" = 42
    "58_move_semantics" = 30
    "60_copy_prevents_move" = 60
    "61_copy_deep_struct" = 42
    "62_copy_deep_array" = 42
    "63_arena_loop_reuse" = 42
    "64_arena_nested_blocks" = 42
    "65_arena_if_branches" = 42
    "72_file_io" = 42
    "73_string_methods" = 42
    "74_vec_operations" = 42
    "75_result_type" = 42
    "76_hashmap_operations" = 42
    "77_typed_vec_operations" = 42
    "79_typed_result_operations" = 42
    "81_typed_hashmap_operations" = 42
    "85_result_handle_roundtrip" = 42
    "88_kernel_unit_enum" = 42
}

# Expected results for non-integer JIT tests (i64, f64, bool)
$expectedStringResults = @{
    "27_kernel_main_i64" = "9223372036854775807"
    "28_kernel_main_f64" = "3.14159"
    "29_kernel_main_bool" = "true"
}

# Shell tests (don't output Result:, just verify they run without error)
# Note: 04_shell_calls_kernel requires explicit args, so it's check-only
$shellTests = @(
    "03_agent_ping_pong",
    "11_shell_calls_kernel_i64",
    "12_kernel_i64_promotion",
    "13_shell_calls_kernel_f64",
    "26_shell_defer",
    "70_shell_arrays_structs",
    "71_shell_loops"
)

$passed = 0
$failed = 0
$skipped = 0

Write-Host "`n=== Bunker Language Test Runner ===" -ForegroundColor Cyan
Write-Host ""

# Get all test files
$testFiles = Get-ChildItem -Path "tests\*.bkr" | Sort-Object Name

foreach ($file in $testFiles) {
    $name = $file.BaseName
    $isBadTest = $name -match "_BAD$"
    $isShellTest = $shellTests -contains $name

    if ($JitOnly -and -not $expectedResults.ContainsKey($name) -and -not $isShellTest) {
        continue
    }

    Write-Host -NoNewline "Testing $name... "

    # Run bunker check
    $checkResult = & $bunker check $file.FullName 2>&1
    $checkExitCode = $LASTEXITCODE

    if ($isBadTest) {
        # BAD tests should FAIL type checking
        if ($checkExitCode -ne 0) {
            Write-Host "PASS" -ForegroundColor Green -NoNewline
            Write-Host " (correctly rejected)"
            $passed++
        } else {
            Write-Host "FAIL" -ForegroundColor Red -NoNewline
            Write-Host " (should have been rejected)"
            $failed++
        }
    } else {
        # Good tests should pass type checking
        if ($checkExitCode -ne 0) {
            Write-Host "FAIL" -ForegroundColor Red -NoNewline
            Write-Host " (check failed)"
            if ($Verbose) {
                Write-Host "  $checkResult" -ForegroundColor DarkGray
            }
            $failed++
        } else {
            # Check passed
            if ($expectedResults.ContainsKey($name)) {
                # Run JIT and verify result
                $runResult = & $bunker run $file.FullName 2>&1 | Out-String
                $runExitCode = $LASTEXITCODE

                # Parse "Result: <number>" from output
                if ($runResult -match 'Result:\s*(-?\d+)') {
                    $actualResult = [int]$matches[1]
                    $expectedResult = $expectedResults[$name]

                    if ($actualResult -eq $expectedResult) {
                        Write-Host "PASS" -ForegroundColor Green -NoNewline
                        Write-Host " (JIT returned $actualResult)"
                        $passed++
                    } else {
                        Write-Host "FAIL" -ForegroundColor Red -NoNewline
                        Write-Host " (expected $expectedResult, got $actualResult)"
                        $failed++
                    }
                } else {
                    Write-Host "FAIL" -ForegroundColor Red -NoNewline
                    Write-Host " (no Result in output)"
                    if ($Verbose) {
                        Write-Host "  Output: $runResult" -ForegroundColor DarkGray
                    }
                    $failed++
                }
            } elseif ($expectedStringResults.ContainsKey($name)) {
                # Run JIT and verify string result (for i64, f64, bool)
                $runResult = & $bunker run $file.FullName 2>&1 | Out-String
                $runExitCode = $LASTEXITCODE

                # Parse "Result: <value>" from output
                if ($runResult -match 'Result:\s*(.+?)\s*$') {
                    $actualResult = $matches[1].Trim()
                    $expectedResult = $expectedStringResults[$name]

                    if ($actualResult -eq $expectedResult) {
                        Write-Host "PASS" -ForegroundColor Green -NoNewline
                        Write-Host " (JIT returned $actualResult)"
                        $passed++
                    } else {
                        Write-Host "FAIL" -ForegroundColor Red -NoNewline
                        Write-Host " (expected $expectedResult, got $actualResult)"
                        $failed++
                    }
                } else {
                    Write-Host "FAIL" -ForegroundColor Red -NoNewline
                    Write-Host " (no Result in output)"
                    if ($Verbose) {
                        Write-Host "  Output: $runResult" -ForegroundColor DarkGray
                    }
                    $failed++
                }
            } elseif ($isShellTest) {
                # Shell test - just verify it runs without crashing
                $runResult = & $bunker run $file.FullName 2>&1 | Out-String
                $runExitCode = $LASTEXITCODE

                if ($runExitCode -eq 0) {
                    Write-Host "PASS" -ForegroundColor Green -NoNewline
                    Write-Host " (shell executed)"
                    $passed++
                } else {
                    Write-Host "FAIL" -ForegroundColor Red -NoNewline
                    Write-Host " (shell failed)"
                    $failed++
                }
            } else {
                Write-Host "PASS" -ForegroundColor Green -NoNewline
                Write-Host " (check only)"
                $passed++
            }
        }
    }
}

if (-not $JitOnly) {
    $selfHostTmp = Join-Path $env:TEMP "bunker-self-host-test"
    New-Item -ItemType Directory -Force -Path $selfHostTmp | Out-Null

    Write-Host -NoNewline "Testing self_host_compile_subset... "
    $selfHostSubset = @(
        "tests\01_basic_math.bkr",
        "tests\14_kernel_if_branching.bkr",
        "tests\16_kernel_match_block_expr.bkr",
        "tests\19_kernel_match_binding.bkr",
        "tests\20_kernel_option_basic.bkr",
        "tests\21_kernel_option_if_infer.bkr",
        "tests\38_kernel_while_loop.bkr",
        "tests\39_kernel_while_break.bkr",
        "tests\52_kernel_option_match.bkr",
        "tests\74_vec_operations.bkr",
        "tests\75_result_type.bkr",
        "tests\76_hashmap_operations.bkr",
        "tests\77_typed_vec_operations.bkr",
        "tests\79_typed_result_operations.bkr",
        "tests\81_typed_hashmap_operations.bkr",
        "tests\85_result_handle_roundtrip.bkr",
        "tests\88_kernel_unit_enum.bkr"
    )

    $subsetOk = $true
    foreach ($subsetFile in $selfHostSubset) {
        $subsetOut = Join-Path $selfHostTmp ([IO.Path]::GetFileNameWithoutExtension($subsetFile) + ".c")
        $compileResult = & $bunker self-host-compile $subsetFile -o $subsetOut 2>&1 | Out-String
        $compileExitCode = $LASTEXITCODE
        if ($compileExitCode -ne 0 -or -not (Test-Path $subsetOut)) {
            Write-Host "FAIL" -ForegroundColor Red -NoNewline
            Write-Host " (self-host compile failed for $subsetFile)"
            if ($Verbose) {
                Write-Host "  $compileResult" -ForegroundColor DarkGray
            }
            $subsetOk = $false
            break
        }

        $generated = Get-Content $subsetOut -Raw
        if ($generated -notlike "*int main(void)*") {
            Write-Host "FAIL" -ForegroundColor Red -NoNewline
            Write-Host " (unexpected generated C for $subsetFile)"
            $subsetOk = $false
            break
        }
    }

    if ($subsetOk) {
        Write-Host "PASS" -ForegroundColor Green -NoNewline
        Write-Host " (self-host compile subset accepted)"
        $passed++
    } else {
        $failed++
    }

    Write-Host -NoNewline "Testing self_host_compile_basic... "
    $selfHostOut = Join-Path $selfHostTmp "basic_math.c"
    $compileResult = & $bunker self-host-compile "tests\01_basic_math.bkr" -o $selfHostOut 2>&1 | Out-String
    $compileExitCode = $LASTEXITCODE

    if ($compileExitCode -eq 0 -and (Test-Path $selfHostOut)) {
        $generated = Get-Content $selfHostOut -Raw
        $hasI32Entry = $generated -match "bkr_i32\s+_v[0-9]+\(void\)"
        $hasMainWrapper = $generated -match "int\s+main\(void\)" -and $generated -match "return\s+\(int\)_v[0-9]+\(\);"
        $hasNoParseError = $generated -notmatch "Parse error at token"
        if ($hasI32Entry -and $hasMainWrapper -and $hasNoParseError) {
            Write-Host "PASS" -ForegroundColor Green -NoNewline
            Write-Host " (Bunker compiler emitted C)"
            $passed++
        } else {
            Write-Host "FAIL" -ForegroundColor Red -NoNewline
            Write-Host " (unexpected generated C)"
            if ($Verbose) {
                Write-Host "  $generated" -ForegroundColor DarkGray
            }
            $failed++
        }
    } else {
        Write-Host "FAIL" -ForegroundColor Red -NoNewline
        Write-Host " (self-host compile failed)"
        if ($Verbose) {
            Write-Host "  $compileResult" -ForegroundColor DarkGray
        }
        $failed++
    }

    if ($selfHostOut) { Remove-Item -Path $selfHostOut -ErrorAction SilentlyContinue }
    if ($selfHostTmp) { Remove-Item -Path $selfHostTmp -ErrorAction SilentlyContinue -Recurse -Force }
}

Write-Host ""
Write-Host "=== Results ===" -ForegroundColor Cyan
Write-Host "Passed: $passed" -ForegroundColor Green
Write-Host "Failed: $failed" -ForegroundColor $(if ($failed -gt 0) { "Red" } else { "Green" })
Write-Host ""

if ($failed -gt 0) {
    exit 1
} else {
    Write-Host "All tests passed!" -ForegroundColor Green
    exit 0
}
