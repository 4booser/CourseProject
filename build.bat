@echo off
chcp 65001 > nul

echo Building CourseProject...

g++ -std=c++20 -Wall -Wextra -Wpedantic -Iinclude ^
    src/main.cpp ^
    src/ui.cpp ^
    src/app/teacher.cpp ^
    src/app/group.cpp ^
    src/app/discipline.cpp ^
    src/app/workload.cpp ^
    src/app/repositories/teacher_repository.cpp ^
    src/app/repositories/group_repository.cpp ^
    src/app/repositories/discipline_repository.cpp ^
    src/app/repositories/workload_repository.cpp ^
    -static -static-libgcc -static-libstdc++ ^
    -o app.exe

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