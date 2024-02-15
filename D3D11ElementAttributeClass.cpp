#include "D3D11ElementAttributeClass.h"
#include "WheelFunctions.h"
#include "NMStringUtils.h"
#include "NMLoggerUtils.h"

D3D11ElementAttributeClass::D3D11ElementAttributeClass() {

}


D3D11ElementAttributeClass::D3D11ElementAttributeClass(std::wstring gameType) {

	this->GameType = gameType;
	LogOutput(L"Current Processing: " + this->GameType);

	//Honkai Impact 3rd
	if (gameType == L"HI3Body") {
		SetHI3Body();
	}
	if (gameType == L"HI3Body2") {
		SetHI3Body2();
	}
	else if (gameType == L"HI3Object") {
		SetHI3Object();
	}
	//Naraka Bladepoint
	else if (gameType == L"UnknownBody") {
		SetNBPBody();
	}
	else if (gameType == L"UnknownEyeball") {
		SetNBPEyeball();
	}
	else if (gameType == L"UnknownObject") {
		SetNBPObject();
	}
	else if (gameType == L"UnknownWeapon") {
		SetNBPWeapon();
	}
	else if (gameType == L"UnknownWeapon2") {
		SetNBPWeapon2();
	}
	else if (gameType == L"UnknownObjectIB") {
		SetNBPObjectIB();
	}
	//Honkai StarRail
	else if (gameType == L"HSRBody") {
		SetHSRBody();
	}
	else if (gameType == L"HSRBodyEnemy") {
		SetHSRBodyEnemy();
	}
	else if (gameType == L"HSRBodyNPC") {
		SetHSRBodyNPC();
	}

	else if (gameType == L"HSRHair") {
		SetHSRHair();
	}
	else if (gameType == L"HSRWeapon") {
		SetHSRWeapon();
	}
	else if (gameType == L"HSRWeaponType2") {
		SetHSRWeaponType2();
	}
	else if (gameType == L"HSRWeaponType3") {
		SetHSRWeaponType3();
	}
	else if (gameType == L"HSRObject") {
		SetHSRObject();
	}
	else if (gameType == L"HSRObjectIB") {
		SetHSRObjectIB();
	}
	//Genshin Impact
	else if (gameType == L"GIBody") {
		SetGIBody();
	}
	else if (gameType == L"GIObject") {
		SetGIObject();
	}
	else if (gameType == L"GIBodyNPC") {
		SetGIBodyNPC();
	}
	else if (gameType == L"GIObject2") {
		SetGIObject2();
	}
	else if (gameType == L"GIObject3") {
		SetGIObject3();
	}
	//Zenless Zero Zone
	else if (gameType == L"ZZZBody") {
		SetZZZBody();
	}
	else if (gameType == L"ZZZBodyType2") {
		SetZZZBodyType2();
	}
	else if (gameType == L"ZZZWeapon") {
		SetZZZWeapon();
	}
	else if (gameType == L"ZZZObject") {
		SetZZZObject();
	}
	else if (gameType == L"ZZZObjectType2") {
		SetZZZObjectType2();
	}

	//then initialize CategorySlotMap and CategoryTopologyMap
	LogOutput(L"Start to initialize CategorySlotMap and CategoryTopologyMap:");
	for (const auto& pair : ElementNameD3D11ElementMap) {
		D3D11Element d3d11Element = pair.second;
		CategorySlotMap[d3d11Element.Category] = d3d11Element.ExtractVBFile;
		LogOutput(L"Add to CategorySlotMap, Category: " + d3d11Element.Category + L" ExtractVBFile: " + d3d11Element.ExtractVBFile);
		CategoryTopologyMap[d3d11Element.Category] = d3d11Element.ExtractTechnique;
		LogOutput(L"Add to CategoryTopologyMap, Category: " + d3d11Element.Category + L" Topology: " + d3d11Element.ExtractTechnique);

	}

	LogOutputSplitStr();
}

