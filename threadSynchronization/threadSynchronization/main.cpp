#include <iostream>
#include "Windows.h"

using namespace std;

DWORD WINAPI summ(void* data) {
	int a, b;
	cout << "Enter a: ";
	cin >> a;
	cout << "Enter b: ";
	cin >> b;
	cout << a << " + " << b << " = " << a + b << endl;
	SetEvent(data);
	return 0;
}

int main() {
	HANDLE thread;
	HANDLE event;

	event = CreateEvent(NULL, FALSE, FALSE, L"Event");

	while (1)
	{

		thread = CreateThread(NULL, 0, summ, event, NULL, NULL);

		WaitForSingleObject(event, INFINITE);
		
	}

	CloseHandle(event);

}
