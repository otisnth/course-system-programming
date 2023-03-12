#include "lr3lib.h"
#include "pch.h"

#include <iostream>
#include <windows.h>

using namespace std;

DWORD WINAPI asyncfilecopy(void* data) {
    string filenameInput, filenameOutput;

    cout << "Enter name of input file: ";
    cin >> filenameInput;
    cout << "Enter name of output file: ";
    cin >> filenameOutput;

    HANDLE inputFile, outputFile, event;
    DWORD bytesRead = 0;
    int filesize;
    char buffer[1];

    event = CreateEvent(NULL, TRUE, FALSE, NULL);

    OVERLAPPED ov;
    ZeroMemory(&ov, sizeof(OVERLAPPED));
    ov.Offset = 0;
    ov.OffsetHigh = 0;
    ov.hEvent = event;

    inputFile = CreateFileA(filenameInput.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    outputFile = CreateFileA(filenameOutput.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);

    filesize = GetFileSize(inputFile, NULL);

    for (int i = 0; i < filesize; ++i) {
        ReadFile(inputFile, &buffer, sizeof(buffer), &bytesRead, &ov);
        WriteFile(outputFile, &buffer, sizeof(buffer), &bytesRead, &ov);
        ov.Offset++;

    }

    CloseHandle(inputFile);
    CloseHandle(outputFile);
    return 0;

}

extern "C" __declspec(dllexport) void copyFile()
{
   HANDLE thread;
   thread = CreateThread(NULL, 0, asyncfilecopy, NULL, NULL, NULL);
   WaitForSingleObject(thread, INFINITE);
}