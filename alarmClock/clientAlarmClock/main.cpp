#include <Windows.h>
#include <time.h>
#include <iostream>

using namespace std;

void main()
{
    LPCWSTR sMailName = L"\\\\.\\mailslot\\mymail";
    HANDLE hMail = NULL;
 
    DWORD dwBytesWritten = 0;
    int hour, min, sec;
    int period;

    hMail = CreateFile(sMailName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hMail == INVALID_HANDLE_VALUE)
    {
        cout << "Create file failed." << endl;
        system("pause");
        return;
    }

    cout << "Hour: "; 
    cin >> hour;

    cout << "Min: ";
    cin >> min;

    cout << "Sec: ";
    cin >> sec;

    period = sec + min * 60 + hour * 60 * 60;

    if (!WriteFile(hMail, &period, sizeof(period), &dwBytesWritten, NULL))
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