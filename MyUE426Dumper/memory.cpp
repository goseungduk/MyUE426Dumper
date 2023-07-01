#include <Windows.h>
#include <winternl.h>
#include <iostream>

uint64_t GetGameBaseAddr(HANDLE hProc, uint32_t pid) {
	PROCESS_BASIC_INFORMATION pbi;
	uint64_t NumberOfBytesRead;
	uint64_t BaseAddr;

	if (NtQueryInformationProcess(hProc, ProcessBasicInformation, &pbi, sizeof(pbi), 0) < 0) {
		return -1;
	}
	
	if (!ReadProcessMemory(hProc, (uint8_t*)pbi.PebBaseAddress + 0x10, &BaseAddr, sizeof(BaseAddr), &NumberOfBytesRead)) {
		return -1;
	}
	return BaseAddr;
}