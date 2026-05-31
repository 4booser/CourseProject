# CourseProject

Console C++ application for managing educational workload distribution.

## Features

- Teachers CRUD
- Groups CRUD
- Disciplines CRUD
- Workloads CRUD
- JSON file storage in `Output/`
- CMake build configuration

## Requirements

- C++20 compiler
- CMake 3.20+
- nlohmann/json

On Arch Linux:

```bash
sudo pacman -S cmake gcc nlohmann-json
```

On Ubuntu:

```bash
sudo apt-get install cmake g++ nlohmann-json3-dev
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/course_project
```

## Runtime data

The application creates JSON files in the `Output/` directory:

- `Teachers.json`
- `Groups.json`
- `Disciplines.json`
- `Workloads.json`

`Output/` is ignored by Git because it contains local runtime data.
