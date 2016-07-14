//=======================================================================================
//
//	シェーダ処理
//
//=======================================================================================

//-------- ヘッダ
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include "Sys_Shader.h"
#include "Sys_Global_Variable.h"


//-------- 定数
#define PATH_FXTEST		_T("data/Sys_File/MultiLight.fx")
#define MAX_TECHNIQUE	4

//-------- グローバル変数
LPD3DXEFFECT	g_pFX;		// エフェクト オブジェクト
D3DXHANDLE		g_hMatWVP;	// ワールド×ビュー×射影
D3DXHANDLE		g_hMatW;	// ワールド マトリックス
D3DXHANDLE		g_hViewProj;
D3DXHANDLE		g_hCamera;	// 視点座標
D3DXHANDLE		g_hLight;	// 光源ベクトル
D3DXHANDLE		g_hTexValid;// パラメータハンドル
D3DXHANDLE		g_hDiffuse;	// (マテリアル)拡散色
D3DXHANDLE		g_hSpecular;// (マテリアル)鏡面反射色
D3DXHANDLE		g_hPower;	// (マテリアル)鏡面反射指数
D3DXHANDLE		g_hAmbient;	// (マテリアル)環境色
D3DXHANDLE		g_hTexture;	// テクスチャ
D3DXHANDLE		g_hTexEnable;// テクスチャ有無
//D3DXHANDLE		g_hTech[MAX_TECHNIQUE];	// テクニック

D3DXHANDLE				g_hLightPos;				// パラメータハンドル
D3DXHANDLE				g_hLightDir;				// パラメータハンドル
D3DXHANDLE				g_hLightCol;

static D3DXVECTOR3	g_vLight;
static D3DXVECTOR3	g_vCamera;
static D3DXMATRIX	g_mView;
static D3DXMATRIX	g_mProj;

//---------------------------------------------------------------------------------------
// シェーダ初期化
//---------------------------------------------------------------------------------------
HRESULT InitShader()
{
	// シェーダ読み込み
	HRESULT hr = D3DXCreateEffectFromFile(g_pD3DDevice,
		PATH_FXTEST, NULL, NULL, 0, NULL, &g_pFX, NULL);
	if (FAILED(hr)) {
		TCHAR szMsg[1024];
		_stprintf(szMsg, _T("シェーダ(%s)読み込みエラー"),
			PATH_FXTEST);
		MessageBox(g_hWnd, szMsg, _T("error"), MB_OK);
		return hr;
	}
	//// ハンドル取得
	//struct _param 
	//{
	//	LPCSTR		pszName;
	//	D3DXHANDLE*	pHandle;
	//} param[] = {
	//	{"WORLDVIEWPROJECTION", &g_hMatWVP},
	//	{"WORLD",				&g_hMatW},
	//	{"CAMERAPOSITION",		&g_hCamera},
	//	{"MATERIALDIFFUSE",		&g_hDiffuse},
	//	{"MATERIALSPECULAR",	&g_hSpecular},
	//	{"MATERIALPOWER",		&g_hPower},
	//	{"MATERIALAMBIENT",		&g_hAmbient},
	//	{"MATERIALTEXTURE",		&g_hTexture},
	//	{"MATERIALTEXTUREVALID", &g_hTexEnable},

	//	{"lightPos", &g_hLightPos},
	//	{"lightDir", &g_hLightDir},
	//	{"lightCol", &g_hLightCol},
	//};

	g_hMatW = g_pFX->GetParameterBySemantic(0, "WORLD");
	g_hViewProj = g_pFX->GetParameterBySemantic(0, "VIEWPROJECTION");
	g_hTexture = g_pFX->GetParameterBySemantic(0, "MATERIALTEXTURE");
	g_hTexValid = g_pFX->GetParameterBySemantic(0, "MATERIALTEXTUREVALID");
	g_hDiffuse = g_pFX->GetParameterBySemantic(0, "MATERIALDIFFUSE");
	g_hAmbient = g_pFX->GetParameterBySemantic(0, "MATERIALAMBIENT");
	g_hSpecular = g_pFX->GetParameterBySemantic(0, "MATERIALSPECULAR");
	g_hPower = g_pFX->GetParameterBySemantic(0, "MATERIALPOWER");
	g_hCamera = g_pFX->GetParameterBySemantic(0, "CAMERAPOSITION");
	g_hLightPos = g_pFX->GetParameterByName(0, "lightPos");
	g_hLightDir = g_pFX->GetParameterByName(0, "lightDir");
	g_hLightCol = g_pFX->GetParameterByName(0, "lightCol");

	return hr;
}

