#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <iostream>
#include <windows.h>

using namespace std;

extern "C" __declspec(dllexport) LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

#endif