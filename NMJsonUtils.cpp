#include "NMJsonUtils.h"
#include "NMStringUtils.h"

nlohmann::json readJsonFromFile(const std::wstring& filenamew) {
    std::string filename = to_byte_string(filenamew);

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for reading: " + filename);
    }

    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    std::string content = ss.str();
    nlohmann::json jsonData = nlohmann::json::parse(content);
    return jsonData;
}

void saveToJson(std::wstring jsonOutputPath, nlohmann::json jsonObject) {
    std::ofstream outputJsonFile(jsonOutputPath);
    outputJsonFile << jsonObject.dump(4);
    outputJsonFile.close();
}
