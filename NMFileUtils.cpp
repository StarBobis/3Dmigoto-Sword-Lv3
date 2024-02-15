#include "NMFileUtils.h"

#include <Windows.h>
#include <filesystem>


bool MoveFileToRecycleBin(const std::wstring& filePath)
{
    if (!std::filesystem::exists(filePath))
    {
        return false;
    }

    SHFILEOPSTRUCT fileOp = { 0 };
    fileOp.wFunc = FO_DELETE;
    fileOp.pFrom = filePath.c_str();
    fileOp.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION;

    int result = SHFileOperation(&fileOp);
    if (result != 0)
    {
        return false;
    }

    return true;
}
