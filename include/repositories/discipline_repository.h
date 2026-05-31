#pragma once

#include "models.h"
#include <vector>
#include <optional>

unsigned short GetLastDisciplineId();

bool SaveDiscipline(models::Discipline& discipline);
std::vector<models::Discipline> GetDisciplines();
std::optional<models::Discipline> GetDisciplineById(unsigned short id);
bool EditDisciplineById(const unsigned short& id, const models::Discipline& updated_discipline);
