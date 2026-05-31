#pragma once

#include "models.h"
#include <vector>

unsigned short GetNextWorkloadId();

bool SaveWorkload(models::Workload& workload);
std::vector<models::Workload> GetWorkloads();
bool EditWorkload(unsigned short& id);
bool DeleteWorkload(unsigned short& id);
