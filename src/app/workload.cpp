#include "repositories/workload_repository.h"
#include "headers/workload.h"
#include "models.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <optional>

static std::vector<unsigned short> ReadIdsFromLine()
{
    std::vector<unsigned short> ids;
    std::string line;

    std::getline(std::cin, line);

    std::istringstream stream(line);
    unsigned short id;

    while (stream >> id)
    {
        ids.push_back(id);
    }

    return ids;
}

static void ReadWorkloadFields(models::Workload& workload)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Teacher IDs: ";
    workload.teacher_ids = ReadIdsFromLine();

    std::cout << "Group IDs: ";
    workload.group_ids = ReadIdsFromLine();

    std::cout << "Discipline ID: ";
    std::cin >> workload.subject_id;

    std::cout << "Lectures: ";
    std::cin >> workload.lectures;

    std::cout << "Practical classes: ";
    std::cin >> workload.practical_classes;

    std::cout << "Laboratory classes: ";
    std::cin >> workload.laboratory_classes;

    std::cout << "Seminars: ";
    std::cin >> workload.seminars;

    std::cout << "Consultations: ";
    std::cin >> workload.consultations;

    workload.total_hours =
        workload.lectures +
        workload.practical_classes +
        workload.laboratory_classes +
        workload.seminars +
        workload.consultations;
}

void HandleWorkloadCreate()
{
    models::Workload workload{};

    ReadWorkloadFields(workload);

    if (!SaveWorkload(workload))
    {
        std::cout << "Save error.\n";
        return;
    }

    std::cout << "Workload saved.\n";
}

void HandleWorkloadsGet()
{
    std::vector<models::Workload> workloads = GetWorkloads();

    std::cout << std::endl;
    std::cout << std::left
        << std::setw(5)  << "ID"
        << std::setw(15) << "Teachers"
        << std::setw(15) << "Groups"
        << std::setw(12) << "Disc ID"
        << std::setw(10) << "Lect"
        << std::setw(10) << "Pract"
        << std::setw(10) << "Lab"
        << std::setw(10) << "Sem"
        << std::setw(10) << "Cons"
        << std::setw(10) << "Total"
        << std::endl;

    std::cout << std::string(107, '-') << std::endl;

    for (const models::Workload& workload : workloads)
    {
        std::cout << std::left << std::setw(5) << workload.id;

        std::ostringstream teachers_stream;
        for (std::size_t i = 0; i < workload.teacher_ids.size(); ++i)
        {
            teachers_stream << workload.teacher_ids[i];
            if (i + 1 < workload.teacher_ids.size())
            {
                teachers_stream << ",";
            }
        }

        std::ostringstream groups_stream;
        for (std::size_t i = 0; i < workload.group_ids.size(); ++i)
        {
            groups_stream << workload.group_ids[i];
            if (i + 1 < workload.group_ids.size())
            {
                groups_stream << ",";
            }
        }

        std::cout
            << std::setw(15) << teachers_stream.str()
            << std::setw(15) << groups_stream.str()
            << std::setw(12) << workload.subject_id
            << std::setw(10) << workload.lectures
            << std::setw(10) << workload.practical_classes
            << std::setw(10) << workload.laboratory_classes
            << std::setw(10) << workload.seminars
            << std::setw(10) << workload.consultations
            << std::setw(10) << workload.total_hours
            << std::endl;
    }
}

void HandleWorkloadEdit(const unsigned short& id)
{
    std::optional<models::Workload> existing_workload = GetWorkloadById(id);

    if (!existing_workload.has_value())
    {
        std::cout << "Workload not found.\n";
        return;
    }

    models::Workload updated_workload{};
    ReadWorkloadFields(updated_workload);

    if (!EditWorkloadById(id, updated_workload))
    {
        std::cout << "Edit error.\n";
        return;
    }

    std::cout << "Workload updated.\n";
}

void HandleWorkloadDelete(const unsigned short& id)
{
    if (!RemoveWorkloadById(id))
    {
        std::cout << "Workload not found.\n";
        return;
    }

    std::cout << "Workload removed.\n";
}
