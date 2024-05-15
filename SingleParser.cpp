#include "IniParser.h"
#include "NMLoggerUtils.h"
#include "NMStringUtils.h"

std::wstring RemoveZhongKuohao(std::wstring inputStr) {
    if (inputStr.size() >= 2 && inputStr.front() == L'[' && inputStr.back() == L']') {
        inputStr = inputStr.substr(1, inputStr.size() - 2);
    }
    return inputStr;
}


std::vector<TextureOverrideIB> parseTextureOverrideIBList(std::vector<std::wstring> lines) {
    std::vector<TextureOverrideIB> TextureOverrideIBList;
    bool matchTextureOverride = false;
    bool matchTextureOverrideIB = false;
    bool matchFirstIndex = false;
    TextureOverrideIB tmpTextureOverrideIB;

    for (std::wstring line : lines) {
        boost::algorithm::trim(line);
        std::wstring lowerLine = boost::algorithm::to_lower_copy(line);

        if (boost::algorithm::starts_with(lowerLine, ";")) {
            continue;
        }

        if (lowerLine.empty()) {
            continue;
        }

        if (boost::algorithm::starts_with(lowerLine, "[textureoverride")) {
            matchTextureOverride = true;
            tmpTextureOverrideIB = TextureOverrideIB();
            tmpTextureOverrideIB.SectionName = RemoveZhongKuohao(lowerLine);
            continue;
        }

        if (matchTextureOverride && boost::algorithm::starts_with(lowerLine, "hash")) {
            KeyValuePair kvp(line);
            std::wstring hashValue = kvp.value;

            tmpTextureOverrideIB.HashValue = hashValue;
            continue;
        }

        if (matchTextureOverride && boost::algorithm::starts_with(lowerLine, "vb")) {
            KeyValuePair kvp(line);
            std::wstring vbSlot = kvp.key;
            std::wstring vbResourceName = kvp.value;

            continue;
        }


        if (matchTextureOverride && boost::algorithm::starts_with(lowerLine, "match_first_index")) {
            KeyValuePair kvp(line);
            std::wstring matchFirstIndex = kvp.value;


            try {
                int num = boost::lexical_cast<int>(matchFirstIndex);
                tmpTextureOverrideIB.MatchFirstIndex = std::stoi(matchFirstIndex);
                matchFirstIndex = true;
            }
            catch (const boost::bad_lexical_cast&) {

                continue;
            }

            continue;

        }

        if (boost::algorithm::starts_with(lowerLine, "ib")) {
            KeyValuePair kvp(line);
            std::wstring ibResourceName = kvp.value;
            tmpTextureOverrideIB.IBResourceName = ibResourceName;

            if (matchFirstIndex) {
                matchFirstIndex = false;
            }
            matchTextureOverride = false;

            if (ibResourceName != L"null" && ibResourceName != L"") {
                TextureOverrideIBList.push_back(tmpTextureOverrideIB);
            }

            continue;

        }
    }

    return TextureOverrideIBList;
}


std::vector<ModResource> parseResourceVBList(std::vector<std::wstring> lines, std::wstring reverseIniFolderPath) {
    std::vector<ModResource> ResourceVBList;

    bool matchResource = false;
    bool matchResourceVB = false;
    bool matchResourceIB = false;

    ModResource tmpResource;

    for (std::wstring line : lines) {
        boost::algorithm::trim(line);
        std::wstring lowerLine = boost::algorithm::to_lower_copy(line);

        if (boost::algorithm::starts_with(lowerLine, ";")) {
            continue;
        }

        if (lowerLine.empty()) {
            continue;
        }

        if (boost::algorithm::starts_with(lowerLine, "[resource")) {
            matchResource = true;
            tmpResource = ModResource();
            tmpResource.SectionName = RemoveZhongKuohao(line);
        }

        if (matchResource && boost::algorithm::starts_with(lowerLine, "stride")) {
            KeyValuePair kvp(line);
            tmpResource.Stride = std::stoi(kvp.value);
            matchResourceVB = true;
        }

        if (matchResource && boost::algorithm::starts_with(lowerLine, "format")) {
            KeyValuePair kvp(line);
            tmpResource.Format = kvp.value;
            matchResourceIB = true;
        }

        if (matchResource && boost::algorithm::starts_with(lowerLine, "filename")) {
            KeyValuePair kvp(line);
            if (boost::algorithm::starts_with(kvp.value, L".")) {
                std::wstring relativePath = kvp.value.substr(1, kvp.value.length() - 1);
                boost::algorithm::replace_all(relativePath, L"/", L"\\");
                kvp.value = reverseIniFolderPath + relativePath;
            }
            else {
                std::wstring relativePath = kvp.value;
                boost::algorithm::replace_all(relativePath, L"/", L"\\");
                kvp.value = reverseIniFolderPath + L"\\" + relativePath;
            }
            tmpResource.FileName = kvp.value;
        }

        if (matchResourceVB && !tmpResource.FileName.empty() && tmpResource.FileName != L"") {
            matchResourceVB = false;
            ResourceVBList.push_back(tmpResource);
        }


    }
    return ResourceVBList;
}


