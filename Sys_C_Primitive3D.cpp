//============================================================================
//Primitive2D
//============================================================================
//-----------------------------------
//システムインクルード
#include "Sys_C_Primitive3D.h"
c_Primitive3D::c_Primitive3D()
{
	Reset_Primitive();
}
c_Primitive3D::c_Primitive3D(LPCSTR fzName)
{
	Reset_Primitive();
	m_pszFName		= fzName;
}
void	c_Primitive3D::SetFileName(LPCSTR fzName)
{
	m_pszFName = fzName;
}
c_Primitive3D::~c_Primitive3D()
{
		Uninit_Primitive();
}
void c_Primitive3D::Reset_Primitive(void)
{
	D3DV_INIT(m_vPos);
	D3DV_INIT(m_vRot);
	D3DV_INIT(m_vOblique[0]);
	D3DV_INIT(m_vOblique[1]);
	D3DM_INIT(m_mMatrix);
	m_bWatchCamera	= false;
	m_bUReversal	= false;
	m_pszFName		= FILE_NAME_DEAULT_PRIMITIVE;
	m_pD3DVertexBuffer	= NULL;
	m_pD3DTexture		= NULL;
	m_vSize.x			= 1.0f;
	m_vSize.y			= 1.0f;
	m_vSize.z			= 0.0f;
	m_nRecFrameU		= 0;
	m_nRecFrameV		= 0;
	m_nMaxFrameV		= 1;
	for(int v = 0; v  < MAX_V_FRAME; v++)
	{
		m_nMaxFrameU[v] = 1;
		m_nFrameUPerTimt[v] = 1;
	}

}
//===============================================================================
//Primitiveの基本処理
//===============================================================================
HRESULT c_Primitive3D::Init_Primitive()
{
	DVERTEX_PRIMITIVE*	VBuffer;								// 頂点バッファへのポインタ
	// 頂点バッファ作成
	if (FAILED(g_pD3DDevice->CreateVertexBuffer(sizeof(DVERTEX_PRIMITIVE) * 4, 0, 0, D3DPOOL_DEFAULT,
															&m_pD3DVertexBuffer, NULL))) {
		MessageBox(g_hWnd, _T("頂点バッファオブジェクトの作成に失敗しました"), m_pszFName, MB_OK | MB_ICONERROR);
		return E_FAIL;
	}
	//-------- ここからテクスチャロード処理
	// テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, m_pszFName, &m_pD3DTexture))) 
	{
		MessageBox(g_hWnd, _T("テクスチャオブジェクトの作成に失敗しました,デフォールトを使用"), _T("error"), 
			MB_OK | MB_ICONERROR);
		if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, m_pszFName, &m_pD3DTexture))) 
		{
			MessageBox(g_hWnd, _T("デフォールトテクスチャオブジェクトの作成に失敗しました,"), _T("error"), 
				MB_OK | MB_ICONERROR);
			return E_FAIL;
		}
		
	}
	
	// 頂点バッファに値をセット
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("頂点バッファのロックに失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		VBuffer[0].x  =  -2.0f;	VBuffer[0].y  =  4.0f;	VBuffer[0].z  =   0.0f;	// 頂点０
		VBuffer[0].nx =    0.0f;	VBuffer[0].ny =   0.0f;	VBuffer[0].nz =  -1.0f;
		VBuffer[0].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[0].tu  =   0.0f;	VBuffer[0].tv  =  0.0f;
		
		VBuffer[1].x  =   2.0f;	VBuffer[1].y  =  4.0f;	VBuffer[1].z  =   0.0f;	// 頂点１
		VBuffer[1].nx =    0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;
		VBuffer[1].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[1].tu  =   1.0f;	VBuffer[1].tv  =  0.0f;

		VBuffer[2].x  =  -2.0f;	VBuffer[2].y  =   0.0f;	VBuffer[2].z  =   0.0f;	// 頂点3
		VBuffer[2].nx =    0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;
		VBuffer[2].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[2].tu  =    0.0f;	VBuffer[2].tv  =  1.0f;

		VBuffer[3].x  =   2.0f;	VBuffer[3].y  =   0.0f;	VBuffer[3].z  =   0.0f;	// 頂点２
		VBuffer[3].nx =    0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;
		VBuffer[3].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[3].tu  =    1.0f;	VBuffer[3].tv  =  1.0f;


		m_pD3DVertexBuffer->Unlock();					// バッファをアンロック
	}
	return S_OK;
}
HRESULT c_Primitive3D::CreatePrimitiveBuffOnly(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// 頂点バッファへのポインタ
	// 頂点バッファ作成
	if (FAILED(g_pD3DDevice->CreateVertexBuffer(sizeof(DVERTEX_PRIMITIVE) * 4, 0, 0, D3DPOOL_DEFAULT,
															&m_pD3DVertexBuffer, NULL))) {
		MessageBox(g_hWnd, _T("頂点バッファオブジェクトの作成に失敗しました"), m_pszFName, MB_OK | MB_ICONERROR);
		return E_FAIL;
	}
	// 頂点バッファに値をセット
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("頂点バッファのロックに失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		VBuffer[0].x  =  -2.0f;	VBuffer[0].y  =  4.0f;	VBuffer[0].z  =   0.0f;	// 頂点０
		VBuffer[0].nx =    0.0f;	VBuffer[0].ny =   0.0f;	VBuffer[0].nz =  -1.0f;
		VBuffer[0].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[0].tu  =   0.0f;	VBuffer[0].tv  =  0.0f;
		
		VBuffer[1].x  =   2.0f;	VBuffer[1].y  =  4.0f;	VBuffer[1].z  =   0.0f;	// 頂点１
		VBuffer[1].nx =    0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;
		VBuffer[1].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[1].tu  =   1.0f;	VBuffer[1].tv  =  0.0f;

		VBuffer[2].x  =  -2.0f;	VBuffer[2].y  =   0.0f;	VBuffer[2].z  =   0.0f;	// 頂点3
		VBuffer[2].nx =    0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;
		VBuffer[2].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[2].tu  =    0.0f;	VBuffer[2].tv  =  1.0f;

		VBuffer[3].x  =   2.0f;	VBuffer[3].y  =   0.0f;	VBuffer[3].z  =   0.0f;	// 頂点２
		VBuffer[3].nx =    0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;
		VBuffer[3].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[3].tu  =    1.0f;	VBuffer[3].tv  =  1.0f;


		m_pD3DVertexBuffer->Unlock();					// バッファをアンロック
	}
	return S_OK;
}

