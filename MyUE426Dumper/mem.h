#pragma once
#include <iostream>

DWORD_PTR GetProcessBaseAddress(uint32_t processId);
uint64_t GetImageSize(uint32_t processId, DWORD_PTR Base);