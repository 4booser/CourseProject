#include "repositories/discipline_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;

bool SaveDiscipline(const models::Discipline& discipline){
    json data = {
        {"Id", discipline.id},
        {"Name", discipline.name},
        {"Quota", discipline.quota}
    };
    std::ofstream file("Disciplines.json");

    if (!file.is_open())
    {
        return;
    }
    file << data.dump(2);
}