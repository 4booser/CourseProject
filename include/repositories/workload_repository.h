#pragma once

#include "models.h"
#include <vector>
#include <optional>

unsigned short GetLastWorkloadId();

bool SaveWorkload(models::Workload& workload);
std::vector<models::Workload> GetWorkloads();
std::optional<models::Workload> GetWorkloadById(unsigned short id);
bool EditWorkloadById(const unsigned short& id, const models::Workload& updated_workload);
bool RemoveWorkloadById(const unsigned short& id);
