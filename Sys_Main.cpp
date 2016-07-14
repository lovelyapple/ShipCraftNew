//=========================================================================
//DirectX Base Main
//=========================================================================
#define STRICT					//より厳密なチェックを行う
#define WIN32_LEAN_AND_MEAN		//ヘッダーからあまり使わない関数を省略する
#define WINVER			0x501	//WXp以降
#define _WIN32_WINNT	0x501


#define D3D_DEBUG_INFO				//Direct3Dデバッグ情報の有効化
#define D3DXFX_ARGEADRESS_HANDLE	//文字列をD3DXHANDLEパラメータに渡す

#include "Sys_Include.h"
#include "Sys_Graphics.h"
#include "Sys_Mgr_Game.h"
//---------------------------
//アプリケーション変数
HINSTANCE		g_hInstance		= NULL;	// インスタンス・ハンドル
HWND			g_hWnd			= NULL;	// ウインドウ・ハンドル
HMENU			g_hMenu			= NULL;	// メニュー・ハンドル

const char*		g_AppTitle	= "DirectX3DGame";
const char*		g_WndClass	= "D3D9GV01";

int				g_FPS;			//　フレームカウント
RECT			g_rectWindow;	//最後のウィンドウ情報を保存する変数
//ウィンド・フルースクリーン関連
bool			g_bWindow		= false;

SIZE			g_sizeWindowMode		=	{SCREEN_WIDTH_WIN,SCREEN_HEIGHT_WIN};		//ウインドウモード
SIZE			g_sizeFullScreenMode	=	{SCREEN_WIDTH_FULL,SCREEN_HEIGHT_FULL};		//フルスクリーンモード
D3DFORMAT		g_formatFull			= D3DFMT_X8R8G8B8;	//ディスプレイ（バックバッファフォーマット）

//アプリケーションの動作フラグ
bool			g_bActive				= false;//アクティブ状態
bool			g_bDeviceLost			= false;
int				g_nMouseHoilu;

//フレーム変数宣言
DWORD			g_dwExecLastTime;					// FPS計測用
DWORD			g_dwFPSLastTime;					// 最後FPSを測った時間
DWORD			g_dwCurrentTime;					// 現在の時間
DWORD			g_dwFrameCount;						// フレーム数

//-------------------------------------------------------
//プロトタイプ宣言
LRESULT	CALLBACK MainWndProc(HWND hWnd,UINT msg,UINT wParam,LONG lparam);
HRESULT	InitApplication(HINSTANCE hInst);
bool CleanApplication(void);
bool AppIdle(void);
HRESULT ChangeWindowSize(void);
void ChangeDisplayMode(void);