std::vector<ModResource> parseResourceIBList(std::vector<std::wstring> lines,std::wstring reverseIniFolderPath) {
    std::vector<ModResource> ResourceIBList;

    bool matchResource = false;
    bool matchResourceVB = false;
    bool matchResourceIB = false;
    TextureOverrideIB tmpTextureOverrideIB;
    ModResource tmpResource;

    for (std::wstring line : lines) {
        boost::algorithm::trim(line);
        std::wstring lowerLine = boost::algorithm::to_lower_copy(line);

        if (boost::algorithm::starts_with(lowerLine, ";")) {
            continue;
        }

        if (lowerLine.empty()) {
            continue;
        }
        //LogOutput(L"Current line: " + line);

        if (boost::algorithm::starts_with(lowerLine, "[resource")) {
            matchResource = true;
            tmpResource = ModResource();
            tmpResource.SectionName = RemoveZhongKuohao(line);
        }

        if (matchResource && boost::algorithm::starts_with(lowerLine, "stride")) {
            KeyValuePair kvp(line);
            tmpResource.Stride = std::stoi(kvp.value);
            matchResourceVB = true;
        }

        if (matchResource && boost::algorithm::starts_with(lowerLine, "format")) {
            KeyValuePair kvp(line);
            tmpResource.Format = kvp.value;
            matchResourceIB = true;
        }

        if (matchResource && boost::algorithm::starts_with(lowerLine, "filename")) {
            KeyValuePair kvp(line);
            if (boost::algorithm::starts_with(kvp.value, L".")) {
                std::wstring relativePath = kvp.value.substr(1, kvp.value.length() - 1);
                boost::algorithm::replace_all(relativePath, L"/", L"\\");
                kvp.value = reverseIniFolderPath + relativePath;
            }
            else {
                std::wstring relativePath = kvp.value;
                boost::algorithm::replace_all(relativePath, L"/", L"\\");
                kvp.value = reverseIniFolderPath + L"\\" + relativePath;
            }
            tmpResource.FileName = kvp.value;
        }

        if (matchResourceIB && !tmpResource.FileName.empty() && tmpResource.FileName != L"") {
            matchResourceIB = false;
            ResourceIBList.push_back(tmpResource);
        }

    }
    return ResourceIBList;
}


std::vector<ModResource> parseResourceAllList(std::vector<std::wstring> lines, std::wstring reverseIniFolderPath) {
    std::vector<ModResource> ResourceList;

    bool matchResource = false;
    ModResource tmpResource;

    for (std::wstring line : lines) {
        boost::algorithm::trim(line);
        std::wstring lowerLine = boost::algorithm::to_lower_copy(line);

        if (boost::algorithm::starts_with(lowerLine, ";")) {
            continue;
        }
        if (lowerLine.empty()) {
            continue;
        }

        if (boost::algorithm::starts_with(lowerLine, "[resource")) {
            matchResource = true;
            tmpResource = ModResource();
            tmpResource.SectionName = RemoveZhongKuohao(line);
        }

        if (matchResource && boost::algorithm::starts_with(lowerLine, "stride")) {
            KeyValuePair kvp(line);
            tmpResource.Stride = std::stoi(kvp.value);
        }

        if (matchResource && boost::algorithm::starts_with(lowerLine, "format")) {
            KeyValuePair kvp(line);
            tmpResource.Format = kvp.value;
        }

        if (matchResource && boost::algorithm::starts_with(lowerLine, "filename")) {
            KeyValuePair kvp(line);
            if (boost::algorithm::starts_with(kvp.value, L".")) {
                std::wstring relativePath = kvp.value.substr(1, kvp.value.length() - 1);
                boost::algorithm::replace_all(relativePath, L"/", L"\\");
                kvp.value = reverseIniFolderPath + relativePath;
            }
            else {
                std::wstring relativePath = kvp.value;
                boost::algorithm::replace_all(relativePath, L"/", L"\\");
                kvp.value = reverseIniFolderPath + L"\\" + relativePath;
            }
            tmpResource.FileName = kvp.value;
        }

        if (!tmpResource.FileName.empty() && tmpResource.FileName != L"") {
            ResourceList.push_back(tmpResource);
        }

    }
    return ResourceList;
}


