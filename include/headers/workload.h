#pragma once

#include <vector>

static std::vector<unsigned short> ReadIdsFromLine();

void HandleWorkloadCreate();
void HandleWorkloadsGet();
void HandleWorkloadEdit(const unsigned short& id);
void HandleWorkloadDelete(const unsigned short& id);