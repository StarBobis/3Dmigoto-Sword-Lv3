#include "D3D11ElementAttributeClass.h"
#include "IniParser.h"

#include "NMJsonUtils.h"
#include "NMStringUtils.h"
#include "NMLoggerUtils.h"
#include "NMFileUtils.h"

#include "WheelFunctions.h"
#include "WheelConfigs.h"




std::vector<std::wstring> readAllLinesW(std::wstring filePath) {
    std::wifstream file(filePath); 
    std::vector<std::wstring> lines; 

    if (file.is_open()) { 
        std::wstring line;
        while (std::getline(file, line)) { 
            lines.push_back(line); 
        }
        file.close();
    }
    else {
        std::cout << "Can't open this file!" << std::endl;
    }
    return lines;
}


std::uint32_t CharArrayToUINT32_T(char* data) {
    return (static_cast<unsigned char>(data[3]) << 24) |
        (static_cast<unsigned char>(data[2]) << 16) |
        (static_cast<unsigned char>(data[1]) << 8) |
        static_cast<unsigned char>(data[0]);
}


std::uint16_t CharArrayToUINT16_T(char* data) {
    return (static_cast<unsigned char>(data[1]) << 8) |
        static_cast<unsigned char>(data[0]);
}


void ReverseSingle(std::wstring ApplicationLocation) {
    std::wstring location = ApplicationLocation + L"\\settings\\ReverseSetting.json";
    LogOutput(L"Config location path: " + location);
    json reverseJsonObject = readJsonFromFile(location);

    std::wstring GameName = to_wide_string(reverseJsonObject["GameName"]);
    std::wstring reverseFilePath = to_wide_string(reverseJsonObject["ReverseFilePath"]);

    LogOutput(L"reverseFilePath: " + reverseFilePath);
    LogOutput(L"GameName: " + GameName);

    ReverseModelSingle reverseModel(reverseFilePath);

    LogOutput(L"Parse ini info finished.");
    LogOutputSplitStr();

    reverseModel.parseElementList(GameName);

    reverseModel.reverseAndOutput();

}


void ReverseMerged(std::wstring ApplicationLocation) {
    std::wstring location = ApplicationLocation + L"\\settings\\ReverseSetting.json";
    LogOutput(L"Config location path: " + location);
    json reverseJsonObject = readJsonFromFile(location);

    std::wstring GameName = to_wide_string(reverseJsonObject["GameName"]);
    std::wstring reverseFilePath = to_wide_string(reverseJsonObject["ReverseFilePath"]);

    LogOutput(L"reverseFilePath: " + reverseFilePath);
    LogOutput(L"GameName: " + GameName);

    parseMergedInI(reverseFilePath, GameName);

    LogOutputSplitStr();
}