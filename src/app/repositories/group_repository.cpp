#include "repositories/group_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;

bool SaveGroup(const models::Group& group){
    json data = {
        {"Id", group.id},
        {"Name", group.name},
        {"Course", group.course},
        {"Speciality", group.speciality}
    };
    std::ofstream file("Groups.json");

    if (!file.is_open()){ return false; }
    file << data.dump(2);
}

