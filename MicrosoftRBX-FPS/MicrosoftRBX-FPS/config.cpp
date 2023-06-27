#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <conio.h>
#include "Lib/SimpleIni.h"
#include "config.h"

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

std::string convert(wchar_t* lab);
std::string GetKeyText(UCHAR virtualKey);

bool loop;
int newBorder;

std::string configs[] = {
    "Toggle key",
    "Left Border",
    "Right Border",
    "Top Border",
    "Bottom Border",
};

std::string removeSpace(std::string inputString)
{
    std::string outputString;
    for (auto it = inputString.begin(); it != inputString.end(); ) {
        if (*it == ' ') {
            // Erase the space character
            it = inputString.erase(it);
        }
        else {
            // Move to the next character
            ++it;
        }
    }
    return inputString;
}

void changeKeyBind (){}

void configMain() {
    CSimpleIniA ini;
    ini.LoadFile("config.ini");

    const char* section = "Settings";
    int toggleKey = static_cast<int>(ini.GetLongValue(section, "ToggleKey", VK_END));
    std::string toggleKeyName = GetKeyText(toggleKey);

    int leftBorder = static_cast<int>(ini.GetLongValue(section, "LeftBorder", 30));
    int rightBorder = static_cast<int>(ini.GetLongValue(section, "RightBorder", 20));
    int topBorder = static_cast<int>(ini.GetLongValue(section, "TopBorder", 70));
    int bottomBorder = static_cast<int>(ini.GetLongValue(section, "BottomBorder", 20));


    ini.SetLongValue(section, "ToggleKey", toggleKey);
    ini.SetLongValue(section, "LeftBorder", leftBorder);
    ini.SetLongValue(section, "RightBorder", rightBorder);
    ini.SetLongValue(section, "TopBorder", topBorder);
    ini.SetLongValue(section, "BottomBorder", bottomBorder);

    loop = true;
    int change;
    while (loop){
        system("cls");
        for (int i = 0; i < 5; i++)
            std::cout << KYEL << i + 1 << ". " << configs[i] << "\n";
        std::cout << KYEL << "0: Exit\n";
        std::cout << KCYN << "\nInput: ";
        std::cin >> change;
        system("cls");
        // Get ready for janky shit
        switch (change) {
            case 1:
            {
                std::cout << KWHT << "To edit keypresses you will have to edit the file by hand" << std::endl;
                std::cout << KWHT << "I will add support here soonish" << std::endl;

                std::system("pause");
#ifdef keypressconfig
                std::cout << KWHT << "Press any key..." << std::endl;

                int newKey;
                for (int i = 0; i < 256; i++) {
                    // Get the state of the key
                    int keyState = GetKeyState(i);

                    // Check if the key is down
                    if (keyState & 0x8000) {
                        // The key is down
                        newKey = i;
                    }
                }
                ini.SetLongValue(section, "ToggleKey", newKey);
#endif // keypressconfig
                break;
            }

            case 2:
            case 3:
            case 4:
            case 5:
                std::cout << KWHT << "Please enter a new " << configs[change-1] << ": ";
                std::cin >> newBorder;
                ini.SetLongValue(section, removeSpace(configs[change - 1]).c_str(), newBorder);
                break;

            case 0:
                loop = false;
                break;
        }
    }

    ini.SaveFile("config.ini");
    std::cout << KGRN << "It should now be saved in config.ini" << RST;
}