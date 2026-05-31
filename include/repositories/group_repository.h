#pragma once

#include "models.h"
#include <vector>
#include <optional>

unsigned short GetLastGroupId();

bool SaveGroup(models::Group& group);
std::vector<models::Group> GetGroups();
std::optional<models::Group> GetGroupById(unsigned short id);
bool EditGroupById(const unsigned short& id, const models::Group& updated_group);
bool DeleteGroupById(const unsigned short& id);
