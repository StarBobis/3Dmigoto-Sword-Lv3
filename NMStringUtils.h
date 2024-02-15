#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>

std::wstring getFolderPathFromFilePath(std::wstring filePath);

std::wstring to_wide_string(std::string input);

std::string to_byte_string(std::wstring input);

std::wstring generateUUID();

std::wstring GetFormattedDateTimeForFilename();

std::vector<std::wstring> NMString_splitString(std::wstring,std::wstring);

std::wstring getFileNameFromFilePath(std::wstring filePath);