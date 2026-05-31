#pragma once

#include "common/operation_result.h"
#include "models.h"

namespace services
{
    OperationResult ValidateGroup(const models::Group& group);
    OperationResult CanDeleteGroup(unsigned short group_id);
}
