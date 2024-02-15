#pragma once
#include <unordered_map>
#include <iostream>
#include "json.hpp"
#include "D3D11ElementAttributeClass.h"
#include <vector>


using json = nlohmann::json;


class WheelConfigs {
public:
	std::wstring ApplicationRunningLocation;

	std::wstring GameName;

	WheelConfigs();
	std::vector<D3D11ElementAttributeClass> d3d11ElementAttributeList;
	std::vector<std::wstring> FrameAnalyseFileNameList;

	std::vector<D3D11ElementAttributeClass> getD3D11ElementAttributeListByGameName(std::wstring);
};