std::vector<DrawIBMod> parseDrawIBModList(
    std::vector<TextureOverrideIB> TextureOverrideIBList,
    std::vector<ModResource> ResourceVBList,
    std::vector<ModResource> ResourceIBList) {

    std::vector<DrawIBMod> drawIBModList;


    //LogOutputSplitStr();
    //LogOutput(L"Parse Mod ini finished, show result: ");
    //LogOutputSplitStr();

    //LogOutput(L"ResourceIBList:");
    //for (ModResource obj : ResourceIBList) {
    //    obj.show();
    //}
    //LogOutput(L"ResourceVBList:");
    //for (ModResource obj : ResourceVBList) {
    //    obj.show();
    //}

    for (TextureOverrideIB& textureOverrideIB : TextureOverrideIBList) {
        for (ModResource resourceIB : ResourceIBList) {
            std::wstring ibResourceNameLower = boost::algorithm::to_lower_copy(textureOverrideIB.IBResourceName);
            std::wstring ibResourceSectionNameLower = boost::algorithm::to_lower_copy(resourceIB.SectionName);

            if (ibResourceNameLower == ibResourceSectionNameLower) {
                textureOverrideIB.IBFileFormat = resourceIB.Format;
                textureOverrideIB.IBFileName = resourceIB.FileName;
                break;
            }
        }
    }
    //LogOutput(L"TextureOverrideIBList:");
    //for (TextureOverrideIB obj : TextureOverrideIBList) {
    //    obj.show();
    //}
    //LogOutputSplitStr();


    std::unordered_map<std::wstring, std::vector<TextureOverrideIB>> hashTextureOverrideIBListMap;
    for (TextureOverrideIB obj : TextureOverrideIBList) {
        std::vector<TextureOverrideIB> tmpTextureOverrideIBList = hashTextureOverrideIBListMap[obj.HashValue];
        tmpTextureOverrideIBList.push_back(obj);
        hashTextureOverrideIBListMap[obj.HashValue] = tmpTextureOverrideIBList;
    }
    LogOutputSplitStr();

    LogOutput(L"Start to order TextureOverrideIB,make sure from lower to bigger.");
    std::unordered_map<std::wstring, std::vector<TextureOverrideIB>> orderedHashTextureOverrideIBListMap;
    for (const auto& pair : hashTextureOverrideIBListMap) {
        std::wstring hashValue = pair.first;
        std::vector<TextureOverrideIB> tmpTextureOverrideIBList = pair.second;
        LogOutput(L"Current Processing HaseValue: " + hashValue);

        std::map<int, std::wstring> textureOverrideSectionNameMap;
        std::map<std::wstring, TextureOverrideIB> SectionNameTextureOverrideMap;

        for (TextureOverrideIB ibObject : tmpTextureOverrideIBList) {
            std::wstring ibFileName = ibObject.IBFileName;
            std::wstring ibFilePath = ibFileName;
            std::wstring IBReadDxgiFormat = ibObject.IBFileFormat;
            boost::algorithm::to_lower(IBReadDxgiFormat);

            std::wstring sectionName = ibObject.SectionName;




            int readLength = 2;
            if (IBReadDxgiFormat == L"dxgi_format_r16_uint") {
                readLength = 2;
            }
            if (IBReadDxgiFormat == L"dxgi_format_r32_uint") {
                readLength = 4;
            }
            std::ifstream ReadIBFile(ibFilePath, std::ios::binary);

            char* data = new char[readLength];


            int tmpMinNumber = 9999999;
            int tmpMaxNumber = 0;

            int readCount = 0;
            while (ReadIBFile.read(data, readLength)) {
                int number = 0;
                if (IBReadDxgiFormat == L"dxgi_format_r16_uint") {
                    std::uint16_t value = (static_cast<unsigned char>(data[1]) << 8) |
                        static_cast<unsigned char>(data[0]);
                    number = value;
                }

                if (IBReadDxgiFormat == L"dxgi_format_r32_uint") {
                    std::uint32_t value = (static_cast<unsigned char>(data[3]) << 24) |
                        (static_cast<unsigned char>(data[2]) << 16) |
                        (static_cast<unsigned char>(data[1]) << 8) |
                        static_cast<unsigned char>(data[0]);
                    number = value;
                }

                if (number < tmpMinNumber) {
                    tmpMinNumber = number;
                }

                if (number > tmpMaxNumber) {
                    tmpMaxNumber = number;
                }
                readCount++;
            }


            ReadIBFile.close();

            ibObject.minNumber = tmpMinNumber;
            ibObject.maxNumber = tmpMaxNumber;
            ibObject.indexCount = readCount;
            SectionNameTextureOverrideMap[sectionName] = ibObject;

            LogOutput(L"sectionName: " + sectionName);
            LogOutput(L"minNumber: " + std::to_wstring(tmpMinNumber));
            LogOutput(L"indexCount: " + std::to_wstring(readCount));
            textureOverrideSectionNameMap[tmpMinNumber] = sectionName;
        }

        std::vector<TextureOverrideIB> TextureOverrideIBListWithFileNameOrdered;

        for (std::map<int, std::wstring>::iterator it = textureOverrideSectionNameMap.begin(); it != textureOverrideSectionNameMap.end(); ++it) {
            int minNumber = it->first;
            std::wstring sectionName = it->second;
            TextureOverrideIB ibObject = SectionNameTextureOverrideMap[sectionName];
            TextureOverrideIBListWithFileNameOrdered.push_back(ibObject);
        }

        orderedHashTextureOverrideIBListMap[hashValue] = TextureOverrideIBListWithFileNameOrdered;
    }
    hashTextureOverrideIBListMap = orderedHashTextureOverrideIBListMap;


    LogOutput(L"Output the final TextureOverrideIBList:");
    for (const auto& pair : hashTextureOverrideIBListMap) {
        std::wstring hashValue = pair.first;
        LogOutput(L"Current HaseValue:" + hashValue);
        std::vector<TextureOverrideIB> tmpTextureOverrideIBList = pair.second;
        for (TextureOverrideIB obj : tmpTextureOverrideIBList) {
            obj.show();
        }
        LogOutputSplitStr();
    }


    LogOutputSplitStr();

    LogOutput(L"Split ResourceVB based on different size.");
    std::unordered_map<int, std::vector<ModResource>> sizeResourceVBListMap;
    for (ModResource resourceVB : ResourceVBList) {
        std::wstring ResourceBufFilePath = resourceVB.FileName;
        LogOutput(L"ResourceBufFilePath: " + ResourceBufFilePath);
        std::wifstream file(ResourceBufFilePath, std::ifstream::ate | std::ifstream::binary);
        if (!file.is_open()) {
            LogError(L"This file didn't exists.");
        }

        std::streampos fileSize = file.tellg();

        file.close();

        int result = static_cast<int>(fileSize) / resourceVB.Stride;

        LogOutput(L"FilePath: " + ResourceBufFilePath + L"Vertex Number:" + std::to_wstring(result));

        std::vector<ModResource> tmpResourceVBList = sizeResourceVBListMap[result];
        tmpResourceVBList.push_back(resourceVB);
        sizeResourceVBListMap[result] = tmpResourceVBList;

    }
    LogOutputSplitStr();
    //LogOutput(L"Output and see the result:");
    //for (const auto& pair : sizeResourceVBListMap) {
    //    int size = pair.first;
    //    std::vector<ModResource> tmpResourceVBList = pair.second;
    //    LogOutput(L"Current size: " + std::to_wstring(size));
    //    for (ModResource tmpResource : tmpResourceVBList) {
    //        tmpResource.show();
    //    }
    //    LogOutputSplitStr();
    //}
    //LogOutputSplitStr();


    LogOutput(L"Start to combine DrawIBModList:");
    LogOutput(L"hashTextureOverrideIBListMap size: " + std::to_wstring(hashTextureOverrideIBListMap.size()));
    LogOutput(L"Method1: Use MaxNumber to match between TextureOverrideIB and ResourceVB");
    int shouldMatchCount = 0;
    for (const auto& pair : hashTextureOverrideIBListMap) {


        std::wstring hashValue = pair.first;
        LogOutput(L"Current HaseValue:" + hashValue);
        std::vector<TextureOverrideIB> tmpTextureOverrideIBList = pair.second;

        int maxNumber = 0;
        for (TextureOverrideIB obj : tmpTextureOverrideIBList) {
            if (obj.maxNumber > maxNumber) {
                maxNumber = obj.maxNumber;
            }
        }
        maxNumber++;
        LogOutput(L"DrawIB Vertex Count number: " + std::to_wstring(maxNumber));
        LogOutputSplitStr();
        DrawIBMod drawIBMod;
        drawIBMod.hash = hashValue;
        drawIBMod.textureOverrideIBList = tmpTextureOverrideIBList;
        for (TextureOverrideIB obj : tmpTextureOverrideIBList) {
            obj.show();
        }

        drawIBMod.resourceVBList = sizeResourceVBListMap[maxNumber];
        for (ModResource obj : drawIBMod.resourceVBList) {
            obj.show();
        }

        if (drawIBMod.resourceVBList.size() > 0) {
            drawIBModList.push_back(drawIBMod);
            shouldMatchCount++;
        }
        else {
            LogOutput(L"Can't find any match ResourceVB for hash: " + hashValue);
        }
    }
    LogOutput(L"Method1 Completed.");

    if (shouldMatchCount < hashTextureOverrideIBListMap.size()) {
        LogOutput(L"Can't match all only use exactly match, try fuzzy match with IndexCount.");
        LogOutput(L"Method1(Back Up): Use IndexCount to fuzzy match between TextureOverrideIB and ResourceVB");
        LogOutput(L"Because we can't match exactly with MaxNumber");
        LogOutput(L"So we think all MaxNumber match is wrong, and use fuzzy match to rematch all,and delete the MaxNumber match result.");
        drawIBModList.clear();

        for (const auto& pair : hashTextureOverrideIBListMap) {
            std::wstring hashValue = pair.first;
            LogOutput(L"Current HaseValue:" + hashValue);
            std::vector<TextureOverrideIB> tmpTextureOverrideIBList = pair.second;

            int combinedIndexCount = 0;
            for (TextureOverrideIB obj : tmpTextureOverrideIBList) {
                LogOutput(L"Current add IBFileName: " + obj.IBFileName);
                LogOutput(L"Combined IndexCount += " + std::to_wstring(obj.indexCount));
                LogOutput(L"Current IndexCount += " + std::to_wstring(combinedIndexCount));
                combinedIndexCount += obj.indexCount;
            }

            combinedIndexCount = combinedIndexCount / 3;

            LogOutput(L"DrawIB Index Count number: " + std::to_wstring(combinedIndexCount));
            LogOutputSplitStr();
            DrawIBMod drawIBMod;
            drawIBMod.hash = hashValue;
            drawIBMod.textureOverrideIBList = tmpTextureOverrideIBList;
            for (TextureOverrideIB obj : tmpTextureOverrideIBList) {
                obj.show();
            }

            int mostMatchSize = -1;
            int minDifference = 999999999;
            for (const auto& pair : sizeResourceVBListMap) {
                int size = pair.first;
                LogOutput(L"Curent Resource Size: " + std::to_wstring(size));

                int difference = abs(size - combinedIndexCount);
                LogOutput(L"Curent Difference: " + std::to_wstring(difference));
                if (difference < minDifference) {
                    minDifference = difference;
                    mostMatchSize = size;
                }

                //if (size > combinedIndexCount) {
                //    int difference = abs(size - combinedIndexCount);
                //    LogOutput(L"Curent Difference: " + std::to_wstring(difference));
                //    if (difference < minDifference) {
                //        minDifference = difference;
                //        mostMatchSize = size;
                //    }
                //}
            }

            if (mostMatchSize == -1) {
                LogError(L"Can't even find any fuzzy matched resource ??");
            }

            drawIBMod.resourceVBList = sizeResourceVBListMap[mostMatchSize];
            for (ModResource obj : drawIBMod.resourceVBList) {
                obj.show();
            }

            if (drawIBMod.resourceVBList.size() > 0) {
                drawIBModList.push_back(drawIBMod);
                shouldMatchCount++;
            }
            else {
                LogOutput(L"Can't find any match ResourceVB for hash: " + hashValue);
            }
        }

        if (shouldMatchCount < hashTextureOverrideIBListMap.size()) {
            LogWarning(L"Even fuzzy match can't match any ResourceVB ! this is crazy and seems can't even happen.");
        }
        else {
            LogOutput(L"Fuzzy Match use IndexCount success!");
        }
    }


    if (hashTextureOverrideIBListMap.size() == 1 && drawIBModList.size() == 0) {
        LogOutput(L"Process special situation: Only one single DrawIB and can't match any resourceVB.");
        LogOutput(L"Trying to force them together.");
        for (const auto& pair : hashTextureOverrideIBListMap) {
            std::wstring hashValue = pair.first;
            LogOutput(L"Current HaseValue:" + hashValue);
            std::vector<TextureOverrideIB> tmpTextureOverrideIBList = pair.second;

            int maxNumber = 0;
            for (TextureOverrideIB obj : tmpTextureOverrideIBList) {
                if (obj.maxNumber > maxNumber) {
                    maxNumber = obj.maxNumber;
                }
            }
            maxNumber++;
            LogOutput(L"DrawIB Vertex Count number: " + std::to_wstring(maxNumber));
            LogOutputSplitStr();
            DrawIBMod drawIBMod;
            drawIBMod.hash = hashValue;
            drawIBMod.textureOverrideIBList = tmpTextureOverrideIBList;
            for (TextureOverrideIB obj : tmpTextureOverrideIBList) {
                obj.show();
            }

            drawIBMod.resourceVBList = ResourceVBList;
            for (ModResource obj : drawIBMod.resourceVBList) {
                obj.show();
            }

            if (drawIBMod.resourceVBList.size() > 0) {
                drawIBModList.push_back(drawIBMod);
            }
            else {
                LogWarning(L"Can't find any match ResourceVB for hash: " + hashValue);
            }
        }
    }


    return drawIBModList;
}


