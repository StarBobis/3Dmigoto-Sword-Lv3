#include "WheelFunctions.h"
#include "WheelConfigs.h"
#include "NMStringUtils.h"
#include "NMJsonUtils.h"
#include "NMLoggerUtils.h"


WheelConfigs::WheelConfigs() {

}

std::vector<D3D11ElementAttributeClass> WheelConfigs::getD3D11ElementAttributeListByGameName(std::wstring gameName) {
    std::vector<D3D11ElementAttributeClass> detectD3d11ElementAttributeList;
    if (gameName == L"GI") {
        detectD3d11ElementAttributeList = {
            D3D11ElementAttributeClass(L"GIBody"),
            D3D11ElementAttributeClass(L"GIBodyNPC"),
            D3D11ElementAttributeClass(L"GIObject"),
            D3D11ElementAttributeClass(L"GIObject2"),
            D3D11ElementAttributeClass(L"GIObject3")
        };
    }
    else if (gameName == L"HI3") {
        detectD3d11ElementAttributeList = {
            D3D11ElementAttributeClass(L"HI3Body"),
            D3D11ElementAttributeClass(L"HI3Body2"),
            D3D11ElementAttributeClass(L"HI3Object")
        };
    }
    else if (gameName == L"HSR") {
        detectD3d11ElementAttributeList = {
            D3D11ElementAttributeClass(L"HSRBody"),
            D3D11ElementAttributeClass(L"HSRBodyEnemy"),
            D3D11ElementAttributeClass(L"HSRBodyNPC"),
            D3D11ElementAttributeClass(L"HSRHair"),
            D3D11ElementAttributeClass(L"HSRObject"),
            D3D11ElementAttributeClass(L"HSRObjectIB"),
            D3D11ElementAttributeClass(L"HSRWeapon"),
            D3D11ElementAttributeClass(L"HSRWeaponType2"),
            D3D11ElementAttributeClass(L"HSRWeaponType3"),
            D3D11ElementAttributeClass(L"HSR210Body"),
            D3D11ElementAttributeClass(L"HSRBodyObject"),
            D3D11ElementAttributeClass(L"HSRObject2")
        };
    }
    else if (gameName == L"Unknown") {
        detectD3d11ElementAttributeList = {
            D3D11ElementAttributeClass(L"UnknownBody"),
            D3D11ElementAttributeClass(L"UnknownEyeball"),
            D3D11ElementAttributeClass(L"UnknownObject"),
            D3D11ElementAttributeClass(L"UnknownObjectIB"),
            D3D11ElementAttributeClass(L"UnknownWeapon"),
            D3D11ElementAttributeClass(L"UnknownWeapon2")
        };
    }
    else if (gameName == L"GF2") {
        detectD3d11ElementAttributeList = {
            D3D11ElementAttributeClass(L"GF2Body"),
            D3D11ElementAttributeClass(L"GF2Face"),
            D3D11ElementAttributeClass(L"GF2Leg"),
            D3D11ElementAttributeClass(L"GF2Object"),
            D3D11ElementAttributeClass(L"GF2ObjectR32"),
            D3D11ElementAttributeClass(L"GF2Weapon")
        };
    }
    else if (gameName == L"ZZZ") {
        detectD3d11ElementAttributeList = {
            D3D11ElementAttributeClass(L"ZZZBody"),
            D3D11ElementAttributeClass(L"ZZZBodyType2"),
            D3D11ElementAttributeClass(L"ZZZObject"),
            D3D11ElementAttributeClass(L"ZZZObjectType2"),
            D3D11ElementAttributeClass(L"ZZZWeapon")
        };
    }
    else if (gameName == L"BS") {
        detectD3d11ElementAttributeList = {
            D3D11ElementAttributeClass(L"BSBody")
        };
    }
    else if (gameName == L"KALABIYAU") {
        detectD3d11ElementAttributeList = {
            D3D11ElementAttributeClass(L"KALABIYAUBody")
        };
    }
    LogOutput(L"getD3D11ElementAttributeListByGameName success.");
    return detectD3d11ElementAttributeList;
}