#ifndef _LR3LIB_H_
#define _LR3LIB_H_

#include <iostream>
#include <windows.h>

using namespace std;

DWORD WINAPI asyncfilecopy(void* data);

extern "C" __declspec(dllexport) void copyFile();

#endif