ReverseModelSingle::ReverseModelSingle(std::wstring reverseFilePath) {
    this->iniFilePath = reverseFilePath;
    std::wstring reverseIniFolderPath = getFolderPathFromFilePath(reverseFilePath);
    this->iniFolderPath = reverseIniFolderPath;
    this->outputFolderPath = reverseIniFolderPath + L"\\reverse\\";
    std::filesystem::create_directories(outputFolderPath);
    LogOutput(L"Start to reverse Mod: " + reverseFilePath);
    LogOutput(L"Reverse mod folder: " + reverseIniFolderPath);
    LogOutput(L"Reverse output folder: " + outputFolderPath);
    std::vector<std::wstring> lines = readAllLinesW(reverseFilePath);

    std::vector<TextureOverrideIB> TextureOverrideIBList = parseTextureOverrideIBList(lines);
    std::vector<ModResource> ResourceVBList = parseResourceVBList(lines,reverseIniFolderPath);
    std::vector<ModResource> ResourceIBList = parseResourceIBList(lines,reverseIniFolderPath);

    this->drawIBModList = parseDrawIBModList(
        TextureOverrideIBList,
        ResourceVBList,
        ResourceIBList
    );
    
    LogOutputSplitStr();

}


void ReverseModelSingle::reverseAndOutput() {

    std::vector<ReversedObject> matchReversedObjectList = this->reversedObjectList;
    int reverseCounts = 0;
    for (ReversedObject reversedObject : matchReversedObjectList) {
        reverseCounts++;
        std::wstring outputPath = reversedObject.outputFolderGameTypePath + std::to_wstring(reverseCounts) + L"\\";
        std::filesystem::create_directories(outputPath);
        LogOutput(L"Create output folder:" + outputPath);

        int count = 0;
        for (TextureOverrideIB ibObject : reversedObject.textureOverrideIBList) {
            std::wstring IBFileName = ibObject.IBFileName;
            std::wstring IBReadDxgiFormat = ibObject.IBFileFormat;
            boost::algorithm::to_lower(IBReadDxgiFormat);
            std::wstring IBFilePath = IBFileName;
            int minNumber = ibObject.minNumber;


            int readLength = 2;
            if (IBReadDxgiFormat == L"dxgi_format_r16_uint") {
                readLength = 2;
            }
            if (IBReadDxgiFormat == L"dxgi_format_r32_uint") {
                readLength = 4;
            }
            std::ifstream ReadIBFile(IBFilePath, std::ios::binary);

            std::vector<uint16_t> IBR16DataList = {};
            std::vector<uint32_t> IBR32DataList = {};

            char* data = new char[readLength];

            while (ReadIBFile.read(data, readLength)) {
                if (IBReadDxgiFormat == L"dxgi_format_r16_uint") {
                    std::uint16_t value = CharArrayToUINT16_T(data);
                    value = value - static_cast<std::uint16_t>(minNumber);
                    IBR16DataList.push_back(value);

                }
                if (IBReadDxgiFormat == L"dxgi_format_r32_uint") {
                    std::uint32_t value = CharArrayToUINT32_T(data);
                    value = value - static_cast<std::uint32_t>(minNumber);
                    IBR32DataList.push_back(value);
                }
            }

            ReadIBFile.close();
            std::wstring outputIBFileName = outputPath + L"body_part" + std::to_wstring(count) + L".ib";

            if (IBReadDxgiFormat == L"dxgi_format_r16_uint") {
                IBR32DataList = std::vector<uint32_t>(IBR16DataList.size());
                std::transform(IBR16DataList.begin(), IBR16DataList.end(), IBR32DataList.begin(),
                    [](uint16_t value) { return static_cast<uint32_t>(value); });
            }

            LogOutput(L"IB file format: " + IBReadDxgiFormat);
            LogOutput(L"IB file length: " + std::to_wstring(IBR32DataList.size()));
            std::ofstream file(outputIBFileName, std::ios::binary); 
            for (const auto& data : IBR32DataList) {
                uint32_t paddedData = data; 
                file.write(reinterpret_cast<const char*>(&paddedData), sizeof(uint32_t));
            }
            file.close(); 

            count = count + 1;



        }

        LogOutputSplitStr();

        int stride = 0;
        for (std::wstring elementName : reversedObject.elementList) {
            LogOutput(L"processing element name: " + elementName);
            int byteWidth = reversedObject.d3d11ElementAttribute.ElementNameD3D11ElementMap[elementName].ByteWidth;
            stride = stride + byteWidth;
        }
        LogOutputSplitStr();


        std::vector<std::wstring> orderedElementList;
        for (std::wstring elementName: reversedObject.d3d11ElementAttribute.orderedFullElementList) {

            for (std::wstring element: reversedObject.elementList) {
                if (element == elementName) {
                    orderedElementList.push_back(elementName);
                    break;
                }
            }
        }


        for (int i = 0; i < count; i++) {

            //std::cout << "for count£º" << i + 1 << std::endl;

            std::wstring outputFmtFileName = outputPath + L"body_part" + std::to_wstring(i) + L".fmt";
            std::wofstream outputFmtFile(outputFmtFileName);

            outputFmtFile << "stride: " << stride << std::endl;
            outputFmtFile << "topology: trianglelist" << std::endl;
            outputFmtFile << "format: DXGI_FORMAT_R32_UINT" << std::endl;

            int elementNumber = 0;
            int alignedByteOffset = 0;
            for (std::wstring elementName : orderedElementList) {
                D3D11Element elementObject = reversedObject.d3d11ElementAttribute.ElementNameD3D11ElementMap[elementName];
                outputFmtFile << "element[" << elementNumber << "]:" << std::endl;
                outputFmtFile << "  SemanticName: " << elementObject.SemanticName << std::endl;
                outputFmtFile << "  SemanticIndex: " << elementObject.SemanticIndex << std::endl;
                outputFmtFile << "  Format: " << elementObject.Format << std::endl;
                outputFmtFile << "  InputSlot: " << elementObject.InputSlot << std::endl;
                outputFmtFile << "  AlignedByteOffset: " << alignedByteOffset << std::endl;
                alignedByteOffset = alignedByteOffset + elementObject.ByteWidth;
                outputFmtFile << "  InputSlotClass: " << elementObject.InputSlotClass << std::endl;
                outputFmtFile << "  InstanceDataStepRate: " << elementObject.InstanceDataStepRate << std::endl;
                elementNumber = elementNumber + 1;
            }
            outputFmtFile.close();
        }
        LogOutput(L"output fmt file over");
        LogOutputSplitStr();

        LogOutput(L"read vb file ,combine final file");
        std::unordered_map<int, std::vector<byte>> vb0IndexNumberBytes;

        for (ModResource resourceVBObject : reversedObject.resourceVBList) {
            LogOutput(L"Show the resourceVBObject before read and output to vb file.");
            resourceVBObject.show();
            if (resourceVBObject.FileName == L"" || resourceVBObject.FileName.empty()) {
                LogOutput(L"Can't find any FileNam in this ResourceVB.");
                continue;
            }
            LogOutput(L"current processing vb file: " + resourceVBObject.FileName);
            std::wstring resourceVBFileName = resourceVBObject.FileName;
            int resourceVBStride = resourceVBObject.Stride;
            std::wstring resourceVBFilePath = resourceVBFileName;

            LogOutput(L"current processing vb file path: " + resourceVBFilePath);

            std::ifstream resourceVBFile(resourceVBFilePath, std::ios::binary);
            resourceVBFile.seekg(0, std::ios::end);
            std::streampos resourceVBFileSize = resourceVBFile.tellg();
            resourceVBFile.seekg(0, std::ios::beg);
            LogOutput(L"Current processing vb file size: " + std::to_wstring(resourceVBFileSize));

            int resourceVBVertexCount = (int)resourceVBFileSize / resourceVBStride;
            LogOutput(L"Get vertex count number: " + std::to_wstring(resourceVBVertexCount));

            for (int i = 1; i <= resourceVBVertexCount; i++) {
                std::vector<byte> bytes(resourceVBStride);
                resourceVBFile.read(reinterpret_cast<char*>(bytes.data()), resourceVBStride);
                vb0IndexNumberBytes[i].insert(vb0IndexNumberBytes[i].end(), bytes.begin(), bytes.end());
            }
            resourceVBFile.close();
        }
        LogOutput(L"Read vb file finished, combined to final format.");
        LogOutputSplitStr();

        LogOutputSplitStr();

        for (int i = 0; i < count; i++) {
            std::wstring ibFileName = reversedObject.textureOverrideIBList[i].IBFileName;
            int ibMaxNumber = reversedObject.textureOverrideIBList[i].maxNumber;
            int ibMinNumber = reversedObject.textureOverrideIBList[i].minNumber;
            int readNumberOffset = ibMinNumber + 1;
            LogOutput(L"ibFileName: " + ibFileName + L"  ibMaxNumber: " + std::to_wstring(ibMaxNumber));
            LogOutput(L"ibFileName: " + ibFileName + L"  ibMinNumber: " + std::to_wstring(ibMinNumber));

            std::vector<byte> outputBytes;
            for (readNumberOffset; readNumberOffset <= ibMaxNumber + 1; readNumberOffset++) {
                std::vector<byte> indexBytes = vb0IndexNumberBytes[readNumberOffset];
                outputBytes.insert(outputBytes.end(), indexBytes.begin(), indexBytes.end());
            }

            std::wstring outputVBFilePath = outputPath + L"body_part" + std::to_wstring(i) + L".vb";
            LogOutput(L"vbFileName: " + outputVBFilePath);
            LogOutput(L"vbFileSize: " + std::to_wstring(outputBytes.size() / stride));

            if (outputBytes.size() == 0) {
                LogOutput(L"Can't output because size is 0.");
            }
            else {
                std::ofstream outputVBFile(outputVBFilePath, std::ios::binary);
                LogOutput(L"Start to output to folder.");
                outputVBFile.write(reinterpret_cast<const char*>(outputBytes.data()), outputBytes.size());
                outputVBFile.close();
            }
            

        }

        LogOutputSplitStr();
    }
    LogOutput(L"Reverse completed!");
}




