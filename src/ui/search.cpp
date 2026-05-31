#include "ui/search.h"

#include "repositories/teacher_repository.h"
#include "repositories/group_repository.h"
#include "repositories/discipline_repository.h"
#include "repositories/workload_repository.h"
#include "ui/input.h"
#include "models.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace
{
    std::string ToLower(std::string value)
    {
        std::transform(value.begin(), value.end(), value.begin(), [](unsigned char character){
            return static_cast<char>(std::tolower(character));
        });

        return value;
    }

    bool ContainsIgnoreCase(const std::string& text, const std::string& query)
    {
        return ToLower(text).find(ToLower(query)) != std::string::npos;
    }

    bool NumberMatches(unsigned int number, const std::string& query)
    {
        return std::to_string(number).find(query) != std::string::npos;
    }

    bool NumberListMatches(const std::vector<unsigned short>& numbers, const std::string& query)
    {
        for (unsigned short number : numbers)
        {
            if (NumberMatches(number, query))
            {
                return true;
            }
        }

        return false;
    }

    void SearchTeachers(const std::string& query)
    {
        bool found = false;

        for (unsigned short id = 1; id <= GetLastTeacherId(); ++id)
        {
            std::optional<models::Teacher> teacher = GetTeacherById(id);

            if (!teacher.has_value())
            {
                continue;
            }

            if (ContainsIgnoreCase(teacher->full_name, query) || ContainsIgnoreCase(teacher->digital_commission, query))
            {
                std::cout << "[Teacher] Id: " << teacher->id
                    << ", Name: " << teacher->full_name
                    << ", Commission: " << teacher->digital_commission
                    << ", Quota: " << teacher->quota << '\n';
                found = true;
            }
        }

        if (!found)
        {
            std::cout << "Викладачiв не знайдено.\n";
        }
    }

    void SearchGroups(const std::string& query)
    {
        bool found = false;
        std::vector<models::Group> groups = GetGroups();

        for (const models::Group& group : groups)
        {
            if (ContainsIgnoreCase(group.name, query) || ContainsIgnoreCase(group.speciality, query))
            {
                std::cout << "[Group] Id: " << group.id
                    << ", Name: " << group.name
                    << ", Course: " << group.course
                    << ", Speciality: " << group.speciality << '\n';
                found = true;
            }
        }

        if (!found)
        {
            std::cout << "Груп не знайдено.\n";
        }
    }

    void SearchDisciplines(const std::string& query)
    {
        bool found = false;
        std::vector<models::Discipline> disciplines = GetDisciplines();

        for (const models::Discipline& discipline : disciplines)
        {
            if (ContainsIgnoreCase(discipline.name, query))
            {
                std::cout << "[Discipline] Id: " << discipline.id
                    << ", Name: " << discipline.name
                    << ", Hours: " << discipline.quota << '\n';
                found = true;
            }
        }

        if (!found)
        {
            std::cout << "Дисциплiн не знайдено.\n";
        }
    }

    void SearchWorkloads(const std::string& query)
    {
        bool found = false;
        std::vector<models::Workload> workloads = GetWorkloads();

        for (const models::Workload& workload : workloads)
        {
            bool matches =
                NumberMatches(workload.id, query) ||
                NumberListMatches(workload.teacher_ids, query) ||
                NumberListMatches(workload.group_ids, query) ||
                NumberMatches(workload.discipline_id, query) ||
                NumberMatches(workload.total_hours, query);

            if (!matches)
            {
                continue;
            }

            std::cout << "[Workload] Id: " << workload.id
                << ", DisciplineId: " << workload.discipline_id
                << ", TotalHours: " << workload.total_hours
                << ", Teachers: ";

            for (std::size_t i = 0; i < workload.teacher_ids.size(); ++i)
            {
                std::cout << workload.teacher_ids[i];
                if (i + 1 < workload.teacher_ids.size())
                {
                    std::cout << ',';
                }
            }

            std::cout << ", Groups: ";

            for (std::size_t i = 0; i < workload.group_ids.size(); ++i)
            {
                std::cout << workload.group_ids[i];
                if (i + 1 < workload.group_ids.size())
                {
                    std::cout << ',';
                }
            }

            std::cout << '\n';
            found = true;
        }

        if (!found)
        {
            std::cout << "Навантажень не знайдено.\n";
        }
    }
}

namespace ui
{
    void HandleSearchMenu()
    {
        ClearInputLine();

        std::string query = ReadLine("Введiть текст для пошуку: ");

        if (query.empty())
        {
            std::cout << "Порожнiй пошуковий запит.\n";
            return;
        }

        SearchTeachers(query);
        SearchGroups(query);
        SearchDisciplines(query);
        SearchWorkloads(query);
    }
}
