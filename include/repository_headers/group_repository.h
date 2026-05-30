#pragma once

#include "models.h"
#include <vector>

void SaveGrouop(Group group);
std::vector<Group> GetGroups();
void EditGroup(unsigned short group_id);
void DeleteGroup(unsigned short group_id);
