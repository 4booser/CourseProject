#pragma once
#include <string>
#include <vector>

using namespace models{
    struct Teacher{
    unsigned short Id;
    std::string FullName;
    std::string DigitalCommission;
    unsigned int Quota; // in hours
    };

    struct Group{
    unsigned short Id;
    std::string Name;
    unsigned short Course;
    std::string Speciality;
    };

    struct Discipline{
    unsigned short Id;
    std::string Name;
    unsigned int Quota; // in hours
    }; 

    struct Workload{
    unsigned short Id;
    std::vector<unsigned short> TeacherIds;
    unsigned short SubjectId;
    std::vector<unsigned short> GroupIds;
    unsigned int Lectures;
    unsigned int PracticalClasses;
    unsigned int LaboratoryClasses;
    unsigned int Seminars;
    unsigned int Consultations;
    unsigned int TotalHours;
    };
}

