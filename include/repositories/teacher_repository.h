#pragma once

#include "models.h"
#include <vector>

unsigned short GetNextTeacherId();

bool SaveTeacher(const models::Teacher& teacher);
std::vector<models::Teacher> GetTeachers();
bool EditTeacher(unsigned short& id);
bool DeleteTeacher(unsigned short& id);
