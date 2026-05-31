#pragma once

#include "common/operation_result.h"
#include "models.h"
#include <vector>
#include <optional>

unsigned short GetLastGroupId();

OperationResult SaveGroup(models::Group& group);
std::vector<models::Group> GetGroups();
std::optional<models::Group> GetGroupById(unsigned short id);
OperationResult EditGroupById(const unsigned short& id, const models::Group& updated_group);
OperationResult DeleteGroupById(const unsigned short& id);
