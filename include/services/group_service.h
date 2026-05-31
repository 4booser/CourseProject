#pragma once

#include "common/operation_result.h"
#include "models.h"

namespace services
{
    OperationResult ValidateGroup(const models::Group& group);
    OperationResult CreateGroup(models::Group& group);
    OperationResult UpdateGroup(unsigned short group_id, const models::Group& group);
    OperationResult DeleteGroup(unsigned short group_id);
}
