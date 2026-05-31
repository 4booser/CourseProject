# CourseProject

Console C++20 application for managing educational workload distribution.

The project stores data in JSON files and provides CRUD operations for teachers, groups, disciplines and workloads.

## Features

- Teachers CRUD
- Groups CRUD
- Disciplines CRUD
- Workloads CRUD
- Search across teachers, groups, disciplines and workloads
- Table-based console output
- Safe numeric input helpers
- Workload relation validation
- Teacher quota validation
- Discipline hours validation
- JSON file storage in `Output/`
- CMake build configuration

## Architecture

The project is organized by layers:

```text
UI
 ↓
Service
 ↓
Repository
 ↓
Storage
```

### UI

Responsible for console input/output:

```text
src/ui.cpp
src/ui/input.cpp
src/ui/menu_handlers.cpp
src/ui/search.cpp
src/app/*.cpp
```

### Service

Responsible for business rules and validation:

```text
src/services/teacher_service.cpp
src/services/group_service.cpp
src/services/discipline_service.cpp
src/services/workload_service.cpp
```

Examples of service rules:

- teacher full name cannot be empty;
- teacher quota must be greater than 0;
- group course must be in range 1-4;
- discipline hours must be greater than 0;
- workload cannot reference missing teachers, groups or disciplines;
- workload cannot exceed teacher quota;
- workload cannot exceed discipline hours;
- related entities cannot be deleted while they are used by workloads.

### Repository

Responsible for CRUD operations:

```text
src/app/repositories/teacher_repository.cpp
src/app/repositories/group_repository.cpp
src/app/repositories/discipline_repository.cpp
src/app/repositories/workload_repository.cpp
```

Repository mutation methods return `OperationResult`:

```cpp
struct OperationResult
{
    bool success = false;
    std::string message;
};
```

### Storage

Responsible for reading and writing JSON arrays:

```text
src/storage/json_storage.cpp
```

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

```text
Output/Teachers.json
Output/Groups.json
Output/Disciplines.json
Output/Workloads.json
```

`Output/` is ignored by Git because it contains local runtime data.

## JSON format

New records are written in `snake_case`.

### Teacher

```json
{
  "id": 1,
  "full_name": "Іваненко Іван Іванович",
  "digital_commission": "Software",
  "quota": 120
}
```

### Group

```json
{
  "id": 1,
  "name": "ПР-214",
  "course": 2,
  "speciality": "Software Engineering"
}
```

### Discipline

```json
{
  "id": 1,
  "name": "Programming",
  "quota": 120
}
```

### Workload

```json
{
  "id": 1,
  "teacher_ids": [1],
  "group_ids": [1],
  "discipline_id": 1,
  "lectures": 20,
  "practical_classes": 30,
  "laboratory_classes": 20,
  "seminars": 10,
  "consultations": 5,
  "total_hours": 85
}
```

Old local JSON files with PascalCase keys are still readable for backward compatibility.

## Recommended local check

```bash
git pull
cmake -S . -B build
cmake --build build
./build/course_project
```
