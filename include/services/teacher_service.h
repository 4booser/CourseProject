#pragma once

#include "common/operation_result.h"
#include "models.h"

namespace services
{
    OperationResult ValidateTeacher(const models::Teacher& teacher);
    OperationResult CreateTeacher(models::Teacher& teacher);
    OperationResult UpdateTeacher(unsigned short teacher_id, const models::Teacher& teacher);
    OperationResult DeleteTeacher(unsigned short teacher_id);
}
