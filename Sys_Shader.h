//=======================================================================================
//
//	シェーダ定義
//
//=======================================================================================
#ifndef _H_SHADER
#define _H_SHADER

//-------- ヘッダ
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"

//-------- プロトタイプ宣言
HRESULT InitShader();	// 初期化
void BeginShader(int nTechnique = 0);	// シェーダ開始
void SetCameraShader(LPD3DXVECTOR3 pCamera, LPD3DXMATRIX pView, LPD3DXMATRIX pProj);
void SetLightShader(LPD3DXVECTOR3 pLight);
void SetWorldMatrixShader(LPD3DXMATRIX pWorld);
void SetMaterialShader(D3DMATERIAL9* pMaterial, LPDIRECT3DTEXTURE9 pTexture);
//void DrawShaderSpotLight(MODEL* pModel,D3DXMATRIX* pMatrix,MODELINFO *pModelInfo);
void EndShader();		// シェーダ終了
void FinShader();		// 解放
void SetTexture(D3DXHANDLE hTexture, LPDIRECT3DTEXTURE9 pTexture);

#endif

//=======================================================================================
//	End of File
//=======================================================================================