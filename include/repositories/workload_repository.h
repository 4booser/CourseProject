#pragma once

#include "models.h"
#include <vector>

unsigned short GetNextWorkloadId();

void SaveWorkload(const models::Workload& workload);
std::vector<models::Workload> GetWorkloads();
void EditWorkload(unsigned short& id);
void DeleteWorkload(unsigned short& id);
