@echo off
chcp 65001 > nul
setlocal enabledelayedexpansion

cd /d "%~dp0"

echo Building CourseProject...
echo.

set SOURCES=
for /r src %%f in (*.cpp) do (
    set SOURCES=!SOURCES! "%%f"
)

where g++ > nul 2> nul
if %errorlevel% equ 0 (
    echo Compiler: g++
    g++ -std=c++20 -Wall -Wextra -Wpedantic -Iinclude !SOURCES! ^
        -static -static-libgcc -static-libstdc++ ^
        -o app.exe
    goto check_result
)

where cl > nul 2> nul
if %errorlevel% equ 0 (
    echo Compiler: MSVC cl.exe
    cl /std:c++20 /EHsc /W4 /utf-8 /Iinclude !SOURCES! /Fe:app.exe
    goto check_result
)

set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist "%VSWHERE%" (
    for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
        set "VSINSTALL=%%i"
    )

    if defined VSINSTALL (
        if exist "!VSINSTALL!\Common7\Tools\VsDevCmd.bat" (
            echo Compiler: MSVC cl.exe from Visual Studio
            call "!VSINSTALL!\Common7\Tools\VsDevCmd.bat" -arch=x64 -host_arch=x64 > nul
            cl /std:c++20 /EHsc /W4 /utf-8 /Iinclude !SOURCES! /Fe:app.exe
            goto check_result
        )
    )
)

echo Compiler was not found.
echo.
echo This script can build the project only if a C++ compiler exists on this PC.
echo.
echo For fully automatic launch on Windows, put a prebuilt app.exe next to run.bat.
echo Then the user only needs to run run.bat or app.exe.
echo.
echo To build from source on this PC, install one option:
echo 1. Visual Studio Installer - Desktop development with C++
echo 2. MSYS2 / MinGW-w64 with g++ added to PATH
echo.
pause
exit /b 1

:check_result
if %errorlevel% neq 0 (
    echo.
    echo Build failed.
    pause
    exit /b %errorlevel%
)

echo.
echo Build successful.
echo File created: app.exe
pause
