#include <stdio.h>
#include <Windows.h>

#include <iostream>
using namespace std;

int main() {
    HMODULE hLib = LoadLibrary(L"MyDLL.dll");

    if (!hLib)
        return -1;

    HOOKPROC hHookProc = (HOOKPROC)GetProcAddress(hLib, "keyboardProc");

    if (!hHookProc)
        return -1;

    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD, hHookProc, hLib, 0);

    if (!hHook)
        return -1;
    
    printf("Program successfully hooked.\nPress enter to unhook the function and stop the program.\n");
    system("pause");
    
    UnhookWindowsHookEx(hHook);
    FreeLibrary(hLib);
    return 0;
}