void c_Primitive3D::Uninit_Primitive(void)
{
	if(m_pD3DVertexBuffer)
	{
		m_pD3DVertexBuffer->Release();
		m_pD3DVertexBuffer = NULL;
	}
	if(m_pD3DTexture)
	{
		m_pD3DTexture->Release();
		m_pD3DTexture = NULL;
	}

}
void c_Primitive3D::Update_PrimitiveNormal(void)
{
	D3DXMATRIX	matRotate;		// 回転マトリックス
	D3DXMATRIX	matTrans;		// 平行移動マトリックス
	D3DXMATRIX*	pmatInv;
	D3DXVECTOR3 vDir;
	D3DM_INIT(m_mMatrix);

	D3DXMatrixRotationYawPitchRoll(&matRotate,m_vRot.y,m_vRot.x,m_vRot.z);	// 回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans,m_vPos.x,m_vPos.y,m_vPos.z);	// 平行移動マトリックスを生成

	m_mMatrix = matRotate * matTrans;
	if(m_bWatchCamera)
	{
		pmatInv = &m_mMatrix;
		float _41 = m_mMatrix._41;
		float _42 = m_mMatrix._42;
		float _43 = m_mMatrix._43;
		D3DXMatrixInverse(pmatInv, NULL, g_matView);
		pmatInv->_41 = _41;  //オフセットを切る（回転行列だけにして）
		pmatInv->_42 = _42;
		pmatInv->_43 = _43;
	}
	SetVerTexBuff();
}


