#include <Windows.h>
#include <time.h>
#include <iostream>

using namespace std;

void main()
{
    LPCWSTR sMailName = L"\\\\.\\mailslot\\mymail";
    HANDLE hMail = NULL;
    time_t t1 = 0;
    struct tm t2 = { 0 };
    DWORD dwBytesWritten = 0;
    int hour, min, sec;

    hMail = CreateFile(sMailName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hMail == INVALID_HANDLE_VALUE)
    {
        cout << "Create file failed." << endl;
        system("pause");
        return;
    }

    t1 = time(NULL);
    localtime_s(&t2, &t1);

    cout << "Hour: "; 
    cin >> hour;

    cout << "Min: ";
    cin >> min;

    cout << "Sec: ";
    cin >> sec;

    t2.tm_hour += hour;
    t2.tm_min += min;
    t2.tm_sec += sec;
    t1 = mktime(&t2);

    if (!WriteFile(hMail, &t1, sizeof(t1), &dwBytesWritten, NULL))
    {
        cout << "Write file failed." << endl;
        CloseHandle(hMail);
        system("pause");
        return;
    }

    CloseHandle(hMail);

    cout << "Write file success." << endl;
    system("pause");
}