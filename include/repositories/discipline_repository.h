#pragma once

#include "models.h"
#include <vector>

unsigned short GetLastDisciplineId();

bool SaveDiscipline(models::Discipline& discipline);
std::vector<models::Discipline> GetDisciplines();
bool EditDiscipline(unsigned short& id);
bool DeleteDiscipline(unsigned short& id);