void c_Primitive3D::SetWatchCamera(bool input)
{
	m_bWatchCamera = input;
}
void c_Primitive3D::SetPos(D3DXVECTOR3 Pos)
{
	m_vPos = Pos;
}
void c_Primitive3D::SetRot(D3DXVECTOR3 Rot)
{
	m_vRot = Rot;
}
void c_Primitive3D::SetAlpha(float fAlpha)
{	
	this->m_fAlpha = fAlpha;
}
void c_Primitive3D::SetReversal(bool bReversa)
{
	m_bUReversal = bReversa;
}

void c_Primitive3D::SetOblique(D3DXVECTOR3* input)
{
	m_vOblique[0] = input[0];
	m_vOblique[1] = input[1];
}
void c_Primitive3D::Update_PrimitiveMatrixOnly(void)
{
	D3DXMATRIX	matRotate;		// 回転マトリックス
	D3DXMATRIX	matTrans;		// 平行移動マトリックス
	D3DXMATRIX*	pmatInv;
	D3DXVECTOR3 vDir;
	D3DM_INIT(m_mMatrix);

	D3DXMatrixRotationYawPitchRoll(&matRotate,m_vRot.y,m_vRot.x,m_vRot.z);	// 回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans,m_vPos.x,m_vPos.y,m_vPos.z);	// 平行移動マトリックスを生成

	m_mMatrix = matRotate * matTrans;
	if(m_bWatchCamera)
	{
		pmatInv = &m_mMatrix;
		float _41 = m_mMatrix._41;
		float _42 = m_mMatrix._42;
		float _43 = m_mMatrix._43;
		D3DXMatrixInverse(pmatInv, NULL, g_matView);
		pmatInv->_41 = _41;  //オフセットを切る（回転行列だけにして）
		pmatInv->_42 = _42;
		pmatInv->_43 = _43;
	}
}
void c_Primitive3D::SetVerTexBuff(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// 頂点バッファへのポインタ	// 頂点バッファに値をセット
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("頂点バッファのロックに失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		VBuffer[0].x  =	 -m_vSize.x;	// 頂点０
		VBuffer[0].y  =   m_vSize.y;		
		VBuffer[0].z  =   0.0f;	

		VBuffer[1].x  =   m_vSize.x;	// 頂点１
		VBuffer[1].y  =   m_vSize.y;	
		VBuffer[1].z  =   0.0f;

		VBuffer[2].x  =  -m_vSize.x; // 頂点3
		VBuffer[2].y  =  -m_vSize.y;	
		VBuffer[2].z  =   0.0f;

		VBuffer[3].x  =   m_vSize.x; // 頂点２	
		VBuffer[3].y  =  -m_vSize.y;	
		VBuffer[3].z  =   0.0f;

		VBuffer[0].nx =   0.0f;	VBuffer[0].ny =   0.0f;	VBuffer[0].nz =  -1.0f;
		VBuffer[1].nx =   0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;
		VBuffer[2].nx =   0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;		
		VBuffer[3].nx =   0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;

		VBuffer[0].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[1].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[2].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[3].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
	}
}
void c_Primitive3D::SetVerTexBuffSizeOblique(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// 頂点バッファへのポインタ	// 頂点バッファに値をセット
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("頂点バッファのロックに失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		VBuffer[0].x  =	  m_vOblique[0].x + 0.0f;		// 頂点０
		VBuffer[0].y  =   m_vOblique[0].y + m_vSize.y;		
		VBuffer[0].z  =   0.0f;	

		VBuffer[1].x  =   m_vOblique[0].x + m_vSize.x;	// 頂点１
		VBuffer[1].y  =   m_vOblique[0].y + m_vSize.y;	
		VBuffer[1].z  =   0.0f;

		VBuffer[2].x  =   m_vOblique[1].x + 0.0f;		// 頂点3
		VBuffer[2].y  =   m_vOblique[1].y - m_vSize.y;	
		VBuffer[2].z  =   0.0f;

		VBuffer[3].x  =   m_vOblique[1].x + m_vSize.x;	// 頂点２	
		VBuffer[3].y  =   m_vOblique[1].y - m_vSize.y;	
		VBuffer[3].z  =   0.0f;


	}
}
void c_Primitive3D::SetVerTexBuffSize(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// 頂点バッファへのポインタ	// 頂点バッファに値をセット
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("頂点バッファのロックに失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		VBuffer[0].x  =	 -m_vSize.x;	// 頂点０
		VBuffer[0].y  =   m_vSize.y;		
		VBuffer[0].z  =   0.0f;	

		VBuffer[1].x  =   m_vSize.x;	// 頂点１
		VBuffer[1].y  =   m_vSize.y;	
		VBuffer[1].z  =   0.0f;

		VBuffer[2].x  =  -m_vSize.x; // 頂点3
		VBuffer[2].y  =  -m_vSize.y;	
		VBuffer[2].z  =   0.0f;

		VBuffer[3].x  =   m_vSize.x; // 頂点２	
		VBuffer[3].y  =  -m_vSize.y;	
		VBuffer[3].z  =   0.0f;
	}
}
void c_Primitive3D::SetVerTexBuffUV(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// 頂点バッファへのポインタ	// 頂点バッファに値をセット
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("頂点バッファのロックに失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		float SizeU = 1.0f / m_nMAXUVFrame[m_nRecFrameV];
		float SizeV = 1.0f / m_nMaxFrameV;
		VBuffer[0].tu =	  SizeU * m_nRecFrameU;	
		VBuffer[0].tv =   SizeV * m_nRecFrameV;	

		VBuffer[1].tu =   SizeU * m_nRecFrameU + SizeU;	
		VBuffer[1].tv =   SizeV * m_nRecFrameV;	

		VBuffer[2].tu =   SizeU * m_nRecFrameU;	
		VBuffer[2].tv =   SizeV * m_nRecFrameV + SizeV;

		VBuffer[3].tu =   SizeU * m_nRecFrameU + SizeU;	
		VBuffer[3].tv =   SizeV * m_nRecFrameV + SizeV;

	}
}
void c_Primitive3D::SetVerTexBuffUVReversa(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// 頂点バッファへのポインタ	// 頂点バッファに値をセット
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("頂点バッファのロックに失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		float SizeU = 1.0f / m_nMAXUVFrame[m_nRecFrameV];
		float SizeV = 1.0f / m_nMaxFrameV;
		if(!m_bUReversal)
		{
			VBuffer[0].tu =	  SizeU * m_nRecFrameU;	
			VBuffer[0].tv =   SizeV * m_nRecFrameV;	

			VBuffer[1].tu =   SizeU * m_nRecFrameU + SizeU;	
			VBuffer[1].tv =   SizeV * m_nRecFrameV;	

			VBuffer[2].tu =   SizeU * m_nRecFrameU;	
			VBuffer[2].tv =   SizeV * m_nRecFrameV + SizeV;

			VBuffer[3].tu =   SizeU * m_nRecFrameU + SizeU;	
			VBuffer[3].tv =   SizeV * m_nRecFrameV + SizeV;
		}
		else
		{
			VBuffer[0].tu =	  -SizeU * m_nRecFrameU;	
			VBuffer[0].tv =    SizeV * m_nRecFrameV;	

			VBuffer[1].tu =   -SizeU * m_nRecFrameU - SizeU;	
			VBuffer[1].tv =    SizeV * m_nRecFrameV;	

			VBuffer[2].tu =   -SizeU * m_nRecFrameU;	
			VBuffer[2].tv =    SizeV * m_nRecFrameV + SizeV;

			VBuffer[3].tu =   -SizeU * m_nRecFrameU - SizeU;	
			VBuffer[3].tv =    SizeV * m_nRecFrameV + SizeV;
		}

	}
}
void c_Primitive3D::SetVerTexBuffAlpha(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// 頂点バッファへのポインタ	// 頂点バッファに値をセット
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("頂点バッファのロックに失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		VBuffer[0].color = D3DCOLOR_RGBA(255,255,255,(int)(m_fAlpha * 255));
		VBuffer[1].color = D3DCOLOR_RGBA(255,255,255,(int)(m_fAlpha * 255));
		VBuffer[2].color = D3DCOLOR_RGBA(255,255,255,(int)(m_fAlpha * 255));
		VBuffer[3].color = D3DCOLOR_RGBA(255,255,255,(int)(m_fAlpha * 255));
	}
}
void c_Primitive3D::DrawPrimitiveAntialiasing(void)
{
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER,
			D3DTEXF_NONE);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER,
			D3DTEXF_NONE);

	// 透過色(抜き色)の部分をZバッファに書き込まない
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 描画設定
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		// ライティングしない
	
	//ワールド変換設定
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

	//描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D_PRIM);
	g_pD3DDevice->SetStreamSource(0, m_pD3DVertexBuffer, 0, sizeof(DVERTEX_PRIMITIVE));	// 頂点バッファを登録
	g_pD3DDevice->SetTexture(0, m_pD3DTexture);	
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//レンダー設定の復元
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);	
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER,
			D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER,
			D3DTEXF_LINEAR);
}

