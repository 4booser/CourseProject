# Manual Testing Checklist

Use this checklist after building the project.

## Build

```bash
cmake -S . -B build
cmake --build build
./build/course_project
```

## Basic scenario

1. Create a teacher.
2. Create a group.
3. Create a discipline.
4. Create a workload that references the created teacher, group and discipline.
5. Print all teachers, groups, disciplines and workloads.
6. Use search by teacher name, group name, discipline name and numeric ID.

## Validation checks

Try these invalid cases:

1. Teacher full name with spaces only.
2. Group course equal to 0.
3. Group course greater than 4.
4. Discipline hours equal to 0.
5. Workload with a missing teacher ID.
6. Workload with a missing group ID.
7. Workload with a missing discipline ID.
8. Workload with duplicated teacher IDs.
9. Workload with duplicated group IDs.
10. Workload with all hour fields equal to 0.
11. Workload that exceeds teacher quota.
12. Workload that exceeds discipline hours.
13. ID list input like `1 abc 2`.

## Delete checks

1. Try to delete a teacher used by workload.
2. Try to delete a group used by workload.
3. Try to delete a discipline used by workload.
4. Delete workload.
5. Delete teacher, group and discipline after workload deletion.

## Expected result

The application should not crash.
Invalid data should be rejected with a clear message.
Valid data should be saved to JSON files in `Output/`.
