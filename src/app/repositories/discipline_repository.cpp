#include "include/repository_headers/discipline_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;

void SaveDiscipline(const Discipline& discipline){
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
    file << data.dump(2);
}