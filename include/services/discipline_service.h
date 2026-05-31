#pragma once

#include "common/operation_result.h"
#include "models.h"

namespace services
{
    OperationResult ValidateDiscipline(const models::Discipline& discipline);
    OperationResult CanDeleteDiscipline(unsigned short discipline_id);
}
