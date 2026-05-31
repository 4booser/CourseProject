#include "ui/search.h"

#include "repositories/teacher_repository.h"
#include "repositories/group_repository.h"
#include "repositories/discipline_repository.h"
#include "repositories/workload_repository.h"
#include "ui/input.h"
#include "ui/table.h"
#include "utils/string_utils.h"
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
        const std::vector<int> widths {5, 25, 20, 10};

        ui::PrintSectionTitle("Викладачi");
        ui::PrintRow(widths, "ID", "Full name", "Commission", "Quota");
        ui::PrintSeparator(60);

        for (unsigned short id = 1; id <= GetLastTeacherId(); ++id)
        {
            std::optional<models::Teacher> teacher = GetTeacherById(id);

            if (!teacher.has_value())
            {
                continue;
            }

            if (ContainsIgnoreCase(teacher->full_name, query) || ContainsIgnoreCase(teacher->digital_commission, query))
            {
                ui::PrintRow(widths, teacher->id, teacher->full_name, teacher->digital_commission, teacher->quota);
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
        const std::vector<int> widths {5, 15, 10, 25};

        ui::PrintSectionTitle("Групи");
        ui::PrintRow(widths, "ID", "Name", "Course", "Speciality");
        ui::PrintSeparator(55);

        for (const models::Group& group : groups)
        {
            if (ContainsIgnoreCase(group.name, query) || ContainsIgnoreCase(group.speciality, query))
            {
                ui::PrintRow(widths, group.id, group.name, group.course, group.speciality);
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
        const std::vector<int> widths {5, 30, 10};

        ui::PrintSectionTitle("Дисциплiни");
        ui::PrintRow(widths, "ID", "Name", "Hours");
        ui::PrintSeparator(45);

        for (const models::Discipline& discipline : disciplines)
        {
            if (ContainsIgnoreCase(discipline.name, query))
            {
                ui::PrintRow(widths, discipline.id, discipline.name, discipline.quota);
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
        const std::vector<int> widths {5, 15, 15, 12, 10};

        ui::PrintSectionTitle("Навантаження");
        ui::PrintRow(widths, "ID", "Teachers", "Groups", "Disc ID", "Total");
        ui::PrintSeparator(57);

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

            ui::PrintRow(widths,
                workload.id,
                utils::JoinIds(workload.teacher_ids),
                utils::JoinIds(workload.group_ids),
                workload.discipline_id,
                workload.total_hours);
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
