#include "ui/search.h"

#include "repositories/teacher_repository.h"
#include "repositories/group_repository.h"
#include "repositories/discipline_repository.h"
#include "repositories/workload_repository.h"
#include "ui/input.h"
#include "models.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
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

    std::string JoinIds(const std::vector<unsigned short>& ids)
    {
        std::ostringstream stream;

        for (std::size_t i = 0; i < ids.size(); ++i)
        {
            stream << ids[i];

            if (i + 1 < ids.size())
            {
                stream << ',';
            }
        }

        return stream.str();
    }

    void PrintSectionHeader(const std::string& title)
    {
        std::cout << "\n=== " << title << " ===\n";
    }

    void SearchTeachers(const std::string& query)
    {
        bool found = false;

        PrintSectionHeader("Викладачi");

        std::cout << std::left
            << std::setw(5)  << "ID"
            << std::setw(25) << "Full name"
            << std::setw(20) << "Commission"
            << std::setw(10) << "Quota"
            << '\n';
        std::cout << std::string(60, '-') << '\n';

        for (unsigned short id = 1; id <= GetLastTeacherId(); ++id)
        {
            std::optional<models::Teacher> teacher = GetTeacherById(id);

            if (!teacher.has_value())
            {
                continue;
            }

            if (ContainsIgnoreCase(teacher->full_name, query) || ContainsIgnoreCase(teacher->digital_commission, query))
            {
                std::cout << std::left
                    << std::setw(5)  << teacher->id
                    << std::setw(25) << teacher->full_name
                    << std::setw(20) << teacher->digital_commission
                    << std::setw(10) << teacher->quota
                    << '\n';
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

        PrintSectionHeader("Групи");

        std::cout << std::left
            << std::setw(5)  << "ID"
            << std::setw(15) << "Name"
            << std::setw(10) << "Course"
            << std::setw(25) << "Speciality"
            << '\n';
        std::cout << std::string(55, '-') << '\n';

        for (const models::Group& group : groups)
        {
            if (ContainsIgnoreCase(group.name, query) || ContainsIgnoreCase(group.speciality, query))
            {
                std::cout << std::left
                    << std::setw(5)  << group.id
                    << std::setw(15) << group.name
                    << std::setw(10) << group.course
                    << std::setw(25) << group.speciality
                    << '\n';
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

        PrintSectionHeader("Дисциплiни");

        std::cout << std::left
            << std::setw(5)  << "ID"
            << std::setw(30) << "Name"
            << std::setw(10) << "Hours"
            << '\n';
        std::cout << std::string(45, '-') << '\n';

        for (const models::Discipline& discipline : disciplines)
        {
            if (ContainsIgnoreCase(discipline.name, query))
            {
                std::cout << std::left
                    << std::setw(5)  << discipline.id
                    << std::setw(30) << discipline.name
                    << std::setw(10) << discipline.quota
                    << '\n';
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

        PrintSectionHeader("Навантаження");

        std::cout << std::left
            << std::setw(5)  << "ID"
            << std::setw(15) << "Teachers"
            << std::setw(15) << "Groups"
            << std::setw(12) << "Disc ID"
            << std::setw(10) << "Total"
            << '\n';
        std::cout << std::string(57, '-') << '\n';

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

            std::cout << std::left
                << std::setw(5)  << workload.id
                << std::setw(15) << JoinIds(workload.teacher_ids)
                << std::setw(15) << JoinIds(workload.group_ids)
                << std::setw(12) << workload.discipline_id
                << std::setw(10) << workload.total_hours
                << '\n';
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
