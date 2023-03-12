#include <Windows.h>
#include <iostream>
#include <string>

#define MAX_COUNT 10

using namespace std;

HANDLE createMutexWithNumber(int number) {
	HANDLE mutex;
	DWORD result;
	wstring name = to_wstring(number);
	mutex = CreateMutex(NULL, FALSE, name.c_str());
	result = WaitForSingleObject(mutex, 0);
	if (result == WAIT_OBJECT_0) {
		return mutex;
	}
	else {
		return NULL;
	}
}


int main() {
	HANDLE mutex;
	int instanceNumber = 0;

	do {
		mutex = createMutexWithNumber(instanceNumber);
		if (instanceNumber == MAX_COUNT) {
			cout << "Error! Number out of range" << endl;
			system("pause");
			exit(0);
		}
		instanceNumber++;
		
	} while (!mutex);

	cout << "Instance number: " << instanceNumber << endl;

	while (true) {
		int choice;
		cout << "Enter 1 to show count" << endl;
		cout << "Enter 0 to exit" << endl;
		cin >> choice;
		if (choice == 0) {
			ReleaseMutex(mutex);
			break;
		}
		else {

			int count = 1;

			for (int i = 0; i < MAX_COUNT; ++i) {
				HANDLE tempMutex;
				tempMutex = createMutexWithNumber(i);
				if (!tempMutex) count++;
				ReleaseMutex(tempMutex);
			}

			cout << "Count of instance: " << count << endl;
		}
	}
}