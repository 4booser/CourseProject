#include "repository_headers/discipline_repository.h"
#include <nlohmann/json.hpp>
#include <ofstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;

void SaveDiscipline(int discipline){
    json data = {
        {"Id", discipline.Id},
        {"Name", discipline.Name},
        {"Quota", discipline.Quota}
    };
    std::ofstream file("Disciplines.json");

    if (!file.is_open())
    {
        return;
    }
    data.dump(2);
}