//***********************************************************
//Main
//***********************************************************
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow)
{

	srand((unsigned int)time (NULL));
	// デバッグ ヒープ マネージャによるメモリ割り当ての追跡方法を設定
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	//アプリケーションに関する初期化
	HRESULT hr = InitApplication(hInst);
	if(FAILED(hr))
	{
		MessageBox(g_hWnd, _T("システム初期化失敗"),
			_T("アプリケーション初期化失敗"), 
			MB_OK | MB_ICONERROR);	
	}
	else
	{
		hr = InitDXGraphics();
		if(FAILED(hr))
		{
			MessageBox(g_hWnd, _T("システム初期化失敗"),
				_T("D3D_3DGraphic初期化失敗"), 
				MB_OK | MB_ICONERROR);
			DestroyWindow(g_hWnd);
		}


		//Direct以外のオブジェクト
		hr = Init3DObject();
		hr = Init_SysGame();


		if(FAILED(hr))
		{
			MessageBox(g_hWnd, _T("システム初期化失敗"),
				_T("D3D_3Dオブジェクト初期化失敗"), 
				MB_OK | MB_ICONERROR);
			DestroyWindow(g_hWnd);
		}
	}

	//フレームに関する初期化
	timeBeginPeriod(1);								// タイマの分解能を最小にセット
	g_dwFPSLastTime = g_dwExecLastTime = timeGetTime();	// 現在のシステムタイマを取得
	g_dwExecLastTime -= FRAME_RATE;					// Update()が先に1回以上呼ばれるように
	g_dwFrameCount = 0;
	g_FPS = 0;

	//メッセージループ
	MSG msg;
	msg.message = WM_NULL;
	//Input初期化
	InitInput(g_hInstance,g_hWnd);


	while(WM_QUIT != msg.message)
	{
		//メッセージチェック
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{		// メッセージをチェック
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			// この辺でフレーム数カウント
			g_dwCurrentTime = timeGetTime();					// 現在のタイマ値を取得
			if (g_dwCurrentTime - g_dwFPSLastTime >= 500)
			{		// 0.5秒ごとに計測
				// フレーム数を計算
				g_FPS = g_dwFrameCount * 1000 / (g_dwCurrentTime - g_dwFPSLastTime);
				g_dwFPSLastTime = g_dwCurrentTime;	// タイマ値を更新
				g_dwFrameCount = 0;				// フレームカウンタをリセット
			}

			// この辺で時間管理
			while (g_dwCurrentTime - g_dwExecLastTime >= FRAME_RATE)
			{	// 一定時間が経過したら…
				g_dwExecLastTime += FRAME_RATE;						// タイマ値を更新
				g_nMouseHoilu = GET_WHEEL_DELTA_WPARAM(msg.wParam);
				UpdateInput();
				Update_SysGame();
			
			}
			if(!AppIdle())//中身にレンダー関数がある
				DestroyWindow(g_hWnd);
			//Render();		

			g_dwFrameCount++;										// フレームカウントを+1
		
		}
	}

	timeEndPeriod(1);//タイマー分解能を解除
	//Input終了処理
	UninitInput();
	
	Uninit_SysGame();
	
	UninitDXGraphics();//グラフィック環境の終了処理
	return (int)msg.wParam;
	_CrtDumpMemoryLeaks();
}
//--------------------------------------
//アプリケーションの初期化
//--------------------------------------
HRESULT InitApplication(HINSTANCE hInst)
{
	//アプリケーションのインスタンス　ハンドルを保存
	g_hInstance = hInst;

	//IMEを禁止する　入力予測機能をOFF
	//ImmDisableIME(-1);// このスレッドで禁止(imm32.libをリンクする)

	//ウインドをレジスタに登録
	WNDCLASS wc;
	wc.style			= CS_HREDRAW | CS_VREDRAW;		//基本性質設定
	wc.lpfnWndProc		= (WNDPROC)MainWndProc;			//メッセージを受け取る関数のポインタ
	wc.cbClsExtra		= 0;							//1にすると、アプリ共通ポインタを設定する為に動的メモリを確保する
	wc.cbWndExtra		= 0;							//上と似ている
	wc.hInstance		= hInst;						//アプリケーションのインスタンスハンドル
	wc.hIcon			= LoadIcon(hInst, IDI_APPLICATION);//アイコンがでくすとっぽに描画
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);//カーソルの設定
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);//アプリケーションが画面を再描画する時の色ブラシハンドル
	wc.lpszMenuName		= NULL;//メニューを作るか
	//wc.lpszMenuName		= g_bWindow ? MAKEINTRESOURCE(IDR_MENU1) : NULL;
	wc.lpszClassName	= g_WndClass;//このウィンドウのクラスの名前、適当いいい
	if(!RegisterClass(&wc))
		return false;
	//ウィンドウの作成
	g_rectWindow.top	= 0;
	g_rectWindow.left	= 0;
	g_rectWindow.right	= g_sizeWindowMode.cx;
	g_rectWindow.bottom	= g_sizeWindowMode.cy;
	AdjustWindowRect(&g_rectWindow, WS_OVERLAPPEDWINDOW, TRUE);
	g_rectWindow.right	= g_rectWindow.right - g_rectWindow.left;
	g_rectWindow.bottom	= g_rectWindow.bottom - g_rectWindow.top;
	g_rectWindow.top	= 0;
	g_rectWindow.left	= 0;
	
	g_bWindow			= true;
	//if(IDYES == MessageBox(g_hWnd,_T("まずウインドウモードで実行しますか？"),
	//	_T("画面モード"), MB_YESNO))
	//	g_bWindow = true;

	RECT	rect;
	if(g_bWindow)
	{
		// (ウインドウ・モード用)
		rect.top	= CW_USEDEFAULT;
		rect.left	= CW_USEDEFAULT;
		rect.right	= g_rectWindow.right;
		rect.bottom	= g_rectWindow.bottom;
	}
	else
	{
		// (フルスクリーン・モード用)
		rect.top	= 0;
		rect.left	= 0;
		rect.right	= g_sizeFullScreenMode.cx;
		rect.bottom	= g_sizeFullScreenMode.cy;
	}
	//-----------------------------------
	//ウインドウの作成
	g_hWnd = CreateWindow(
		g_WndClass,
		g_AppTitle,
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION,// | WS_THICKFRAME,
		rect.left, 
		rect.top, 
		rect.right, 
		rect.bottom,
		NULL,
		NULL,
		hInst,
		NULL);
	if(g_hWnd == NULL)
	{
		return false;
	}
	//-------------------------------------
	//ウインドウをｐ一度表示
	ShowWindow(g_hWnd,SW_SHOWNORMAL);
	UpdateWindow(g_hWnd);
	return S_OK;
}
//--------------------------------------
//アプリケーションの終了処理
//--------------------------------------
bool CleanApplication(void)
{
	//念のために書いとく
	if(g_hMenu)
		DestroyMenu(g_hMenu);

	//ウィンドウクラスをレジスタから解放
	UnregisterClass(g_WndClass,g_hInstance);
	return true;
}
//--------------------------------------
//コールバックプロシージャ関数
//--------------------------------------
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
{
	HRESULT hr = S_OK;
	switch(msg)
	{
	case WM_ACTIVATE:
		g_bActive = (LOWORD(wParam)!= 0);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		g_hWnd = NULL;
		return 0;

	// ウインドウ・サイズの変更処理
	case WM_SIZE:
		if(g_D3DPP.Windowed != TRUE)
			break;
		if (!g_pD3DDevice || wParam == SIZE_MINIMIZED)
			break;
		g_D3DPP.BackBufferWidth  = LOWORD(lParam);
		g_D3DPP.BackBufferHeight = HIWORD(lParam);

		if(g_bDeviceLost)
			break;
		if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)
			ChangeWindowSize();
		break;

	case WM_SETCURSOR://カーソルを消す
		if (g_D3DPP.Windowed != TRUE)
		{
			SetCursor(NULL);
			return 1;
		}
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE://[ESCAPE]キーでウインドウを閉じる
			PostMessage(hWnd,WM_CLOSE,0,0);
			break;
		//case KEY_CHANGE_DISP://該当キーを押したら、ディスプレイのモードを変更
		//	ChangeDisplayMode();
		//	break;
		}
			break;
	case WM_COMMAND:
		//選択されたメニューを実行//たぶん使わない
		switch(LOWORD(wParam))
		{
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			return 0;
		}
		break;
	}
	//デフォルト処理
	return DefWindowProc(hWnd,msg,wParam,lParam);

}
//--------------------------------------
//アイドル処理
//--------------------------------------
bool AppIdle(void)
{
	if(!g_pD3D || !g_pD3DDevice)
		return false;
	if(!g_bActive)
		return true;

	//デバイス消失した時の復元処理
	HRESULT hr;
	if(g_bDeviceLost)
	{
		Sleep(100);//0.1秒を待つ
		//デバイスのチェックを行う
		hr = g_pD3DDevice->TestCooperativeLevel();
		
		if(FAILED(hr))
		{
			if(hr == D3DERR_DEVICELOST)
				return true;	//デバイスはまだ失われている

			if(hr != D3DERR_DEVICENOTRESET)
				return false;

			//いったんDirectで管理されていないソースを開放
			CleanupD3DObject();

			hr = g_pD3DDevice->Reset(&g_D3DPP);//復元を試してみる
			if(FAILED(hr))
			{
				if (hr == D3DERR_DEVICELOST)
					return true;  // デバイスはまだ失われてい
				MessageBox(g_hWnd, _T("画面モード切替失敗"),
					_T("デバイスがまた失った"), 
					MB_OK | MB_ICONERROR);
				return false;
			}
			//先ほど開放したソースを再取得
			hr = Init3DObject();
			if(FAILED(hr))
			{
				MessageBox(g_hWnd, _T("画面モード切替失敗"),
					_T("リソースの再取得が失敗しました"), 
					MB_OK | MB_ICONERROR);
				return false;
			}
		}
		//デバイスが復元した,フラグを変更
		g_bDeviceLost = false;
	}

	//画面を復元後の更新を一回行う
	hr = Render();
	if(hr == D3DERR_DEVICELOST)
		g_bDeviceLost = true; //デバイスが回復されていない
	else if (FAILED(hr))
		return false;//描画失敗

	return true;
}
//-----------------------------------------
//ウインドウ・サイズの変更
HRESULT ChangeWindowSize(void)
{
	//ウインドウのクライアント領域に合わせる
	CleanupD3DObject();
	
	HRESULT	hr = g_pD3DDevice->Reset(&g_D3DPP);//デバイスをまずリセットする

	if(FAILED(hr))
	{
		if(hr == D3DERR_DEVICELOST)
			g_bDeviceLost = true;
		else
			DestroyWindow(g_hWnd);

		return E_FAIL;
	}
	hr = Init3DObject();
	if(FAILED(hr))
	{
		DestroyWindow(g_hWnd);
		return E_FAIL;
	}

	// ビューポートの再設定
	D3DVIEWPORT9 vp;
	vp.X		= 0;
	vp.Y		= 0;
	vp.Width	= g_D3DPP.BackBufferWidth;
	vp.Height	= g_D3DPP.BackBufferHeight;
	vp.MinZ		= 0.0f;
	vp.MaxZ		= 1.0f;
	hr = g_pD3DDevice->SetViewport(&vp);
	if (FAILED(hr))
	{
		DestroyWindow(g_hWnd);
	}
	return hr;
	
}
//-----------------------------------------
//画面モード変更
void ChangeDisplayMode(void)
{
	g_bWindow = !g_bWindow;//現在のモードの反対モードに切り替え

	CleanupD3DObject();
	if(g_bWindow)
	{
		g_D3DPP = g_D3DPPWindow;
	}
	else
	{
		g_D3DPP = g_D3DPPFull;
	}

	HRESULT hr = g_pD3DDevice->Reset(&g_D3DPP);
	if(FAILED(hr))
	{
		if(hr == D3DERR_DEVICELOST)
			g_bDeviceLost = true;
		else
			DestroyWindow(g_hWnd);
		MessageBox(g_hWnd, _T("画面モードの切り替え中が失敗しました"),
			_T("デバイスのリセット失敗"), 
			MB_OK | MB_ICONERROR);
		return ;
	}

	hr = Init3DObject();
	if(FAILED(hr))
	{
		DestroyWindow(g_hWnd);
		MessageBox(g_hWnd, _T("画面モードの切り替え中が失敗しました"),
			_T("3Dオブジェクトの初期化失敗"), 
			MB_OK | MB_ICONERROR);
		return;
	}

	if(g_bWindow)
	{
		SetWindowLong(g_hWnd,GWL_STYLE,WS_OVERLAPPEDWINDOW | WS_VISIBLE);
		if(g_hMenu != NULL)//たぶん大丈夫けど、一応書いとく
		{
			SetMenu(g_hWnd,g_hMenu);
				g_hMenu = NULL;
		}
		//ウインドウの位置を再設定
		SetWindowPos(g_hWnd, HWND_NOTOPMOST,
				g_rectWindow.left, g_rectWindow.top,
				g_rectWindow.right - g_rectWindow.left,
				g_rectWindow.bottom - g_rectWindow.top,
				SWP_SHOWWINDOW);

	}
	else
	{
		SetWindowLong(g_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
		if(g_hMenu == NULL)
		{
			g_hMenu = GetMenu(g_hWnd);
			SetMenu(g_hWnd, NULL);
		}
	}
}
