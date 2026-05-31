#pragma once

#include "common/operation_result.h"
#include "models.h"
#include <vector>
#include <optional>

unsigned short GetLastWorkloadId();

OperationResult SaveWorkload(models::Workload& workload);
std::vector<models::Workload> GetWorkloads();
std::optional<models::Workload> GetWorkloadById(unsigned short id);
OperationResult EditWorkloadById(const unsigned short& id, const models::Workload& updated_workload);
OperationResult RemoveWorkloadById(const unsigned short& id);

bool HasWorkloadForTeacher(unsigned short teacher_id);
bool HasWorkloadForGroup(unsigned short group_id);
bool HasWorkloadForDiscipline(unsigned short discipline_id);
