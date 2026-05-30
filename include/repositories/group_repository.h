#pragma once

#include "models.h"
#include <vector>

unsigned short GetNextGroupId();

bool SaveGrouop(const models::Group& group);
std::vector<models::Group> GetGroups();
bool EditGroup(unsigned short& id);
bool DeleteGroup(unsigned short& id);
