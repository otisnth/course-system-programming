#include <windows.h>
#include <iostream>
#include "../MyDll/lr3lib.h"

using namespace std;

typedef void (WINAPI* cfunc)();

void PrepareStatic()
{
#pragma comment(lib, "MyDLL.lib")
}

cfunc dynamic—opyFile;

int main()
{
    HINSTANCE hLib = LoadLibrary(L"MyDLL.DLL");
    if (hLib == NULL)
    {
        cout << "Unable to load library!" << endl;
        system("pause");
        return 0;
    }

    
    dynamic—opyFile = (cfunc)GetProcAddress((HMODULE)hLib, "copyFile");
    if (dynamic—opyFile == NULL)
    {
        cout << "Unable to load function." << endl;
        FreeLibrary((HMODULE)hLib);
        return 0;
    }
    dynamic—opyFile();
    FreeLibrary((HMODULE)hLib);
    system("pause");

    PrepareStatic();
    copyFile();
    system("pause");

    return 0;
}

