#pragma once

#include "models.h"
#include <vector>

void SaveGrouop(const models::Group& group);
std::vector<models::Group> GetGroups();
void EditGroup(unsigned short group_id);
void DeleteGroup(unsigned short group_id);
