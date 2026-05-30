#pragma once

#include "models.h"
#include <vector>

unsigned short GetNextDisciplineId();

bool SaveDiscipline(const models::Discipline& discipline);
std::vector<models::Discipline> GetDisciplines();
bool EditDiscipline(unsigned short& id);
bool DeleteDiscipline(unsigned short& id);

