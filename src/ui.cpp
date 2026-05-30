#include <iostream>
#include "ui.h"

using namespace std;

namespace ui{
    void ShowObjects(){
    cout << endl;
    cout << "========== РОЗПОДІЛ УЧБОВОГО НАВАНТАЖЕННЯ ==========" << endl;
    cout << endl;
    cout << "Оберiть об`єкт:" << endl;
    cout << endl;
    cout << "1. викладачi" << endl;
    cout << "2. дисципліни" << endl;
    cout << "3. групи" << endl;
    cout << "4. навантаження" << endl;
    cout << endl;
    cout << "5. Пошук" << endl;
    cout << endl;
    cout << "0. Вихід" << endl;
    cout << "-----------------------------------------------------";
    cout << endl;
    }

    void ShowOptions(){
    cout << endl;
    cout << "-----------------------------------------------------";
    cout << "Оберiть опцiю:" << endl;
    cout << endl;
    cout << "1. Додати" << endl;
    cout << "2. Прочитати " << endl;
    cout << "3. Редагувати" << endl;
    cout << "4. Видалити" << endl;
    cout << endl;
    cout << "0. Повернутися до об`єктiв.";
    cout << "-----------------------------------------------------";
    cout << endl;
    }
}
