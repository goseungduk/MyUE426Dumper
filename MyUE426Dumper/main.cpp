#include<Windows.h>
#include<iostream>
#include "mem.h"
using namespace std;


int main() {
	uint32_t pid = 0;
	HWND hWnd = FindWindowA("UnrealWindow", nullptr);
	GetWindowThreadProcessId(hWnd, (DWORD*)(&pid));
	cout << pid << "\n";
	CloseHandle(hWnd);
	DWORD_PTR baseAddress = GetProcessBaseAddress(pid);
	if (baseAddress) {
		cout << hex << baseAddress << "\n";
	}
	else {
		cout << "false\n";
		return 0;
	}
	uint64_t size = GetImageSize(pid, baseAddress);
	cout << hex << size << "\n";
	void* Image = nullptr;
	Image = VirtualAlloc(0, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	uint64_t read;
	HANDLE ProcessHandle = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pid);
	if (!ReadProcessMemory(ProcessHandle, (void*)baseAddress, Image, size, &read)) {
		return 0;
	}
	cout << hex << Image << "\n";
}

/*
{
	
    DWORD_PTR baseAddress = GetProcessBaseAddress(pid);
	if(baseAddress){
		cout << hex << baseAddress << "\n";
	}
	else {
		cout << "false\n";
		return 0;
	}
	uint64_t size = GetImageSize(pid, baseAddress);
	cout << hex << size << "\n";
	void* Image = nullptr;
	Image = VirtualAlloc(0, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, pid);
	uint64_t read;
	if (!ReadProcessMemory(hProc,(void*)baseAddress, Image, size, &read)) {
		return 0;
	}
	cout << hex << Image << "\n";
}
*/