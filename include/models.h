#pragma once
#include <string>
#include <vector>

namespace models{
    struct Teacher{
        unsigned short id = 0;
        std::string full_name;
        std::string digital_commission;
        unsigned int quota = 0; // in hours
    };

    struct Group{
        unsigned short id = 0;
        std::string name;
        unsigned short course = 0;
        std::string speciality;
    };

    struct Discipline{
        unsigned short id = 0;
        std::string name;
        unsigned int quota = 0; // in hours
    }; 

    struct Workload{
        unsigned short id = 0;
        std::vector<unsigned short> teacher_ids;
        unsigned short discipline_id = 0;
        std::vector<unsigned short> group_ids;
        unsigned int lectures = 0;
        unsigned int practical_classes = 0;
        unsigned int laboratory_classes = 0;
        unsigned int seminars = 0;
        unsigned int consultations = 0;
        unsigned int total_hours = 0;
    };
}
