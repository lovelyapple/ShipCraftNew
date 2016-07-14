#include "Sys_C_Model.h"
c_Model::c_Model(LPCSTR File)
{
	D3DM_INIT(m_matrix);
	D3DV_INIT(m_vPos);
	D3DV_INIT(m_vAngle);
	
	m_pModel = new MODEL;
	ZeroMemory(m_pModel,sizeof(m_pModel));
	m_pszFName = File;
}

c_Model::c_Model()
{
	D3DM_INIT(m_matrix);
	D3DV_INIT(m_vPos);
	D3DV_INIT(m_vAngle);
	m_pModel = new MODEL;
	ZeroMemory(m_pModel,sizeof(m_pModel));
}
c_Model::c_Model(LPCSTR File,D3DXVECTOR3 pos)
{
	D3DM_INIT(m_matrix);
	D3DV_INIT(m_vPos);
	D3DV_INIT(m_vAngle);
	m_pszFName	= File;
	m_vPos		= pos;
	m_pModel = new MODEL;
	ZeroMemory(m_pModel,sizeof(m_pModel));
	HRESULT hr = (Init_LoadModel());
	if(FAILED(hr))
	{
		delete m_pModel;
		SAFE_DELETE(m_pModel);
		
		m_pszFName = ERROR_MODEL_FILE;
		m_pModel = new MODEL;
		hr = (Init_LoadModel());
		if(FAILED(hr))
		{
			delete m_pModel;
			SAFE_DELETE(m_pModel);
		}

	}
}
c_Model::~c_Model()
{

}
void c_Model::SetFileName(LPCSTR FileName)
{
	this->m_pszFName = FileName;
}

