#pragma once

#include "common/operation_result.h"
#include "models.h"

namespace services
{
    OperationResult ValidateDiscipline(const models::Discipline& discipline);
    OperationResult CreateDiscipline(models::Discipline& discipline);
    OperationResult UpdateDiscipline(unsigned short discipline_id, const models::Discipline& discipline);
    OperationResult DeleteDiscipline(unsigned short discipline_id);
}
