#pragma once

#include "common/operation_result.h"
#include "models.h"

namespace services
{
    OperationResult ValidateTeacher(const models::Teacher& teacher);
    OperationResult CanDeleteTeacher(unsigned short teacher_id);
}
