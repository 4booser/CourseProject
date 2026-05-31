#pragma once

#include "common/operation_result.h"
#include "models.h"

namespace services
{
    OperationResult ValidateWorkload(const models::Workload& workload, unsigned short excluded_workload_id = 0);
}
