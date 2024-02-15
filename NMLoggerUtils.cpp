#include "NMLoggerUtils.h"
#include "NMStringUtils.h"

// time
#include <boost/date_time/posix_time/posix_time.hpp>

void LogOutput(std::wstring str) {
    //std::wcout << "[DebugInfo]:" << str << "\n";
    LOG(INFO) << to_byte_string(str);
}

void LogWarning(std::wstring str) {
    std::wcout << L"[Warning]:" << str << "\n";
}

void LogError(std::wstring str) {
    std::wcout << L"[Error]:" << str << "\n";
    exit(1);
}

void LogOutputSplitStr() {
    LogOutput(L"--------------------------------------------------------------------");
}