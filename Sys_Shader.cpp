//=======================================================================================
//
//	�V�F�[�_����
//
//=======================================================================================

//-------- �w�b�_
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include "Sys_Shader.h"
#include "Sys_Global_Variable.h"


//-------- �萔
#define PATH_FXTEST		_T("data/Sys_File/MultiLight.fx")
#define MAX_TECHNIQUE	4

//-------- �O���[�o���ϐ�
LPD3DXEFFECT	g_pFX;		// �G�t�F�N�g �I�u�W�F�N�g
D3DXHANDLE		g_hMatWVP;	// ���[���h�~�r���[�~�ˉe
D3DXHANDLE		g_hMatW;	// ���[���h �}�g���b�N�X
D3DXHANDLE		g_hViewProj;
D3DXHANDLE		g_hCamera;	// ���_���W
D3DXHANDLE		g_hLight;	// �����x�N�g��
D3DXHANDLE		g_hTexValid;// �p�����[�^�n���h��
D3DXHANDLE		g_hDiffuse;	// (�}�e���A��)�g�U�F
D3DXHANDLE		g_hSpecular;// (�}�e���A��)���ʔ��ːF
D3DXHANDLE		g_hPower;	// (�}�e���A��)���ʔ��ˎw��
D3DXHANDLE		g_hAmbient;	// (�}�e���A��)���F
D3DXHANDLE		g_hTexture;	// �e�N�X�`��
D3DXHANDLE		g_hTexEnable;// �e�N�X�`���L��
//D3DXHANDLE		g_hTech[MAX_TECHNIQUE];	// �e�N�j�b�N

D3DXHANDLE				g_hLightPos;				// �p�����[�^�n���h��
D3DXHANDLE				g_hLightDir;				// �p�����[�^�n���h��
D3DXHANDLE				g_hLightCol;

static D3DXVECTOR3	g_vLight;
static D3DXVECTOR3	g_vCamera;
static D3DXMATRIX	g_mView;
static D3DXMATRIX	g_mProj;

//---------------------------------------------------------------------------------------
// �V�F�[�_������
//---------------------------------------------------------------------------------------
HRESULT InitShader()
{
	// �V�F�[�_�ǂݍ���
	HRESULT hr = D3DXCreateEffectFromFile(g_pD3DDevice,
		PATH_FXTEST, NULL, NULL, 0, NULL, &g_pFX, NULL);
	if (FAILED(hr)) {
		TCHAR szMsg[1024];
		_stprintf(szMsg, _T("�V�F�[�_(%s)�ǂݍ��݃G���["),
			PATH_FXTEST);
		MessageBox(g_hWnd, szMsg, _T("error"), MB_OK);
		return hr;
	}
	//// �n���h���擾
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
// �J�������ݒ�
//---------------------------------------------------------------------------------------
void SetCameraShader(LPD3DXVECTOR3 pCamera,
	LPD3DXMATRIX pView, LPD3DXMATRIX pProj)
{
	g_vCamera = *pCamera;
	g_mView = *pView;
	g_mProj = *pProj;
}

//---------------------------------------------------------------------------------------
// �����x�N�g���ݒ�
//---------------------------------------------------------------------------------------
void SetLightShader(LPD3DXVECTOR3 pLight)
{
	g_vLight = *pLight;
}

//---------------------------------------------------------------------------------------
// �V�F�[�_�J�n
//---------------------------------------------------------------------------------------
void BeginShader(int nTechnique)
{
	if (nTechnique < 0 || nTechnique >= MAX_TECHNIQUE) {
		nTechnique = 0;
	}
	// �e�N�j�b�N�ݒ�
	g_pFX->SetTechnique(g_pFX->GetTechnique(0));
	HRESULT hr = g_pFX->Begin(NULL, 0);
	// �p�X�J�n
	hr = g_pFX->BeginPass(0);
}

//---------------------------------------------------------------------------------------
// ���[���h�ϊ��s��ݒ�(&�V�F�[�_�֐ݒ�)
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
// �}�e���A���ݒ�(&�R�~�b�g)
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
// �V�F�[�_�I��
//---------------------------------------------------------------------------------------
void EndShader()
{
	// �p�X�I��
	g_pFX->EndPass();
	// �e�N�j�b�N�I��
	g_pFX->End();
}

//---------------------------------------------------------------------------------------
// �V�F�[�_���
//---------------------------------------------------------------------------------------
void FinShader()
{
	SAFE_RELEASE(g_pFX);
}

// �e�N�X�`���ݒ�
void SetTexture(D3DXHANDLE hTexture, LPDIRECT3DTEXTURE9 pTexture)
{
	g_pFX->SetTexture(hTexture, pTexture);
}
//---------------------------------------------------------------------------------------
// �V�F�[�_�`��
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
//		g_pFX->SetFloatArray(g_hLightPos,(float*)vLightPos, 3 * 1);	// �����ʒu�ݒ�
//		g_pFX->SetFloatArray(g_hLightDir,(float*)vLightDir, 3 * 1);	// ���������ݒ�
//		g_pFX->SetVectorArray(g_hLightCol, vLightCol, 1);
//		g_pFX->SetFloatArray("lightRag", fRange, 1);
//		g_pFX->SetMatrix(g_hMatW, pMatrix);							// ���[���h�}�g���N�X�ݒ�
//		g_pFX->SetMatrix(g_hViewProj, &((*g_matView) * (*g_pMatrixProjection)));			// �r���[�~�ˉe�}�g���b�N�X�ݒ�
//		g_pFX->SetFloatArray(g_hCamera, (float*)&g_vCamera, 3);		// ���_���W�ݒ�
//		g_pD3DDevice->SetTransform(D3DTS_WORLD, pMatrix);
//		g_pD3DDevice->SetTransform(D3DTS_VIEW, g_matView);
//		g_pD3DDevice->SetTransform(D3DTS_PROJECTION, g_pMatrixProjection);
//
//		// �T�u�Z�b�g���̕`��
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