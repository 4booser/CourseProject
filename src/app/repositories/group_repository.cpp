#include "include/repository_headers/group_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;

void SaveGroup(const Group& group){
    json data = {
        {"Id", group.Id},
        {"Name", group.Name},
        {"Course", group.Course},
        {"Speciality", group.Speciality}
    }
    std::ofstream file("Groups.json");

    if (!file.is_open())
    {
        return;
    }
    file << data.dump(2);
}

