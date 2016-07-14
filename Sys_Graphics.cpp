//=========================================================================
//DirectX Base Graphics.cpp
//=========================================================================

#include "Sys_Graphics.h"


//インターフェイス
LPDIRECT3D9				g_pD3D			= NULL; // Direct3Dインターフェイス
LPDIRECT3DDEVICE9		g_pD3DDevice	= NULL; // Direct3DDeviceインターフェイス
D3DPRESENT_PARAMETERS	g_D3DPP;				// D3DDeviceの設定(現在)

D3DPRESENT_PARAMETERS	g_D3DPPWindow;			// D3DDeviceの設定(ウインドウ・モード用)
D3DPRESENT_PARAMETERS	g_D3DPPFull;			// D3DDeviceの設定(フルスクリーン・モード用)

D3DXMATRIX*	g_matView;							// ヴューマトリックスポインター
D3DXMATRIX*	g_pMatrixProjection;				// プロジェクションマトリックスポインター
//-----------------------------------------
//グラフィックス関連初期化
HRESULT	InitDXGraphics(void)
{
	//Drecit3Dオブジェクトを作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
		return E_FAIL;

	//D3DDeviceオブジェクトのパラメーターを設定----window mode
	ZeroMemory(&g_D3DPPWindow,sizeof(g_D3DPPWindow));

	
	g_D3DPPWindow.BackBufferWidth			= 0;
	g_D3DPPWindow.BackBufferHeight			= 0;
	g_D3DPPWindow.BackBufferFormat			= D3DFMT_UNKNOWN;
	g_D3DPPWindow.BackBufferCount			= 1;
	g_D3DPPWindow.MultiSampleType			= D3DMULTISAMPLE_NONE;
	g_D3DPPWindow.MultiSampleQuality		= 0;
	g_D3DPPWindow.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	g_D3DPPWindow.hDeviceWindow				= g_hWnd;
	g_D3DPPWindow.Windowed					= TRUE;
	g_D3DPPWindow.EnableAutoDepthStencil	= TRUE;
	g_D3DPPWindow.AutoDepthStencilFormat	= D3DFMT_D24S8;
	g_D3DPPWindow.Flags						= 0;
	g_D3DPPWindow.FullScreen_RefreshRateInHz= 0;
	g_D3DPPWindow.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	// D3DDeviceオブジェクトの設定(フルスクリーン・モード)
	ZeroMemory(&g_D3DPPFull, sizeof(g_D3DPPFull));

	g_D3DPPFull.BackBufferWidth				= g_sizeFullScreenMode.cx;
	g_D3DPPFull.BackBufferHeight			= g_sizeFullScreenMode.cy;
	g_D3DPPFull.BackBufferFormat			= g_formatFull;
	g_D3DPPFull.BackBufferCount				= 1;
	g_D3DPPFull.MultiSampleType				= D3DMULTISAMPLE_NONE;
	g_D3DPPFull.MultiSampleQuality			= 0;
	g_D3DPPFull.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	g_D3DPPFull.hDeviceWindow				= g_hWnd;
	g_D3DPPFull.Windowed					= FALSE;
	g_D3DPPFull.EnableAutoDepthStencil		= TRUE;
	g_D3DPPFull.AutoDepthStencilFormat		= D3DFMT_D24S8;
	g_D3DPPFull.Flags						= 0;
	g_D3DPPFull.FullScreen_RefreshRateInHz	= 0;
	g_D3DPPFull.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	
	//--------------------------------
	//Deviceを作成

	//if (IDYES == MessageBox(g_hWnd, _T("ウィンドウモードで実行しますか？"), _T("画面モード"), MB_YESNO))
	//	g_bWindow = true;

	if (g_bWindow)
		g_D3DPP = g_D3DPPWindow;
	else
		g_D3DPP = g_D3DPPFull;



	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
						D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_D3DPP, &g_pD3DDevice);
	if (FAILED(hr))
	{
		hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
						D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_D3DPP, &g_pD3DDevice);
		if (FAILED(hr))
		{
			hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, g_hWnd,
							D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_D3DPP, &g_pD3DDevice);
			if (FAILED(hr))
				return E_FAIL;
		}
	}




	// レンダリングステートパラメータの設定
	//g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// カリングを行わない
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャＵ値の繰り返し設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャＶ値の繰り返し設定
	// テクスチャステージステートパラメータの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理 マテリアルのAと関係ない
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
	//アンチエイリアシング
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER,
			D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER,
			D3DTEXF_LINEAR);


	//--------------------------------
	//ビューポートの設定
	D3DVIEWPORT9 vp;
	vp.X			= 0;
	vp.Y			= 0;
	vp.Width		= g_D3DPP.BackBufferWidth;
	vp.Height		= g_D3DPP.BackBufferHeight;
	vp.MinZ			= 0.0f;
	vp.MaxZ			= 1.0f;
	hr = g_pD3DDevice->SetViewport(&vp);
	if(FAILED(hr))
		return E_FAIL;
	return S_OK;

}

//-----------------------------------------
//オブジェクトに関する設定
HRESULT	Init3DObject(void)
{
	return S_OK;
}
//-----------------------------------------
//オブジェクトのクリーンアップ
HRESULT CleanupD3DObject(void)
{
	return S_OK;
}
//-----------------------------------------
//描画処理
HRESULT Render(void)
{

	//バックバッファクリア
	g_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL,BACKCOLOR,1.0f,0);

	//描画開始
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		Draw_SysGame();
		//シーン終了
		g_pD3DDevice->EndScene();
	}

	//シーンを表示
	return g_pD3DDevice->Present(NULL,NULL,NULL,NULL);

				// シェーダ終了
	return S_OK;
}
//-----------------------------------------
//グラフィックスの終了処理
bool UninitDXGraphics(void)
{
	SAFE_RELEASE(g_pD3DDevice);		//デバイスを解除
	SAFE_RELEASE(g_pD3D);			//インタフェースを解除
	return true;
}
