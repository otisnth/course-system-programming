#include <windows.h>
#include "keyboard.h"
#include "pch.h"

#include <vector>
#include <iostream>
using namespace std;

vector<int> codes;

template<typename T>
void pop_front(std::vector<T>& v)
{
    if (v.size() > 0) {
        v.erase(v.begin());
    }
}

extern "C" __declspec(dllexport) LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode < 0)
        return CallNextHookEx(0, nCode, wParam, lParam);

    DWORD IsDown, checkUp;
    IsDown = !(lParam >> 31);
    checkUp = !(lParam >> 30);

    if (IsDown && nCode == HC_ACTION && checkUp) {
        MessageBeep(-1);
        codes.push_back(wParam);

        if (codes.size() >= 3) {
            if ((codes[0] == 0x43) && (codes[1] == 0x47) && (codes[2] == 0x4A)) {
                pop_front(codes);
                MessageBoxW(NULL, L"Пользователь ввел СПО", L"Alert!", MB_OK);
            }
            else {
                pop_front(codes);
            }

        }

    } 

    return CallNextHookEx(0, nCode, wParam, lParam);
}
