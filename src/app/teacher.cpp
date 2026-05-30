#include "repositories/teacher_repository.h"
#include "headers/teacher.h"
#include "models.h"

using namespace std;

void Hadnle(){
    models::Teacher teacher;
    
    cout << endl << "Введiть ПIБ: "; 
    cin << teacher.FullName;
    cout << endl << "Введiть цифрову комiссiю: "
    cin >> teacher.DigitalCommission;
    cout << endl << "Введiть максимальну кiлькiсть годин: "
    cin >> teacher.Quota;
    
    SaveTeacher(teacher);
}