#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <thread>
#include "SimpleIni.h"
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

HWND robloxHWND;
bool isEnabled = false;
int letterbox = 5; // Just how much to move the mouse back by to prevent it from being stuck LUL

// Config values \\

int toggleKey;
std::string toggleKeyName;
int leftBorder;
int rightBorder;
int topBorder;
int bottomBorder;

//                \\

int mode = 1;
const char* modes[] = { "Force Center Lock", "Lock Border", "Right Click Lock" };

std::string convert(wchar_t* lab) {
    std::wstring ws(lab);
    std::string str(ws.begin(), ws.end());
    return str;
}

std::string GetKeyText(UCHAR virtualKey)
{ // "Borrowed" from https://stackoverflow.com/a/38107083
    UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

    CHAR szName[128];
    int result = 0;
    switch (virtualKey)
    {
    case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
    case VK_RCONTROL: case VK_RMENU:
    case VK_LWIN: case VK_RWIN: case VK_APPS:
    case VK_PRIOR: case VK_NEXT:
    case VK_END: case VK_HOME:
    case VK_INSERT: case VK_DELETE:
    case VK_DIVIDE:
    case VK_NUMLOCK:
        scanCode |= KF_EXTENDED;
    default:
        result = GetKeyNameTextA(scanCode << 16, szName, 128);
    }
    if (result == 0)
        throw std::system_error(std::error_code(GetLastError(), std::system_category()),
            "WinAPI Error occured.");
    return szName;
}

bool isRbxActive()
{
    return (GetForegroundWindow() == robloxHWND);
}

std::string getWindowTitle(HWND handle)
{
    if (handle)
    {
        BOOL passObject;
        const int size = 32;

        wchar_t title[size];
        memset(title, 0, size);

        passObject = GetWindowTextW(handle, title, size);

        if (passObject)
        {
            return convert(title);
        }
    }
    return "NULL";
}

void fixCursor(HWND handle)
{
    if (mode == 1)
    { 
        RECT rect = { NULL };
        if (GetWindowRect(robloxHWND, &rect)) {
            int sizeX = (rect.right - rect.left);
            int sizeY = (rect.bottom - rect.top);

            int centerX = (rect.right - rect.left) / 2;
            int centerY = (rect.bottom - rect.top) / 2;

            SetCursorPos(rect.left + centerX, rect.top + centerY);
        }
    }
    else if (mode == 2)
    {
        POINT p;
        if (GetCursorPos(&p))
        {
            if (ScreenToClient(handle, &p))
            {
                RECT rect = { NULL };
                if (GetWindowRect(robloxHWND, &rect)) {
                    int sizeX = (rect.right - rect.left);
                    int sizeY = (rect.bottom - rect.top);

                    int centerX = (rect.right - rect.left) / 2;
                    int centerY = (rect.bottom - rect.top) / 2;

                    POINT realP;
                    if (GetCursorPos(&realP))
                    {
                        if (p.x < 30)
                        {
                            SetCursorPos(rect.left + leftBorder + letterbox, realP.y);
                        }
                        else if (p.x > sizeX - 20)
                        {
                            SetCursorPos(rect.right - rightBorder - letterbox, realP.y);
                        }
                        else if (p.y < 70)
                        {
                            SetCursorPos(realP.x, rect.top + topBorder + letterbox);
                        }
                        else if (p.y > sizeY - 20)
                        {
                            SetCursorPos(realP.x, rect.bottom - bottomBorder - letterbox);
                        }
                    }
                }
            }
        }
    }
    else if (mode == 3)
    {
        POINT p;
        if (GetCursorPos(&p))
        {
            if (ScreenToClient(handle, &p))
            {
                RECT rect = { NULL };
                if (GetWindowRect(robloxHWND, &rect)) {
                    POINT realP;
                    if (GetCursorPos(&realP))
                    {
                        while (GetAsyncKeyState(VK_RBUTTON)) {
                            SetCursorPos(realP.x, realP.y);
                        }
                    }
                }
            }
        }
    }
}

void printStatus()
{
    system("cls");
    std::cout << KBLU;
    std::cout << BOLD("Roblox-HWND: ") << robloxHWND << std::endl;
    std::cout << KRED;
    std::cout << BOLD("Mode: ") << modes[mode - 1] << std::endl;
    std::cout << KYEL;
    std::cout << BOLD("Keybind: ") << toggleKeyName << std::endl;
    std::cout << KCYN;
    std::cout << BOLD("Enabled: ") << (isEnabled ? "Enabled" : "Disabled");
}

void init()
{
    // FindWindow is so fucked because it has none for this so i had to use this method <3
    std::cout << KRED;
    std::cout << "Please open Microsoft Roblox Client and click somewhere.";
    while (true)
    {
        HWND currentHWND = GetForegroundWindow();
        if (currentHWND)
        {
            std::string getTitle = getWindowTitle(currentHWND);
            if (getTitle == "Roblox")
            {
                robloxHWND = currentHWND;
                system("cls");
                std::cout << KMAG;
                std::cout << "Initialized!\nRoblox-Handle: " << currentHWND;
                break;
            }
        }

        Sleep(1000);
    }

    Sleep(1000);
    printStatus();
}

void check()
{
    while (true)
    {
        while (ShowCursor(false) >= 0);
        if (isRbxActive() && isEnabled)
        {
            fixCursor(robloxHWND);
        }
        Sleep(10);
    }
}

void toggle()
{
    while (true)
    {
        if (GetAsyncKeyState(toggleKey))
        {
            isEnabled = not isEnabled;
            printStatus();
            Sleep(1000);
        }
        Sleep(25);
    }
}

int main()
{
    CSimpleIniA ini;
    ini.LoadFile("config.ini");
    const char* section = "Settings";
    toggleKey = static_cast<int>(ini.GetLongValue(section, "ToggleKey", VK_END));
    toggleKeyName = GetKeyText(toggleKey);

    leftBorder = static_cast<int>(ini.GetLongValue(section, "LeftBorder", 30));
    rightBorder = static_cast<int>(ini.GetLongValue(section, "RightBorder", 20));
    topBorder = static_cast<int>(ini.GetLongValue(section, "TopBorder", 70));
    bottomBorder = static_cast<int>(ini.GetLongValue(section, "BottomBorder", 20));

    std::cout << KRED;
    std::cout << BOLD("Please enter one of mode numbers.") << "\n" << std::endl;
    for (int i = 0; i < 3; i++)
        std::cout << KYEL << i+1 << ". " << modes[i] << "\n";
    //std::cout << KYEL << 0 << ". Edit config" << "\n";
    std::cout << KCYN << "\nInput: ";
    std::cin >> mode;

    if (mode == 1 || mode == 2 || mode == 3)
    {
        SetConsoleTitleA("UWPMouseFix");
        std::thread mainThread(init);
        std::thread checkThread(check);
        std::thread toggleThread(toggle);
        mainThread.join();
        checkThread.join();
        toggleThread.join();
        std::cin.get();
    }
    else if (mode == 0) {
        //configMain();
    }
    else {
        std::cout << mode << " is an invalid option, please restart software." << std::endl;
        return 0;
    }
}