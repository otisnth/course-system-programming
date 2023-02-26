#include <iostream>
#include "Windows.h"

using namespace std;


int main() {

	string filenameInput, filenameOutput;

	cout << "Enter name of input file: ";
	cin >> filenameInput;
	cout << "Enter name of output file: ";
	cin >> filenameOutput;

	HANDLE inputFile, outputFile, event;
	DWORD bytesRead;
	LPVOID buffer = 0;

	event = CreateEvent(NULL, FALSE, FALSE, L"event");

	OVERLAPPED ov;
	ov.Offset = 0;
	ov.OffsetHigh = 0;
	ov.hEvent = event;

	inputFile = CreateFileA(filenameInput.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	outputFile = CreateFileA(filenameOutput.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

	while (ReadFile(inputFile, &buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead != 0) {
		//WaitForSingleObject(event, INFINITE);
		WriteFile(outputFile, &buffer, sizeof(buffer), &bytesRead, NULL);
		
	}

}