void ReverseModelSingle::parseElementList(std::wstring gameName) {
    LogOutput(L"Start to parse ElementList, first initialize config");
    WheelConfigs wheelConfig;
    std::vector<D3D11ElementAttributeClass> d3d11ElementAttributeList = wheelConfig.getD3D11ElementAttributeListByGameName(gameName);
    LogOutput(L"Initailize D3D11ElementList completed£¬d3d11ElementAttribute size: " + std::to_wstring(d3d11ElementAttributeList.size()));
    LogOutputSplitStr();

    for (DrawIBMod drawIBMod : drawIBModList) {
        std::wstring hashValue = drawIBMod.hash;
        std::vector<TextureOverrideIB> textureOverrideIBList = drawIBMod.textureOverrideIBList;
        std::vector<ModResource> ResourceVBList = drawIBMod.resourceVBList;
        LogOutput(L"Current processing DrawIBMod Hash value: " + hashValue);
        LogOutput(L"textureOverrideIBList size: " + std::to_wstring(textureOverrideIBList.size()));
        LogOutput(L"ResourceVBList size: " + std::to_wstring(ResourceVBList.size()));
        if (ResourceVBList.size() == 0) {
            LogWarning(L"Can't find any ResourceVB in this DrawIB hash.");
        }
        LogOutputSplitStr();

        std::vector<ReversedObject> matchReversedObjectList;

        for (D3D11ElementAttributeClass d3d11ElementAttributes : d3d11ElementAttributeList) {
            if (d3d11ElementAttributes.CategorySlotMap.size() != ResourceVBList.size()) {
                LogOutput(L"Try to parse with type:" + d3d11ElementAttributes.GameType + L" but can't match category size.");
                continue;
            }
            LogOutput(L"Current detecting type: " + d3d11ElementAttributes.GameType);
            std::wstring outputFolderGameTypePath = outputFolderPath + hashValue + L"\\" + d3d11ElementAttributes.GameType + L"_";

            if (ResourceVBList.size() == 3) {

                ModResource ResourcePosition;
                ModResource ResourceTexcoord;
                ModResource ResourceBlend;

                std::vector<std::wstring> elementList;
                std::vector<ModResource> vbResourceOrderedList;

                LogOutput(L"Detect normal Position,Texcoord,Blend mod.");

                int positionByteWidth = d3d11ElementAttributes.ElementNameD3D11ElementMap[L"POSITION"].ByteWidth;
                int normalByteWidth = d3d11ElementAttributes.ElementNameD3D11ElementMap[L"NORMAL"].ByteWidth;
                int tangentByteWidth = d3d11ElementAttributes.ElementNameD3D11ElementMap[L"TANGENT"].ByteWidth;
                int positionStrie = positionByteWidth + normalByteWidth + tangentByteWidth;

                LogOutput(L"Start to load Position category's element list:");
                LogOutput(L"Position stride:" + std::to_wstring(positionStrie));

                for (ModResource resourceVB : ResourceVBList) {
                    int stride = resourceVB.Stride;
                    LogOutput(L"stride:" + std::to_wstring(stride));
                    std::wstring resourceFileName = resourceVB.FileName;
                    LogOutput(L"resourceFileName:" + resourceFileName);

                    //POSITION
                    if (stride == positionStrie) {
                        ResourcePosition = resourceVB;
                        elementList.push_back(L"POSITION");
                        elementList.push_back(L"NORMAL");
                        elementList.push_back(L"TANGENT");
                        break;

                    }
                }

                int colorByteWidth = d3d11ElementAttributes.ElementNameD3D11ElementMap[L"COLOR"].ByteWidth;
                int texcoordByteWidth = d3d11ElementAttributes.ElementNameD3D11ElementMap[L"TEXCOORD"].ByteWidth;
                int texcoord1ByteWidth = d3d11ElementAttributes.ElementNameD3D11ElementMap[L"TEXCOORD1"].ByteWidth;
                LogOutput(L"Start to load TEXCOORD category's element list:");

                for (ModResource resourceVB : ResourceVBList) {
                    int stride = resourceVB.Stride;
                    std::wstring resourceFileName = resourceVB.FileName;
                    //TEXCOORD
                    if (stride == texcoordByteWidth) {
                        ResourceTexcoord = resourceVB;
                        elementList.push_back(L"TEXCOORD");
                        break;

                    }
                    if (stride == colorByteWidth + texcoordByteWidth) {
                        ResourceTexcoord = resourceVB;
                        elementList.push_back(L"COLOR");
                        elementList.push_back(L"TEXCOORD");
                        break;

                    }
                    if (stride == colorByteWidth + texcoordByteWidth + texcoord1ByteWidth) {
                        ResourceTexcoord = resourceVB;
                        elementList.push_back(L"COLOR");
                        elementList.push_back(L"TEXCOORD");
                        elementList.push_back(L"TEXCOORD1");
                        break;

                    }
                }
                LogOutputSplitStr();

                LogOutput(L"Start to load Blend category's element list:");

                for (ModResource resourceVB : ResourceVBList) {
                    LogOutput(L"Current processing ResourceVB: " + resourceVB.FileName);

                    int stride = resourceVB.Stride;
                    std::wstring resourceFileName = resourceVB.FileName;

                    std::vector<std::wstring> blendElementList;

                    for (const auto& pair : d3d11ElementAttributes.ElementNameD3D11ElementMap) {
                        std::wstring elementName = pair.first;
                        D3D11Element d3d11Element = pair.second;
                        if (d3d11Element.Category == L"Blend") {
                            blendElementList.push_back(elementName);
                        }
                    }

                    int blendStride = 0;
                    for (std::wstring blendElementName : blendElementList) {
                        int byteWidth = d3d11ElementAttributes.ElementNameD3D11ElementMap[blendElementName].ByteWidth;
                        blendStride += byteWidth;
                    }
                    LogOutput(L"Blend stride:" + std::to_wstring(blendStride));

                    //BLEND
                    if (stride == blendStride) {
                        ResourceBlend = resourceVB;

                        if (boost::algorithm::any_of_equal(blendElementList, L"BLENDWEIGHT")) {
                            elementList.push_back(L"BLENDWEIGHT");
                        }
                        if (boost::algorithm::any_of_equal(blendElementList, L"BLENDWEIGHTS")) {
                            elementList.push_back(L"BLENDWEIGHTS");
                        }
                        elementList.push_back(L"BLENDINDICES");
                        break;
                    }
                }
                LogOutputSplitStr();


                /*LogOutput(L"current Element list detected");
                for (std::wstring elementName : elementList) {
                    LogOutput(elementName);
                }*/

                vbResourceOrderedList.push_back(ResourcePosition);
                vbResourceOrderedList.push_back(ResourceTexcoord);
                vbResourceOrderedList.push_back(ResourceBlend);

                ReversedObject reversedObject;
                reversedObject.elementList = elementList;
                reversedObject.d3d11ElementAttribute = d3d11ElementAttributes;
                reversedObject.outputFolderGameTypePath = outputFolderGameTypePath;
                reversedObject.textureOverrideIBList = textureOverrideIBList;
                reversedObject.resourceVBList = vbResourceOrderedList;

                matchReversedObjectList.push_back(reversedObject);
            }
            else if (ResourceVBList.size() == 1) {
                int bufStride = 0;
                std::vector<std::wstring> elementList;
                LogOutput(L"Detect only one ResourceVB, maybe this is a object mod.");
                ModResource resourceVBObject = ResourceVBList[0];

                elementList.clear();
                bufStride = 0;
                for (const auto& pair : d3d11ElementAttributes.ElementNameD3D11ElementMap) {
                    std::wstring elementName = pair.first;
                    D3D11Element d3d11Element = pair.second;
                    int byteWidth = d3d11Element.ByteWidth;
                    bufStride += byteWidth;
                    elementList.push_back(elementName);
                    LogOutput(L"Current ElementName: " + elementName + L" ByteWidth: " + std::to_wstring(byteWidth));
                }
                if (resourceVBObject.Stride == bufStride) {

                    std::vector<ModResource> vbResourceOrderedList;
                    vbResourceOrderedList.push_back(resourceVBObject);
                    ReversedObject reversedObject;
                    reversedObject.elementList = elementList;
                    reversedObject.d3d11ElementAttribute = d3d11ElementAttributes;
                    reversedObject.outputFolderGameTypePath = outputFolderGameTypePath;
                    reversedObject.textureOverrideIBList = textureOverrideIBList;
                    reversedObject.resourceVBList = vbResourceOrderedList;
                    matchReversedObjectList.push_back(reversedObject);
                }

                elementList.clear();
                bufStride = 0;
                for (const auto& pair : d3d11ElementAttributes.ElementNameD3D11ElementMap) {
                    std::wstring elementName = pair.first;
                    if (elementName == L"TEXCOORD1") {
                        continue;
                    }
                    D3D11Element d3d11Element = pair.second;
                    int byteWidth = d3d11Element.ByteWidth;
                    bufStride += byteWidth;
                    elementList.push_back(elementName);
                    LogOutput(L"Current ElementName: " + elementName + L" ByteWidth: " + std::to_wstring(byteWidth));
                }
                if (resourceVBObject.Stride == bufStride) {
                    std::vector<ModResource> vbResourceOrderedList;
                    vbResourceOrderedList.push_back(resourceVBObject);
                    ReversedObject reversedObject;
                    reversedObject.elementList = elementList;
                    reversedObject.d3d11ElementAttribute = d3d11ElementAttributes;
                    reversedObject.outputFolderGameTypePath = outputFolderGameTypePath;
                    reversedObject.textureOverrideIBList = textureOverrideIBList;
                    reversedObject.resourceVBList = vbResourceOrderedList;
                    matchReversedObjectList.push_back(reversedObject);
                }



            }

            LogOutput(L"Parse ElementList completed!");

            this->reversedObjectList = matchReversedObjectList;
            reverseAndOutput();
        }

    }



}

