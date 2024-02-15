#pragma once
#include "WheelFunctions.h"
#include "WheelFunctions.h"
#include "NMLoggerUtils.h"
#include "NMLoggerUtils.h"
#include "NMLoggerUtils.h"
#include <vector>


class ModResource {
public:
    std::wstring SectionName;
    std::wstring Format;
    int Stride;
    std::wstring FileName;
    std::wstring Type;

    ModResource() {
        this->SectionName = L"";
        this->Format = L"";
        this->Stride = 0;
        this->FileName = L"";
        this->Type = L"";
    }

    void show() {
        LogOutput(L"SectionName: " + this->SectionName);
        LogOutput(L"Format: " + this->Format);
        LogOutput(L"Stride: " + std::to_wstring(this->Stride));
        LogOutput(L"FileName: " + this->FileName);
        LogOutput(L"Type: " + this->Type);
        LogOutputSplitStr();
    }
};


class KeyValuePair {
public:
    std::wstring key;
    std::wstring value;

    KeyValuePair(std::wstring inputLine) {
        std::vector<std::wstring> splitResultList;
        boost::split(splitResultList, inputLine, boost::is_any_of(L"="));
        if (splitResultList.size() < 2) {
            LogError(L"Wrong kvpair format! Please check your input line.");
        }

        key = splitResultList[0];
        value = splitResultList[1];

        boost::algorithm::trim(key);
        boost::algorithm::trim(value);

    }
};


class Condition {
public:
    std::wstring ConditionName;
    int ConditionLevel;
    bool Positive;

    Condition() {
        this->ConditionName = L"";
        this->ConditionLevel = 0;
        this->Positive = true;
    }

    void show() {
        LogOutput(L"ConditionName: " + this->ConditionName);
        LogOutput(L"ConditionLevel: " + std::to_wstring(this->ConditionLevel));
        LogOutput(L"Positive: " + std::to_wstring(this->Positive));
        LogOutputSplitStr();
    }
};


class ResourceReplace {
public:
    std::wstring OriginalLine;
    std::vector<Condition> ConditionList;

    ResourceReplace() {
        this->OriginalLine = L"";
        //this->ConditionList = std::vector<Condition>();
    }

    void show() {
        LogOutput(L"OriginalLine: " + this->OriginalLine);
        for (Condition condition : this->ConditionList) {
            condition.show();
        }
        LogOutputSplitStr();
    }
};


class CycleKey {
public:
    std::wstring Key;
    std::wstring VarName;
    std::vector<std::wstring> VarValueList;

    CycleKey() {
        this->Key = L"";
        this->VarName = L"";
        //this->VarValueList = std::vector<std::wstring>();
    }

    void show() {
        LogOutput(L"Key: " + this->Key);
        LogOutput(L"VarName: " + this->VarName);
        LogOutput(L"VarValueList: ");
        for (std::wstring varValue : this->VarValueList) {
            LogOutput(L"VarValue: " + varValue);
        }
        LogOutputSplitStr();
    }
};


class TextureOverrideIB {
public:
    std::wstring SectionName;
    std::wstring HashValue;
    int MatchFirstIndex = 0;
    std::wstring IBResourceName;
    std::wstring IBFileName;
    std::wstring IBFileFormat;

    int minNumber;
    int maxNumber;

    //For fuzzy match
    int indexCount;


    TextureOverrideIB() {
        this->SectionName = L"";
        this->HashValue = L"";
        this->MatchFirstIndex = 0;
        this->IBResourceName = L"";
        this->IBFileName = L"";
        this->IBFileFormat = L"";

        this->minNumber = 0;
        this->maxNumber = 0;
        this->indexCount = 0;
    }

    void show() {
        LogOutput(L"SectionName: " + SectionName);
        LogOutput(L"HashValue: " + HashValue);
        LogOutput(L"MatchFirstIndex: " + std::to_wstring(MatchFirstIndex));
        LogOutput(L"IBResourceName: " + IBResourceName);
        LogOutput(L"IBFileName: " + IBFileName);
        LogOutput(L"IBFileFormat: " + IBFileFormat);
        LogOutput(L"minNumber: " + std::to_wstring(minNumber));
        LogOutput(L"maxNumber: " + std::to_wstring(maxNumber));
        LogOutputSplitStr();
    }
};


class TextureOverride {
public:
    std::wstring SectionName;
    std::wstring HashValue;
    std::wstring ActiveConditionStr;
    std::wstring MatchFirstIndex;

    std::vector<std::wstring> CommandList;
    std::vector<ResourceReplace> ResourceReplaceList;
    std::vector<ResourceReplace> ActiveResourceReplaceList;

    TextureOverride() {
        this->SectionName = L"";
        this->HashValue = L"";
        this->ActiveConditionStr = L"";
        this->MatchFirstIndex = L"";
    }

    void show() {
        LogOutput(L"SectionName: " + this->SectionName);
        LogOutput(L"HashValue: " + this->HashValue);
        LogOutput(L"ActiveConditionStr: " + this->ActiveConditionStr);
    }

};


class DrawIBMod {
public:
    std::wstring hash;
    std::vector<TextureOverrideIB> textureOverrideIBList;
    std::vector<ModResource> resourceVBList;

};


class ReversedObject {
public:
    std::wstring outputFolderGameTypePath;

    std::vector<std::wstring> elementList;
    D3D11ElementAttributeClass d3d11ElementAttribute;

    std::vector<TextureOverrideIB> textureOverrideIBList;
    std::vector<ModResource> resourceVBList;

};



class ReverseModelSingle {
public:
    std::wstring iniFilePath;
    std::wstring iniFolderPath;
    std::wstring outputFolderPath;

    std::vector<DrawIBMod> drawIBModList;

    std::vector<ReversedObject> reversedObjectList;


    ReverseModelSingle(){
        this->iniFilePath = L"";
        this->iniFolderPath = L"";
        this->outputFolderPath = L"";
    }

    ReverseModelSingle(std::wstring);

    void parseElementList(std::wstring);

    void reverseAndOutput();

};









std::unordered_map<std::wstring, std::vector<ResourceReplace>> parseCommandResourceReplaceListDict(std::vector<std::wstring> lineList);
std::vector<TextureOverride> parseTextureOverrideList(std::vector<std::wstring> lineList);
std::vector<TextureOverride> matchActiveResourceReplace(
    std::vector<TextureOverride> textureOverrideList,
    std::unordered_map<std::wstring, std::vector<ResourceReplace>> commandResourceReplaceListDict);


std::unordered_map<std::wstring, ModResource> parseResourceDict(std::vector<std::wstring> lineList, std::wstring iniLocationFolder);
std::vector<CycleKey> parseCycleKeyList(std::vector<std::wstring> lineList);
std::vector<std::unordered_map<std::wstring, std::wstring>> calculateKeyCombination(std::vector<CycleKey> cycleKeyList);


std::vector<ModResource> parseResourceVBList(std::vector<std::wstring> lines, std::wstring reverseIniFolderPath);
std::vector<ModResource> parseResourceIBList(std::vector<std::wstring> lines, std::wstring reverseIniFolderPath);
std::vector<ModResource> parseResourceAllList(std::vector<std::wstring> lines, std::wstring reverseIniFolderPath);


std::vector<DrawIBMod> parseDrawIBModList(
    std::vector<TextureOverrideIB> TextureOverrideIBList,
    std::vector<ModResource> ResourceVBList,
    std::vector<ModResource> ResourceIBList);

void parseMergedInI(std::wstring filePath,std::wstring gameName);







