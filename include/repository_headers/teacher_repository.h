#pragma once

#include "models.h"
#include <vector>

void SaveTeacher(Teacher teacher);
std::vector<Teacher> GetTeachers();
void EditTeacher(unsigned short teacher_id);
void DeleteTeacher(unsigned short teacher_id);
