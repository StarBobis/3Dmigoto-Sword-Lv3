#pragma once
#include <string>
#include <vector>
#include <unordered_map>


class D3D11Element {
public:
    std::wstring SemanticName = L"";
    std::wstring ExtractSemanticName = L"";
    std::wstring SemanticIndex = L"";
    std::wstring OutputSemanticIndex = L"";
    std::wstring Format = L"";
    std::wstring InputSlot = L"0";
    std::wstring InputSlotClass = L"per-vertex";
    std::wstring InstanceDataStepRate = L"0";
    int ByteWidth = 0;
    std::wstring ExtractVBFile = L"";
    std::wstring ExtractTechnique = L"";
    std::wstring Category = L"";

    int ElementNumber = 0;
    int AlignedByteOffset = 0;
};



class D3D11ElementAttributeClass {
public:
    std::wstring GameType;
    std::unordered_map<std::wstring, D3D11Element> ElementNameD3D11ElementMap;
    std::unordered_map<std::wstring, D3D11Element> ExtractSemanticNameD3D11ElementMap;
    std::unordered_map <std::wstring, std::wstring> CategorySlotMap;
    std::unordered_map <std::wstring, std::wstring> CategoryTopologyMap;

    std::unordered_map <std::wstring, std::wstring> CategoryDrawCategoryMap;

    std::vector<std::wstring> orderedFullElementList;

    bool normalIs4D = false;

    bool reserve10Texcoord = false;
    bool reserve10Normal = false;
    bool reserve10Position = false;


    bool patchBLENDWEIGHTS = false;

    bool ifUseMaxStrideTexcoordIfCannotFindPerfect = false;

    //Add support for different games
    //Honkai Impact 3rd
    void SetHI3Body();
    void SetHI3Body2();
    void SetHI3Object();

    //Naraka Bladepoint
    void SetNBPBody();
    void SetNBPObject();
    void SetNBPWeapon();
    void SetNBPWeapon2();
    void SetNBPObjectIB();
    void SetNBPEyeball();

    //Genshin Impact
    void SetGIBody();
    void SetGIBodyNPC();
    void SetGIObject();
    void SetGIObject2();
    void SetGIObject3();

    //Honkai StarRail
    void SetHSRBody();
    void SetHSRBodyEnemy();
    void SetHSRBodyNPC();
    void SetHSRHair();
    void SetHSRWeapon();
    void SetHSRWeaponType2();
    void SetHSRWeaponType3();
    void SetHSRObject();
    void SetHSRObjectIB();

    //Zenless Zero Zone
    void SetZZZBody();
    void SetZZZBodyType2();
    void SetZZZWeapon();
    void SetZZZObject();
    void SetZZZObjectType2();


    D3D11ElementAttributeClass();

    D3D11ElementAttributeClass(std::wstring);
};