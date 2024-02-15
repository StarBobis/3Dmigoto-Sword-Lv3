#pragma once
#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <Windows.h>
#include "WheelConfigs.h"

#include <clocale>
#include <codecvt> 
#include <chrono>
#include <cmath>
#include <iostream>
#include <filesystem>
#include <map>
#include <unordered_map>

// algorithm
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/algorithm/string.hpp>
// date_time
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/local_time/local_time_io.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

// property_tree
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>



std::vector<std::wstring> readAllLinesW(std::wstring filePath);

std::uint32_t CharArrayToUINT32_T(char* data);
std::uint16_t CharArrayToUINT16_T(char* data);

void ReverseSingle(std::wstring);
void ReverseMerged(std::wstring ApplicationLocation);