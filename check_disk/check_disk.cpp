#include <filesystem>
#include <iostream>
using namespace std;

namespace fs = std::filesystem;

int main() 
{
    setlocale(LC_ALL, "RU");

    auto info = fs::space("/home");

    //cout << "Количество свободного места на диске (available) " << info.available << " bytes" << endl;
    //cout << "Количество свободного места на диске (capacity) " << info.capacity << " bytes" << endl;
    //cout << "Количество свободного места на диске (free) " << info.free << " bytes" << endl;

    int freeGb = info.free / 1073741824.00;

    cout << "Свободное место: " << freeGb << "Gb" << endl;

    
    if (freeGb < 20)
    {
        //приведение числа в строку через класс stringstream
        stringstream strFreeGb;
        strFreeGb << freeGb;
        string stringFreeGb = strFreeGb.str();

        //cout << "На диске осталось менее 400ГБ!" << endl;
        string command = "php /home/bitrix/www/local/check_disk/send_mess.php " + stringFreeGb;

        int send_command = system(command.c_str());
    }
    
}
