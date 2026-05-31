#pragma once

#include "common/operation_result.h"
#include "models.h"
#include <vector>
#include <optional>

unsigned short GetLastDisciplineId();

OperationResult SaveDiscipline(models::Discipline& discipline);
std::vector<models::Discipline> GetDisciplines();
std::optional<models::Discipline> GetDisciplineById(unsigned short id);
OperationResult EditDisciplineById(const unsigned short& id, const models::Discipline& updated_discipline);
OperationResult RemoveDisciplineById(const unsigned short& id);
