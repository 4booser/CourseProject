#pragma once

#include "models.h"
#include <vector>
#include <optional>

unsigned short GetLastTeacherId();

bool SaveTeacher(models::Teacher& teacher);
std::optional<models::Teacher> GetTeacherById(unsigned short id);
bool EditTeacher(unsigned short& id);
bool DeleteTeacher(unsigned short& id);
