@echo off
setlocal enabledelayedexpansion

rem Bunker Bootstrap Compiler Build Script (Windows)
rem Compiles the self-hosted Bunker compiler directly from portable C11 source.
rem Requires MSVC (cl.exe), GCC (MinGW), or Clang.

set "SCRIPT_DIR=%~dp0"
set "ROOT_DIR=%SCRIPT_DIR%.."
set "OUTPUT=%ROOT_DIR%\bkrc.exe"

echo === Building Bunker Compiler (bkrc) from Bootstrap C Seed ===

rem If cl is not in PATH, try locating Visual Studio environment
where cl >nul 2>nul
if !errorlevel! neq 0 (
    set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
    if exist "!VSWHERE!" (
        for /f "usebackq tokens=*" %%i in (`"!VSWHERE!" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
            set "VSDIR=%%i"
        )
        if exist "!VSDIR!\VC\Auxiliary\Build\vcvars64.bat" (
            echo Initializing MSVC environment via vcvars64.bat...
            call "!VSDIR!\VC\Auxiliary\Build\vcvars64.bat" >nul 2>nul
        )
    )
)

where cl >nul 2>nul
if !errorlevel! equ 0 (
    echo Using Microsoft Visual C++ Compiler (cl.exe)
    cl /nologo /O2 /std:c11 /I "%SCRIPT_DIR%." "%SCRIPT_DIR%bkrc-stage1.c" /Fe:"%OUTPUT%"
    if !errorlevel! neq 0 (
        echo ERROR: cl.exe compilation failed.
        exit /b 1
    )
    goto :done
)

where gcc >nul 2>nul
if !errorlevel! equ 0 (
    echo Using GCC Compiler (MinGW)
    gcc -std=c11 -O2 -I "%SCRIPT_DIR%." "%SCRIPT_DIR%bkrc-stage1.c" -o "%OUTPUT%"
    if !errorlevel! neq 0 (
        echo ERROR: gcc compilation failed.
        exit /b 1
    )
    goto :done
)

where clang >nul 2>nul
if !errorlevel! equ 0 (
    echo Using Clang Compiler
    clang -std=c11 -O2 -I "%SCRIPT_DIR%." "%SCRIPT_DIR%bkrc-stage1.c" -o "%OUTPUT%"
    if !errorlevel! neq 0 (
        echo ERROR: clang compilation failed.
        exit /b 1
    )
    goto :done
)

echo ERROR: No suitable C compiler found (cl.exe, gcc, or clang).
echo Please install Visual Studio Build Tools or GCC (MinGW-w64).
exit /b 1

:done
echo === Build Successful! ===
echo Bunker compiler executable created at: %OUTPUT%
exit /b 0
