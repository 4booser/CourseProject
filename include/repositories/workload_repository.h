#pragma once

#include "models.h"
#include <vector>

void SaveWorkload(const models::Workload& workload);
std::vector<models::Workload> GetWorkloads();
void EditWorkload(unsigned short workload_id);
void DeleteWorkload(unsigned short workload_id);
