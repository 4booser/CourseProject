#pragma once
#include <string>
#include <vector>

namespace models{
    struct Teacher{
    unsigned short id;
    std::string full_name;
    std::string digital_commission;
    unsigned int quota; // in hours
    };

    struct Group{
    unsigned short id;
    std::string name;
    unsigned short course;
    std::string speciality;
    };

    struct Discipline{
    unsigned short id;
    std::string name;
    unsigned int quota; // in hours
    }; 

    struct Workload{
    unsigned short id;
    std::vector<unsigned short> teacher_ids;
    unsigned short subjectId;
    std::vector<unsigned short> group_ids;
    unsigned int lectures;
    unsigned int practical_classes;
    unsigned int laboratory_classes;
    unsigned int seminars;
    unsigned int consultations;
    unsigned int total_hours;
    };
}

