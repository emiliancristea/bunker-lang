@echo off
setlocal enabledelayedexpansion

rem Bunker Bootstrap Compiler Build Script (Windows)
rem Compiles the self-hosted Bunker compiler directly from portable C11 source.
rem Requires GCC (MinGW), Clang, or MSVC (cl.exe).

set "SCRIPT_DIR=%~dp0"
set "OUTPUT=%SCRIPT_DIR%..\bkrc.exe"

echo === Building Bunker Compiler (bkrc) from Bootstrap C Seed ===

where cl >nul 2>nul
if %errorlevel% equ 0 (
    echo Using Microsoft Visual C++ Compiler (cl.exe)
    cl /nologo /O2 /std:c11 /I "%SCRIPT_DIR%." "%SCRIPT_DIR%bkrc-stage1.c" /Fe:"%OUTPUT%"
    goto :done
)

where gcc >nul 2>nul
if %errorlevel% equ 0 (
    echo Using GCC Compiler (MinGW)
    gcc -std=c11 -O2 -I "%SCRIPT_DIR%." "%SCRIPT_DIR%bkrc-stage1.c" -o "%OUTPUT%"
    goto :done
)

where clang >nul 2>nul
if %errorlevel% equ 0 (
    echo Using Clang Compiler
    clang -std=c11 -O2 -I "%SCRIPT_DIR%." "%SCRIPT_DIR%bkrc-stage1.c" -o "%OUTPUT%"
    goto :done
)

echo ERROR: No suitable C compiler found (cl.exe, gcc, or clang).
echo Please install GCC (MinGW-w64) or Visual Studio Build Tools.
exit /b 1

:done
echo === Build Successful! ===
echo Bunker compiler executable created at: %OUTPUT%
exit /b 0
