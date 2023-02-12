#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

void menu() {
	cout << endl << "Functions: " << endl;
	cout << "1. Create process" << endl << "2. Terminate process" << endl
		<< "3. Print processes" << endl << "0. Exit" << endl;
}

void printProcesses(vector<PROCESS_INFORMATION> processes) {
	cout << endl << "ID ProcessID ThreadID" << endl;
	for (int i = 0; i < processes.size(); ++i) {
		cout << i << ". " << processes[i].dwProcessId << setw(5) << " " << processes[i].dwThreadId << endl;
	}
}

void addProcess(vector<PROCESS_INFORMATION>& processes) {
	STARTUPINFO startup = { sizeof(STARTUPINFO) };
	startup.dwFlags = STARTF_USESTDHANDLES;
	startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	startup.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	PROCESS_INFORMATION process;

	SECURITY_ATTRIBUTES securityAttributes;
	securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	securityAttributes.bInheritHandle = TRUE;
	securityAttributes.lpSecurityDescriptor = NULL;
	PROCESS_INFORMATION tempProcess;
	if (CreateProcess(L"c:\\windows\\notepad.exe", NULL, &securityAttributes, NULL, TRUE, 0, 0, 0, &startup, &tempProcess)) cout << "Success!" << endl;
	else cout << "Fail!" << endl;
	processes.push_back(tempProcess);
}

void terminateProcess(vector<PROCESS_INFORMATION> &processes, int idx) {
	TerminateProcess(processes[idx].hProcess, 1);
	processes.erase(processes.begin() + idx);
}

int main() {

	vector<PROCESS_INFORMATION> processes;

	int userChoice;

	do {
		menu();
		cin >> userChoice;

		switch (userChoice) {
		case 1:
			addProcess(processes);
			break;
		case 2:
			int idx;
			cout << "Enter index for terminate: ";
			cin >> idx;
			terminateProcess(processes, idx);
			break;
		case 3:
			printProcesses(processes);
			break;
		}

	} while (userChoice != 0);
}