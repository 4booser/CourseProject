#include "repositories/teacher_repository.h"
#include "headers/teacher.h"
#include "models.h"
#include <iostream>

using namespace std;

void HandleTeacherCreate(){
    models::Teacher teacher;
    
    cout << endl << "Введiть ПIБ: "; 
    std::getline(std::cin, teacher.FullName);
    cout << endl << "Введiть цифрову комiссiю: ";
    std::getline(std::cin, teacher.DigitalCommission);
    cout << endl << "Введiть максимальну кiлькiсть годин: ";
    cin >> teacher.Quota;
    
    SaveTeacher(teacher);
}