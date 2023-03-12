#include <Windows.h>
#include <time.h>
#include <iostream>

using namespace std;

typedef struct _MyParam
{
    HANDLE hTimer;
    time_t nTime;
} MyParam;

void CALLBACK OnTimer(LPVOID lpvParam, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
    MyParam* param = (MyParam*)lpvParam;
    WaitForSingleObjectEx(param->hTimer, INFINITE, TRUE);
    if (time(NULL) >= param->nTime)
    {
        cout << "Alarm !!!" << endl;
        MessageBeep(MB_OK);
        CancelWaitableTimer(param->hTimer);
    }
}

void main()
{
    LPCWSTR sMailName = L"\\\\.\\mailslot\\mymail";
    HANDLE hMail = NULL, hTimer = NULL;
    DWORD dwBytesRead = 0, dwNextMessageSize = 0, dwNextMessageCount = 0;
    _int64 qwStartTimer = 10000000;
    MyParam param = { 0 };

    hMail = CreateMailslot(sMailName, sizeof(time_t), MAILSLOT_WAIT_FOREVER, NULL);
    if (hMail == INVALID_HANDLE_VALUE)
    {
        cout << "Create mailslot failed." << endl;
        return;
    }

    hTimer = CreateWaitableTimerW(NULL, FALSE, NULL);
    if (!hTimer)
    {
        cout << "Create timer failed." << endl;
        return;
    }

    cout << "Waiting time setting..." << endl;

    while (!dwNextMessageSize)
    {
        GetMailslotInfo(hMail, 0, &dwNextMessageSize, &dwNextMessageCount, NULL);
        
    }

    ReadFile(hMail, &param.nTime, sizeof(time_t), &dwBytesRead, NULL);
    param.hTimer = hTimer;

    SetWaitableTimer(hTimer, (LARGE_INTEGER*)&param.nTime, 1000, OnTimer, &param, FALSE);
    WaitForSingleObjectEx(hTimer, INFINITE, TRUE);

    system("pause");
    CloseHandle(hMail);
    CloseHandle(hTimer);
}