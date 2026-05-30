#pragma once
#include "models.h"
#include <vector>

void AddTeacher(Teacher teacher);
std::vector<Teacher> GetTeachers();
void EditTeacher(ushort teacher_id);
void DeleteTeacher(ushort teacher_id);
