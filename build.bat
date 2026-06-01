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

echo Compiler was not found.
echo.
echo Install one of these options:
echo 1. MinGW-w64 / MSYS2 and add g++ to PATH
echo 2. Visual Studio Build Tools and run this script from Developer Command Prompt
echo.
echo If you only need to run the project, use prebuilt app.exe instead of build.bat.
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