//---------------------------------------------------------------------------------------
// カメラ情報設定
//---------------------------------------------------------------------------------------
void SetCameraShader(LPD3DXVECTOR3 pCamera,
	LPD3DXMATRIX pView, LPD3DXMATRIX pProj)
{
	g_vCamera = *pCamera;
	g_mView = *pView;
	g_mProj = *pProj;
}

//---------------------------------------------------------------------------------------
// 光源ベクトル設定
//---------------------------------------------------------------------------------------
void SetLightShader(LPD3DXVECTOR3 pLight)
{
	g_vLight = *pLight;
}

//---------------------------------------------------------------------------------------
// シェーダ開始
//---------------------------------------------------------------------------------------
void BeginShader(int nTechnique)
{
	if (nTechnique < 0 || nTechnique >= MAX_TECHNIQUE) {
		nTechnique = 0;
	}
	// テクニック設定
	g_pFX->SetTechnique(g_pFX->GetTechnique(0));
	HRESULT hr = g_pFX->Begin(NULL, 0);
	// パス開始
	hr = g_pFX->BeginPass(0);
}

//---------------------------------------------------------------------------------------
// ワールド変換行列設定(&シェーダへ設定)
//---------------------------------------------------------------------------------------
void SetWorldMatrixShader(LPD3DXMATRIX pWorld)
{
	//g_pFX->SetFloatArray(g_hLight, &g_vLight.x, g_nLightCount);
	//g_pFX->SetFloatArray(g_hCamera, &g_vCamera.x, 3);

	//g_pFX->SetMatrix(g_hMatWVP,&(*pWorld * g_mView * g_mProj));
	//g_pFX->SetMatrix(g_hMatW, pWorld);
	//
	//g_pFX->SetVectorArray(g_hLightCol, g_vLightCol, g_nLightCount);


}

//---------------------------------------------------------------------------------------
// マテリアル設定(&コミット)
//---------------------------------------------------------------------------------------
void SetMaterialShader(D3DMATERIAL9* pMaterial,
	LPDIRECT3DTEXTURE9 pTexture)
{
	if (pMaterial) 
	{
		g_pFX->SetVector(g_hDiffuse,
			(LPD3DXVECTOR4)&pMaterial->Diffuse);
		g_pFX->SetVector(g_hSpecular,
			(LPD3DXVECTOR4)&pMaterial->Specular);
		g_pFX->SetFloat(g_hPower, pMaterial->Power);
		g_pFX->SetVector(g_hAmbient,
			(LPD3DXVECTOR4)&pMaterial->Ambient);
	}
	if (pTexture) {
		g_pFX->SetTexture(g_hTexture, pTexture);
		g_pFX->SetBool(g_hTexEnable, TRUE);
	} else {
		g_pFX->SetBool(g_hTexEnable, FALSE);
	}
	g_pFX->CommitChanges();
}

//---------------------------------------------------------------------------------------
// シェーダ終了
//---------------------------------------------------------------------------------------
void EndShader()
{
	// パス終了
	g_pFX->EndPass();
	// テクニック終了
	g_pFX->End();
}

//---------------------------------------------------------------------------------------
// シェーダ解放
//---------------------------------------------------------------------------------------
void FinShader()
{
	SAFE_RELEASE(g_pFX);
}

