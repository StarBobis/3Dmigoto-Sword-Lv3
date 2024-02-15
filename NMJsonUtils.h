#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

#include "json.hpp"


nlohmann::json readJsonFromFile(const std::wstring&);

void saveToJson(std::wstring, nlohmann::json);