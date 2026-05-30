#pragma once
#include <string>
#include <vector>

struct Teacher{
    unsigned short Id;
    std::string FullName;
    std::string DigitalCommission;
    int Quota; // in hours
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
    uint Quota; // in hours
}; 

struct Workload{
    unsigned short Id;
    std::vector<unsigned short> TeacherIds;
};