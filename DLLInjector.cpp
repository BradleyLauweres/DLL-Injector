#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

void Display();

std::string PathToDLL;
int PIDToInject = 0;

DWORD GetProcessId(const char* procName) 
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);
		if (Process32First(hSnap, &procEntry)) {
			do {
				if (! _stricmp((const char*)procEntry.szExeFile, procName)) {

					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}

	CloseHandle(hSnap);
	return procId;
}

int main()
{
	const char* pathTodll = "";

	std::cout << "Running tasklist command to retrieve "
		"list of running processes:"
		<< std::endl;

	int returnValue = system("tasklist");

	if (returnValue != 0) {
		std::cerr << "Error executing tasklist command" << std::endl;
		return 1;
	}

	Display();

	return 0;



}

void Display() {

	std::cout << "Please provide the absolute path to the DLL file" << std::endl;
	std::cin >> PathToDLL;
	std::cout << "Please enter the PID from the procces u want to inject to" << std::endl;
	std::cin >> PIDToInject;

}

