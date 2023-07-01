#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
using namespace std;

DWORD_PTR GetProcessBaseAddress(uint32_t processId)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    MODULEENTRY32 moduleEntry = { sizeof(MODULEENTRY32) };
    BOOL success = Module32First(hSnapshot, &moduleEntry);
    if (!success)
    {
        CloseHandle(hSnapshot);
        return 0;
    }

    CloseHandle(hSnapshot);
    return (DWORD_PTR)moduleEntry.modBaseAddr;
}

uint64_t GetImageSize(uint32_t processId, DWORD_PTR Base) {
    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, processId);
    char buffer[0x400];
    uint64_t read;
    if (!ReadProcessMemory(hProc,(void*)Base, buffer, 0x400, &read)) 
        return 0;
    auto nt = (PIMAGE_NT_HEADERS)(buffer + ((PIMAGE_DOS_HEADER)buffer)->e_lfanew);
    CloseHandle(hProc);
    return nt->OptionalHeader.SizeOfImage;
}
