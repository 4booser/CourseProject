#pragma once

#include "models.h"
#include <vector>
#include <optional>

unsigned short GetLastTeacherId();

bool SaveTeacher(models::Teacher& teacher);
std::optional<models::Teacher> GetTeacherById(unsigned short id);
bool EditTeacherById(const unsigned short& id, const models::Teacher& updated_teacher);
bool DeleteTeacherById(const unsigned short& id);
