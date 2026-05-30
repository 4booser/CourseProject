#pragma once

#include "models.h"
#include <vector>

void SaveWorkload(const Workload& workload);
std::vector<Workload> GetWorkloads();
void EditWorkload(unsigned short workload_id);
void DeleteWorkload(unsigned short workload_id);
