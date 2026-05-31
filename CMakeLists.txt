cmake_minimum_required(VERSION 3.20)

project(CourseProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(course_project
    src/main.cpp
    src/ui.cpp
    src/ui/input.cpp
    src/ui/menu_handlers.cpp
    src/ui/search.cpp
    src/app/teacher.cpp
    src/app/group.cpp
    src/app/discipline.cpp
    src/app/workload.cpp
    src/app/repositories/teacher_repository.cpp
    src/app/repositories/group_repository.cpp
    src/app/repositories/discipline_repository.cpp
    src/app/repositories/workload_repository.cpp
    src/services/workload_service.cpp
    src/storage/json_storage.cpp
)

target_include_directories(course_project PRIVATE
    include
)

target_compile_options(course_project PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
