#include "repository_headers/group_repository.h"
#include <nlohmann/json.hpp>
#include <ofstream>
#include "models.h"
#include <vector>

void SaveGrouop(Group group){
    json data = {
        {"Id", group.Id},
        {"Name", group.Name}
        {"Course", group.Course},
        {"Speciality", group.Speciality}
    }
    std::ofstream file("Groups.json");

    if (!file.is_open())
    {
        return;
    }
    data.dump(2);
}

