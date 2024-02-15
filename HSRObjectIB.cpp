#include "D3D11ElementAttributeClass.h"

void D3D11ElementAttributeClass::SetHSRObjectIB() {
	this->CategoryDrawCategoryMap[L"Position"] = L"Position";
	this->CategoryDrawCategoryMap[L"Texcoord"] = L"Texcoord";
	this->CategoryDrawCategoryMap[L"Blend"] = L"Position";

	D3D11Element POSITION;
	POSITION.SemanticName = L"POSITION";
	POSITION.ExtractSemanticName = L"POSITION";
	POSITION.SemanticIndex = L"0";
	POSITION.OutputSemanticIndex = L"0";
	POSITION.Format = L"R32G32B32_FLOAT";
	POSITION.InputSlot = L"0";
	POSITION.InputSlotClass = L"per-vertex";
	POSITION.InstanceDataStepRate = L"0";
	POSITION.ByteWidth = 12;
	POSITION.ExtractVBFile = L"vb0";
	POSITION.ExtractTechnique = L"trianglelist";
	POSITION.Category = L"Position";
	this->ElementNameD3D11ElementMap[L"POSITION"] = POSITION;

	D3D11Element NORMAL;
	NORMAL.SemanticName = L"NORMAL";
	NORMAL.ExtractSemanticName = L"NORMAL";
	NORMAL.SemanticIndex = L"0";
	NORMAL.OutputSemanticIndex = L"0";
	NORMAL.Format = L"R32G32B32_FLOAT";
	NORMAL.InputSlot = L"0";
	NORMAL.InputSlotClass = L"per-vertex";
	NORMAL.InstanceDataStepRate = L"0";
	NORMAL.ByteWidth = 12;
	NORMAL.ExtractVBFile = L"vb0";
	NORMAL.ExtractTechnique = L"trianglelist";
	NORMAL.Category = L"Position";
	this->ElementNameD3D11ElementMap[L"NORMAL"] = NORMAL;

	D3D11Element TANGENT;
	TANGENT.SemanticName = L"TANGENT";
	TANGENT.ExtractSemanticName = L"TANGENT";
	TANGENT.SemanticIndex = L"0";
	TANGENT.OutputSemanticIndex = L"0";
	TANGENT.Format = L"R32G32B32A32_FLOAT";
	TANGENT.InputSlot = L"0";
	TANGENT.InputSlotClass = L"per-vertex";
	TANGENT.InstanceDataStepRate = L"0";
	TANGENT.ByteWidth = 16;
	TANGENT.ExtractVBFile = L"vb0";
	TANGENT.ExtractTechnique = L"trianglelist";
	TANGENT.Category = L"Position";
	this->ElementNameD3D11ElementMap[L"TANGENT"] = TANGENT;

	D3D11Element COLOR;
	COLOR.SemanticName = L"COLOR";
	COLOR.ExtractSemanticName = L"COLOR";
	COLOR.SemanticIndex = L"0";
	COLOR.OutputSemanticIndex = L"0";
	COLOR.Format = L"R8G8B8A8_UNORM";
	COLOR.InputSlot = L"0";
	COLOR.InputSlotClass = L"per-vertex";
	COLOR.InstanceDataStepRate = L"0";
	COLOR.ByteWidth = 4;
	COLOR.ExtractVBFile = L"vb1";
	COLOR.ExtractTechnique = L"trianglelist";
	COLOR.Category = L"Texcoord";
	this->ElementNameD3D11ElementMap[L"COLOR"] = COLOR;

	D3D11Element TEXCOORD;
	TEXCOORD.SemanticName = L"TEXCOORD";
	TEXCOORD.ExtractSemanticName = L"TEXCOORD";
	TEXCOORD.SemanticIndex = L"0";
	TEXCOORD.OutputSemanticIndex = L"0";
	TEXCOORD.Format = L"R32G32_FLOAT";
	TEXCOORD.InputSlot = L"0";
	TEXCOORD.InputSlotClass = L"per-vertex";
	TEXCOORD.InstanceDataStepRate = L"0";
	TEXCOORD.ByteWidth = 8;
	TEXCOORD.ExtractVBFile = L"vb1";
	TEXCOORD.ExtractTechnique = L"trianglelist";
	TEXCOORD.Category = L"Texcoord";
	this->ElementNameD3D11ElementMap[L"TEXCOORD"] = TEXCOORD;

	D3D11Element TEXCOORD1;
	TEXCOORD1.SemanticName = L"TEXCOORD";
	TEXCOORD1.ExtractSemanticName = L"TEXCOORD1";
	TEXCOORD1.SemanticIndex = L"1";
	TEXCOORD1.OutputSemanticIndex = L"1";
	TEXCOORD1.Format = L"R32G32_FLOAT";
	TEXCOORD1.InputSlot = L"0";
	TEXCOORD1.InputSlotClass = L"per-vertex";
	TEXCOORD1.InstanceDataStepRate = L"0";
	TEXCOORD1.ByteWidth = 8;
	TEXCOORD1.ExtractVBFile = L"vb1";
	TEXCOORD1.ExtractTechnique = L"trianglelist";
	TEXCOORD1.Category = L"Texcoord";
	this->ElementNameD3D11ElementMap[L"TEXCOORD1"] = TEXCOORD1;

	this->ExtractSemanticNameD3D11ElementMap = this->ElementNameD3D11ElementMap;

	this->orderedFullElementList = { L"POSITION",L"NORMAL",L"TANGENT",L"COLOR",L"TEXCOORD",L"TEXCOORD1" };

};