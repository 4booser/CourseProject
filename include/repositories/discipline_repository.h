#pragma once

#include "models.h"
#include <vector>

void SaveDiscipline(const Discipline& discipline);
std::vector<Discipline> GetDisciplines();
void EditDiscipline(unsigned short discipline_id);
void DeleteDiscipline(unsigned short discipline_id)