HRESULT c_Model:: Init_LoadModel(void)
{
	LPD3DXBUFFER	pMtrlBuff = NULL;
	TCHAR			szDir[_MAX_DIR];
	TCHAR			szSaveDir[_MAX_DIR];

	HRESULT hr = D3DXLoadMeshFromX(m_pszFName,	// ファイル名
		D3DXMESH_SYSTEMMEM,						// 常に同じ指定
		g_pD3DDevice,							// Direct3Dデバイス
		NULL,									// 常にNULL
		&pMtrlBuff,								// マテリアルバッファ
		NULL,									// 常にNULL
		&m_pModel->dwNumMtrl,					// マテリアル数
		&m_pModel->pMesh);						// メッシュオブジェクト
	if (FAILED(hr)) 
	{
		if (hr == D3DERR_INVALIDCALL) {
			hr = D3DERR_INVALIDCALL;
		} else if (hr == E_OUTOFMEMORY) {
			hr = D3DERR_INVALIDCALL;
		}
		MessageBox(g_hWnd, _T("モデルロード失敗,デフォールトモデル使用"),
			_T("グラフィックス初期化失敗"), 
			MB_OK | MB_ICONERROR);

		m_pszFName = ERROR_MODEL_FILE;
		hr = D3DXLoadMeshFromX(m_pszFName,	// ファイル名
		D3DXMESH_SYSTEMMEM,						// 常に同じ指定
		g_pD3DDevice,							// Direct3Dデバイス
		NULL,									// 常にNULL
		&pMtrlBuff,								// マテリアルバッファ
		NULL,									// 常にNULL
		&m_pModel->dwNumMtrl,					// マテリアル数
		&m_pModel->pMesh);						// メッシュオブジェクト
		if (FAILED(hr)) 
		{
			if (hr == D3DERR_INVALIDCALL) {
				hr = D3DERR_INVALIDCALL;
			} else if (hr == E_OUTOFMEMORY) {
				hr = D3DERR_INVALIDCALL;
			}
			MessageBox(g_hWnd, _T("デフォールトモデルロード失敗"),
				_T("グラフィックス初期化失敗"), 
				MB_OK | MB_ICONERROR);
		}
		return hr;
	}
	// 法線が無い場合は強制的に追加
	LPD3DXMESH pMeshWk;
	DWORD dwFVF = m_pModel->pMesh->GetFVF();
	if ((dwFVF & D3DFVF_NORMAL) == 0) 
	{
		hr = m_pModel->pMesh->CloneMeshFVF(m_pModel->pMesh->GetOptions(),
			dwFVF | D3DFVF_NORMAL, g_pD3DDevice, &pMeshWk);

		if (SUCCEEDED(hr))
		{
			D3DXComputeNormals(pMeshWk, NULL);
			m_pModel->pMesh->Release();
			m_pModel->pMesh = pMeshWk;
		}
	}
// 属性テーブル取得
	hr = m_pModel->pMesh->GetAttributeTable(NULL, &m_pModel->dwNumAttr);
	if (FAILED(hr)) {
		SAFE_RELEASE(pMtrlBuff);
		SAFE_RELEASE(m_pModel->pMesh);
		return hr;
	}
	m_pModel->pAttr = new D3DXATTRIBUTERANGE[m_pModel->dwNumAttr];
	hr = m_pModel->pMesh->GetAttributeTable(m_pModel->pAttr, &m_pModel->dwNumAttr);

	// 頂点バッファ固定
	LPD3DXVECTOR3 pVtx;
	m_pModel->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pVtx);
	// 境界ボックス生成
	D3DXVECTOR3 vMin = *pVtx;
	D3DXVECTOR3 vMax = vMin;
	DWORD dwVtx = m_pModel->pMesh->GetNumVertices();
	DWORD dwStroke = m_pModel->pMesh->GetNumBytesPerVertex();
	LPD3DXVECTOR3 pV = pVtx;
	for (DWORD i = 0; i < dwVtx; i++) {
		if (vMin.x > pV->x) vMin.x = pV->x;
		if (vMin.y > pV->y) vMin.y = pV->y;
		if (vMin.z > pV->z) vMin.z = pV->z;
		if (vMax.x < pV->x) vMax.x = pV->x;
		if (vMax.y < pV->y) vMax.y = pV->y;
		if (vMax.z < pV->z) vMax.z = pV->z;
		pV = (LPD3DXVECTOR3)((LPBYTE)pV + dwStroke);
	}
	m_pModel->vBBox = (vMax - vMin) / 2.0f;
	m_pModel->vCenter = (vMax + vMin) / 2.0f;
	// 境界球生成
	m_pModel->fRadius = 0.0f;
	float fR;
	pV = pVtx;
	for (DWORD i = 0; i < dwVtx; i++)
	{
		fR = D3DXVec3Length(&(*pV - m_pModel->vCenter));
		if (m_pModel->fRadius < fR)
			m_pModel->fRadius = fR;
		pV = (LPD3DXVECTOR3)((LPBYTE)pV + dwStroke);
	}
	// 頂点バッファ解放
	m_pModel->pMesh->UnlockVertexBuffer();

	// カレントディレクトリをXファイルのあるフォルダに移動
	_tsplitpath(m_pszFName, NULL, szDir, NULL, NULL);
	if (szDir[0])
	{	// フォルダ相対指定あり?
		GetCurrentDirectory(_countof(szSaveDir), szSaveDir);
		SetCurrentDirectory(szDir);
	}

	// マテリアルの抽出
	D3DXMATERIAL* pMtrl = (D3DXMATERIAL*)pMtrlBuff->GetBufferPointer();
	m_pModel->pMtrl = new D3DMATERIAL9[m_pModel->dwNumMtrl];
	m_pModel->pTexture = new LPDIRECT3DTEXTURE9[m_pModel->dwNumMtrl];

	for (DWORD i = 0; i < m_pModel->dwNumMtrl; i++) 
	{
		m_pModel->pMtrl[i] = pMtrl[i].MatD3D;
		// Xファイルには環境色が無い、拡散色で上書きしておく.
		m_pModel->pMtrl[i].Ambient = m_pModel->pMtrl[i].Diffuse;

		m_pModel->pTexture[i] = NULL;
		if (pMtrl[i].pTextureFilename && pMtrl[i].pTextureFilename[0]) 
		{
			hr = D3DXCreateTextureFromFileA(g_pD3DDevice, pMtrl[i].pTextureFilename, &m_pModel->pTexture[i]);
			if (FAILED(hr)) 
			{
				break;
			}
		}
	}

	// カレントディレクトリを元に戻す
	if (szDir[0]) 
	{	// フォルダ相対指定あり?
		SetCurrentDirectory(szSaveDir);
	}

	pMtrlBuff->Release();
	return hr;
}
void c_Model::ReleaseModel(void)
{
	if (m_pModel->pTexture) 
	{
		for (DWORD i = 0; i < m_pModel->dwNumMtrl; i++)
		{
			SAFE_RELEASE(m_pModel->pTexture[i]);
		}
	}
	SAFE_DELETE_ARRAY(m_pModel->pTexture);
	SAFE_DELETE_ARRAY(m_pModel->pMtrl);
	SAFE_RELEASE(m_pModel->pMesh);
}

void c_Model::UpdateModel(void)
{
	D3DM_INIT(m_matrix);
	D3DXMATRIX matRot, matMove;
	D3DXMatrixRotationYawPitchRoll(&matRot, 
								m_vAngle.y, 
								m_vAngle.x,
								m_vAngle.z);
	D3DXMatrixRotationY(&matRot,m_vAngle.y);
	D3DXMatrixTranslation(&matMove, 
								m_vPos.x, 
								m_vPos.y, 
								m_vPos.z);
	D3DXMatrixMultiply(&m_matrix, &matRot, &matMove);
}
void c_Model:: DrawModel(void)
{
	if(m_pModel)
	{
		// ワールド変換設定
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matrix);

		// サブセット毎の描画
		for (DWORD i = 0; i < m_pModel->dwNumAttr; i++) 
		{
			DWORD id = m_pModel->pAttr[i].AttribId;
			g_pD3DDevice->SetMaterial(&m_pModel->pMtrl[id]);
			g_pD3DDevice->SetTexture(0, m_pModel->pTexture[id]);
			m_pModel->pMesh->DrawSubset(id);
		}
	}
}
void c_Model::UninitModel(void)
{
	ReleaseModel();
}
D3DXMATRIX* c_Model::GetModelMatrix(void)
{
	return &m_matrix;
}
D3DXVECTOR3* c_Model::GetModelPos(void)
{
	return &m_vPos;
}

