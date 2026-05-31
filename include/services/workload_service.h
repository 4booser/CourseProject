#pragma once

#include "common/operation_result.h"
#include "models.h"

namespace services
{
    OperationResult ValidateWorkload(const models::Workload& workload, unsigned short excluded_workload_id = 0);
    OperationResult CreateWorkload(models::Workload& workload);
    OperationResult UpdateWorkload(unsigned short workload_id, const models::Workload& workload);
    OperationResult DeleteWorkload(unsigned short workload_id);
}