void c_Primitive3D::DrawPrimitive(void)
{
	// 透過色(抜き色)を可能にする
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// αブレンド可
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// 透過色(抜き色)の部分をZバッファに書き込まない
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 描画設定
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		// ライティングしない
	
	//ワールド変換設定
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

	//描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D_PRIM);
	g_pD3DDevice->SetStreamSource(0, m_pD3DVertexBuffer, 0, sizeof(DVERTEX_PRIMITIVE));	// 頂点バッファを登録
	g_pD3DDevice->SetTexture(0, m_pD3DTexture);	
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//レンダー設定の復元
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ライティングする
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// αブレンド 不可

}
void c_Primitive3D::DrawPrimitiveOtherTexture(LPDIRECT3DTEXTURE9 pD3DTexture)
{
	// 透過色(抜き色)を可能にする
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// αブレンド可
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// 透過色(抜き色)の部分をZバッファに書き込まない
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 描画設定
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		// ライティングしない
	
	//ワールド変換設定
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

	//描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D_PRIM);
	g_pD3DDevice->SetStreamSource(0, m_pD3DVertexBuffer, 0, sizeof(DVERTEX_PRIMITIVE));	// 頂点バッファを登録
	g_pD3DDevice->SetTexture(0, m_pD3DTexture);	
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//レンダー設定の復元
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ライティングする
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// αブレンド 不可
}

void c_Primitive3D::SetTexRecUVFrame(int nFrameX,int nFrameY)
{
	m_nRecFrameU = nFrameX;
	m_nRecFrameV = nFrameY;
}
void c_Primitive3D::SetSize(D3DXVECTOR3 size)
{
	m_vSize = size;
}
D3DXMATRIX	c_Primitive3D::GetMatrix(void)
{
	return m_mMatrix;
}
D3DXVECTOR3	c_Primitive3D::GetPos(void)
{
	return m_vPos;
}
D3DXVECTOR3	c_Primitive3D::GetSize(void)
{
	return m_vSize;
}
void c_Primitive3D::SetTextureUV(int V,int U,int Frame)
{
	if(V < MAX_V_FRAME)
	{
		if(V > m_nMaxFrameV)
		{
			m_nMaxFrameV	= V;
			m_nMaxFrameU[V] = U;
			m_nFrameUPerTimt[V] = Frame;
		}
	}
}