// テクスチャ設定
void SetTexture(D3DXHANDLE hTexture, LPDIRECT3DTEXTURE9 pTexture)
{
	g_pFX->SetTexture(hTexture, pTexture);
}
//---------------------------------------------------------------------------------------
// シェーダ描画
//---------------------------------------------------------------------------------------
//void DrawShaderSpotLight(MODEL* pModel,D3DXMATRIX* pMatrix,MODELINFO *pModelInfo)
//{
//
//		D3DVECTOR	vLightPos[1];
//		D3DVECTOR	vLightDir[1];
//		D3DXVECTOR4 vLightCol[1];
//		float		fRange[1];
//		int nLight = 0;
//		//for (int i = 0; i < 1; i++) 
//		{
//			vLightPos[nLight]	= g_pMgtLightShader->m_pCLight[2]->m_pLight->Position;
//			vLightDir[nLight]	= g_pMgtLightShader->m_pCLight[2]->m_pLight->Direction;
//			vLightCol[nLight].x	= g_pMgtLightShader->m_pCLight[2]->m_pLight->Diffuse.r;
//			vLightCol[nLight].y	= g_pMgtLightShader->m_pCLight[2]->m_pLight->Diffuse.g;
//			vLightCol[nLight].z	= g_pMgtLightShader->m_pCLight[2]->m_pLight->Diffuse.b;
//			vLightCol[nLight].w	= g_pMgtLightShader->m_pCLight[2]->m_pLight->Diffuse.a;
//			fRange[nLight]		= g_pMgtLightShader->m_pCLight[2]->m_pLight->Range;
//			nLight++;
//
//			//vLightPos[nLight]	= g_pMgtLightShader->m_pCLight[3]->m_pLight->Position;
//			//vLightDir[nLight]	= g_pMgtLightShader->m_pCLight[3]->m_pLight->Direction;
//			//vLightCol[nLight].x	= g_pMgtLightShader->m_pCLight[3]->m_pLight->Diffuse.r;
//			//vLightCol[nLight].y	= g_pMgtLightShader->m_pCLight[3]->m_pLight->Diffuse.g;
//			//vLightCol[nLight].z	= g_pMgtLightShader->m_pCLight[3]->m_pLight->Diffuse.b;
//			//vLightCol[nLight].w	= g_pMgtLightShader->m_pCLight[3]->m_pLight->Diffuse.a;
//			//fRange[nLight]		= g_pMgtLightShader->m_pCLight[3]->m_pLight->Range;
//		}
//
//
//		g_pFX->SetFloatArray(g_hLightPos,(float*)vLightPos, 3 * 1);	// 光源位置設定
//		g_pFX->SetFloatArray(g_hLightDir,(float*)vLightDir, 3 * 1);	// 光源方向設定
//		g_pFX->SetVectorArray(g_hLightCol, vLightCol, 1);
//		g_pFX->SetFloatArray("lightRag", fRange, 1);
//		g_pFX->SetMatrix(g_hMatW, pMatrix);							// ワールドマトリクス設定
//		g_pFX->SetMatrix(g_hViewProj, &((*g_matView) * (*g_pMatrixProjection)));			// ビュー×射影マトリックス設定
//		g_pFX->SetFloatArray(g_hCamera, (float*)&g_vCamera, 3);		// 視点座標設定
//		g_pD3DDevice->SetTransform(D3DTS_WORLD, pMatrix);
//		g_pD3DDevice->SetTransform(D3DTS_VIEW, g_matView);
//		g_pD3DDevice->SetTransform(D3DTS_PROJECTION, g_pMatrixProjection);
//
//		// サブセット毎の描画
//		for (DWORD i = 0; i < pModelInfo->dwNumMaterial; i++) 
//		{
//			g_pFX->SetVector(g_hDiffuse, (LPD3DXVECTOR4)&pModelInfo->pMaterial[i].Diffuse);
//			g_pFX->SetVector(g_hAmbient, (LPD3DXVECTOR4)&pModelInfo->pMaterial[i].Ambient);
//			g_pFX->SetVector(g_hSpecular, (LPD3DXVECTOR4)&pModelInfo->pMaterial[i].Specular);
//			
//			g_pFX->SetFloat(g_hPower, pModelInfo->pMaterial[i].Power);
//			g_pFX->SetTexture(g_hTexture, pModelInfo->ppTexture[i]);
//			g_pFX->SetBool(g_hTexValid, pModelInfo->ppTexture[i] != NULL);
//			g_pFX->CommitChanges();
//			pModelInfo->pMesh->DrawSubset(i);
//
//		}
//
//}
//=======================================================================================
//	End of File
//=======================================================================================