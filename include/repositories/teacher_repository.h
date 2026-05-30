#pragma once

#include "models.h"
#include <vector>

void SaveTeacher(const models::Teacher& teacher);
std::vector<models::Teacher> GetTeachers();
void EditTeacher(unsigned short teacher_id);
void DeleteTeacher(unsigned short teacher_id);
