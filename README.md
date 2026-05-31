# CourseProject

Console C++ application for managing educational workload distribution.

## Features

- Teachers CRUD
- Groups CRUD
- Disciplines CRUD
- Workloads CRUD
- Workload relation validation
- JSON file storage in `Output/`
- CMake build configuration
- GitHub Actions CMake build check

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

## Workload rules

A workload can be created or edited only if all related entities exist:

- every teacher ID must exist in `Teachers.json`;
- every group ID must exist in `Groups.json`;
- the discipline ID must exist in `Disciplines.json`.

The workload stores discipline relation as `DisciplineId` in JSON.
Old local files with `SubjectId` are still readable for backward compatibility.
