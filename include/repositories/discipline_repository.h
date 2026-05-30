#pragma once

#include "models.h"
#include <vector>

void SaveDiscipline(const models::Discipline& discipline);
std::vector<models::Discipline> GetDisciplines();
void EditDiscipline(unsigned short discipline_id);
void DeleteDiscipline(unsigned short discipline_id);

