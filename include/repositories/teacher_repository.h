#pragma once

#include "common/operation_result.h"
#include "models.h"
#include <vector>
#include <optional>

unsigned short GetLastTeacherId();

OperationResult SaveTeacher(models::Teacher& teacher);
std::optional<models::Teacher> GetTeacherById(unsigned short id);
OperationResult EditTeacherById(const unsigned short& id, const models::Teacher& updated_teacher);
OperationResult DeleteTeacherById(const unsigned short& id);
