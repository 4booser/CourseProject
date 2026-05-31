#pragma once

#include "models.h"
#include <vector>

unsigned short GetLastGroupId();

bool SaveGrouop(models::Group& group);
std::vector<models::Group> GetGroups();
bool EditGroup(unsigned short& id);
bool DeleteGroup(unsigned short& id);
