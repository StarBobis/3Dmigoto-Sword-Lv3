#include "WheelFunctions.h"
#include "WheelConfigs.h"
#include <io.h>
#include <fcntl.h>
#include "NMStringUtils.h"
#include "NMLoggerUtils.h"
#include "IniParser.h"



INITIALIZE_EASYLOGGINGPP

std::int32_t wmain(std::int32_t argc, wchar_t* argv[])
{
    boost::posix_time::ptime currentTime = boost::posix_time::second_clock::local_time();
    std::string logFileName = "logs\\" + boost::posix_time::to_iso_string(currentTime) + ".log";

    el::Configurations logConfigurations;
    logConfigurations.setToDefault();
    logConfigurations.set(el::Level::Global, el::ConfigurationType::ToStandardOutput, "false");
    logConfigurations.set(el::Level::Global, el::ConfigurationType::ToFile, "true");
    logConfigurations.set(el::Level::Global, el::ConfigurationType::Filename, logFileName);
    el::Loggers::reconfigureAllLoggers(logConfigurations);

    setlocale(LC_ALL, "Chinese-simplified");

    std::wstring name = argv[0];
    LogOutput(L"Running : " + name);

#ifdef _DEBUG
    std::wstring applicationLocation = getFolderPathFromFilePath(argv[0]);
    parseMergedInI(L"C:\\Users\\Administrator\\Desktop\\ModExtract\\yinlangkafuka\\merged.ini", L"HSR");
#else

    if (argc < 2) {
        LogError(L"Insufficient parameters");
        return 0;
    }
    else {
        std::wstring method = argv[1];
        LogOutput(L"Current running method [" + method + L"]");

        std::wstring fullPath = argv[0];
        std::wstring path = getFolderPathFromFilePath(fullPath);
        LogOutput(L"Application full path:" + fullPath);
        LogOutput(L"Application location:" + path);

        if (method == L"reverse") {
            ReverseSingle(path);
        }
        else if (method == L"reverseMerged") {
            ReverseMerged(path);
        }

    }
#endif

    return 0;
}
