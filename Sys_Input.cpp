//=============================================================================
//
// 入力処理 [input.cpp]
//
//=============================================================================
#include "Sys_Input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX			(256)				// キー情報の最大値

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
void UninitKeyboard(void);
HRESULT UpdateKeyboard(void);

// マウス用
HRESULT InitMouse(HINSTANCE hInst, HWND hWnd);
void UninitMouse(void);
HRESULT UpdateMouse(void);

// ジョイパッド関連
HRESULT InitJoypad(HWND hWnd);
void UninitJoypad(void);
void UpdateJoypad(void);
BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECTINPUT8			g_pDInput = NULL;					// IDirectInput8インターフェースへのポインタ
LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// IDirectInputDevice8インターフェースへのポインタ(キーボード)
LPDIRECTINPUTDEVICE8	g_pDIDevMouse = NULL;				// IDirectInputDevice8インターフェースへのポインタ(マウス) 
BYTE					g_keyState[NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
BYTE					g_keyStateTrigger[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
BYTE					g_keyStateRepeat[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
BYTE					g_keyStateRelease[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
int						g_keyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ
DIMOUSESTATE2			g_mouseState;						// マウスの状態を受け取るワーク
DIMOUSESTATE2			g_mouseStateTrigger;				// マウスの状態を受け取るワーク

DIJOYSTATE				g_joyState[MAX_CONTROLER];			// ジョイパッド情報配列
DIJOYSTATE				g_joyStatePrev[MAX_CONTROLER];		// ジョイパッド情報配列（直前）
LPDIRECTINPUTDEVICE8	g_pDIDevJoypad[MAX_CONTROLER];		// IDirectInputDevice8インターフェースへのポインタ(ジョイパッド)
int						g_nJoypadNum = 0;					// 見つかったジョイパッドの数
BYTE					g_joyStateTrigger[MAX_CONTROLER][32];
static LONG				g_lInputPOV = -1;					// 前のジョイパッドの前の情報
static bool				g_bController = false;				// コントローラ使用するか
//=============================================================================
// 入力処理の初期化
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if(!g_pDInput)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&g_pDInput, NULL);
	}

	// キーボードの初期化
	InitKeyboard(hInst, hWnd);

	// マウスの初期化
	InitMouse(hInst, hWnd);

	// ゲームパッドの初期化
	if(FAILED(InitJoypad(hWnd)))
		return E_FAIL;

	return hr;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void UninitInput(void)
{
	// キーボードの終了処理
	UninitKeyboard();

	// マウスの終了処理
	UninitMouse();

	// ゲームパッドの終了処理
	UninitJoypad();

	if(g_pDInput)
	{
		g_pDInput->Release();
		g_pDInput = NULL;
	}
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void UpdateInput(void)
{
	// キーボードの更新
	UpdateKeyboard();

	// マウスの更新
	UpdateMouse();

	// ゲームパッドの更新
	UpdateJoypad();
}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
	if(FAILED(hr) || g_pDIDevKeyboard == NULL)
	{
		MessageBox(hWnd, _T("キーボードがねぇ！"), _T("警告！"), MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, _T("キーボードのデータフォーマットを設定できませんでした。"), _T("警告！"), MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, _T("キーボードの協調モードを設定できませんでした。"), _T("警告！"), MB_ICONWARNING);
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDIDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	if(g_pDIDevKeyboard)
	{
		g_pDIDevKeyboard->Unacquire();

		g_pDIDevKeyboard->Release();
		g_pDIDevKeyboard = NULL;
	}
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE keyStateOld[256];

	// 前回のデータを保存
	memcpy(keyStateOld, g_keyState, NUM_KEY_MAX);

	if(GetKeyboardTrigger(DIK_1))
		int a = 0;

	// デバイスからデータを取得
	hr = g_pDIDevKeyboard->GetDeviceState(sizeof(g_keyState), g_keyState);
	if(SUCCEEDED(hr))
	{
		for(int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
		{
			g_keyStateTrigger[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & g_keyState[cnt];
			g_keyStateRelease[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & ~g_keyState[cnt];
			g_keyStateRepeat[cnt] = g_keyStateTrigger[cnt];

			if(g_keyState[cnt])
			{
				g_keyStateRepeatCnt[cnt]++;
				if(g_keyStateRepeatCnt[cnt] >= 20)
				{
					g_keyStateRepeat[cnt] = g_keyState[cnt];
				}
			}
			else
			{
				g_keyStateRepeatCnt[cnt] = 0;
				g_keyStateRepeat[cnt] = 0;
			}
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		hr = g_pDIDevKeyboard->Acquire();
	}

	return hr;
}

//==============================
// ジョイパッドの初期化
//==============================
HRESULT InitJoypad(HWND hWnd)
{
	int nLoop;

	// 初期化
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
		g_pDIDevJoypad[nLoop] = NULL;

	// デバイスオブジェクトを作成(接続されているジョイパッドを列挙する)
	if(FAILED(g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, NULL, DIEDFL_ATTACHEDONLY)))
		return E_FAIL;

	// ジョイパッドの数だけ処理
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		// ジョイパッドがない場合はすっ飛ばす
		if(g_pDIDevJoypad[nLoop] == NULL)
			continue;

		// データフォーマットの設定
		if(FAILED(g_pDIDevJoypad[nLoop]->SetDataFormat(&c_dfDIJoystick)))
			return E_FAIL;

		// 協調レベルの設定
		if(FAILED(g_pDIDevJoypad[nLoop]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
			return E_FAIL;

		// デバイスへの入力制御開始
		g_pDIDevJoypad[nLoop]->Acquire();	
	}

	return S_OK;
}

//==============================
// ジョイパッド問い合わせ用コールバック関数
//==============================
BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{
	DIDEVCAPS	diDevCaps;			// デバイス情報

	// ジョイパッド用デバイスオブジェクトを作成
	if(FAILED(g_pDInput->CreateDevice(lpddi->guidInstance, &g_pDIDevJoypad[g_nJoypadNum], NULL)))
		return DIENUM_CONTINUE;		// 列挙を続ける

	// ジョイパッドの能力を調べる
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	if(FAILED(g_pDIDevJoypad[g_nJoypadNum]->GetCapabilities(&diDevCaps)))
	{
		if(g_pDIDevJoypad[g_nJoypadNum])
			g_pDIDevJoypad[g_nJoypadNum]->Release();
		g_pDIDevJoypad[g_nJoypadNum] = NULL;
		return DIENUM_CONTINUE;		// 列挙を続ける
	}

	// 規定数に達したら終了
	g_nJoypadNum++;
	if(g_nJoypadNum == MAX_CONTROLER)
		return DIENUM_STOP;		// 列挙を終了する
	else
		return DIENUM_CONTINUE;		// 列挙を続ける
}

//==============================
// ジョイパッドの終了処理
//==============================
void UninitJoypad(void)
{
	for(int nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
		SAFE_RELEASE(g_pDIDevJoypad[nLoop]);
}

//==============================
// ジョイパッドの更新処理
//==============================
void UpdateJoypad(void)
{
	int nLoop;
	
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		// 直前ジョイパッド情報のバックアップ
		g_joyStatePrev[nLoop] = g_joyState[nLoop];

		if(g_pDIDevJoypad[nLoop])
		{
			// デバイスからデータを取得
			if(FAILED(g_pDIDevJoypad[nLoop]->GetDeviceState(sizeof(DIJOYSTATE), &g_joyState[nLoop])))
				g_pDIDevJoypad[nLoop]->Acquire();
		}

		// トリガー情報計算
		for( int i = 0; i < 32; i++ )
		{
			if( g_joyState[nLoop].rgbButtons[i] & 0x80 && 
				!(g_joyStatePrev[nLoop].rgbButtons[i] & 0x80) )
			{
				g_joyStateTrigger[nLoop][i] = 0x80;
			} else {
				g_joyStateTrigger[nLoop][i] = 0x00;
			}
		}
	}
}


//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool GetKeyboardPress(int key)
{
	return (g_keyState[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool GetKeyboardTrigger(int key)
{
	return (g_keyStateTrigger[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool GetKeyboardRepeat(int key)
{
	return (g_keyStateRepeat[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool GetKeyboardRelease(int key)
{
	return (g_keyStateRelease[key] & 0x80) ? true : false;
}

//=============================================================================
// マウスの初期化
//=============================================================================
HRESULT InitMouse(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = g_pDInput->CreateDevice(GUID_SysMouse, &g_pDIDevMouse, NULL);
	if(FAILED(hr) || g_pDIDevMouse == NULL)
	{
		MessageBox(hWnd, _T("マウスがねぇ！"), _T("警告！"), MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = g_pDIDevMouse->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(hr))
	{
		MessageBox(hWnd, _T("マウスのデータフォーマットを設定できませんでした。"), _T("警告！"), MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = g_pDIDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, _T("マウスの協調モードを設定できませんでした。"), _T("警告！"), MB_ICONWARNING);
		return hr;
	}

	// デバイスの設定
	{
		DIPROPDWORD dipdw;

		dipdw.diph.dwSize = sizeof(dipdw);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwObj = 0;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = DIPROPAXISMODE_REL;

		hr = g_pDIDevMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDIDevMouse->Acquire();

	return S_OK;
}

//=============================================================================
// マウスの終了処理
//=============================================================================
void UninitMouse(void)
{
	if(g_pDIDevMouse)
	{
		g_pDIDevMouse->Unacquire();

		g_pDIDevMouse->Release();
		g_pDIDevMouse = NULL;
	}
}

//=============================================================================
// マウスの更新処理
//=============================================================================
HRESULT UpdateMouse(void)
{
	HRESULT hr;
	DIMOUSESTATE2 mouseStateOld;

	// 前回のデータを保存
	mouseStateOld = g_mouseState;

	// デバイスからデータを取得
	hr = g_pDIDevMouse->GetDeviceState(sizeof(g_mouseState), &g_mouseState);
	if(SUCCEEDED(hr))
	{
		g_mouseStateTrigger.lX = ((mouseStateOld.lX ^ g_mouseState.lX) & g_mouseState.lX);
		g_mouseStateTrigger.lY = ((mouseStateOld.lY ^ g_mouseState.lY) & g_mouseState.lY);
		g_mouseStateTrigger.lZ = ((mouseStateOld.lZ ^ g_mouseState.lZ) & g_mouseState.lZ);
		for(int cnt = 0; cnt < 8; cnt++)
		{
			g_mouseStateTrigger.rgbButtons[cnt] = ((mouseStateOld.rgbButtons[cnt] ^ g_mouseState.rgbButtons[cnt]) & g_mouseState.rgbButtons[cnt]);
		}
	}
	else
	{
		g_pDIDevMouse->Acquire();
	}

	return S_OK;
}

//=============================================================================
// マウスデータ取得(左プレス)
//=============================================================================
bool GetMouseLeftPress(void)
{
	return (g_mouseState.rgbButtons[0] & 0x80) ? true : false;
}

//=============================================================================
// マウスデータ取得(左トリガー)
//=============================================================================
bool GetMouseLeftTrigger(void)
{
	return (g_mouseStateTrigger.rgbButtons[0] & 0x80) ? true : false;
}

//=============================================================================
// マウスデータ取得(右プレス)
//=============================================================================
bool GetMouseRightPress(void)
{
	return (g_mouseState.rgbButtons[1] & 0x80) ? true : false;
}

//=============================================================================
// マウスデータ取得(右トリガー)
//=============================================================================
bool GetMouseRightTrigger(void)
{
	return (g_mouseStateTrigger.rgbButtons[1] & 0x80) ? true : false;
}

//=============================================================================
// マウスデータ取得(中央プレス)
//=============================================================================
bool GetMouseCenterPress(void)
{
	return (g_mouseState.rgbButtons[2] & 0x80) ? true : false;
}

//=============================================================================
// マウスデータ取得(中央トリガー)
//=============================================================================
bool GetMouseCenterTrigger(void)
{
	return (g_mouseState.rgbButtons[2] & 0x80) ? true : false;
}

//=============================================================================
// マウスデータ取得(Ｘ軸移動)
//=============================================================================
long GetMouseAxisX(void)
{
	return g_mouseState.lX;
}

//=============================================================================
// マウスデータ取得(Ｙ軸移動)
//=============================================================================
long GetMouseAxisY(void)
{
	return g_mouseState.lY;
}

//=============================================================================
// マウスデータ取得(Ｚ軸移動)
//=============================================================================
long GetMouseAxisZ(void)
{
	return g_mouseState.lZ;
}

//=============================================================================
// ジョイスティックデータ取得
//=============================================================================
bool GetJoyStickPress( int button )
{
	// 0番のジョイスティックしか見てない
	return (g_joyState[0].rgbButtons[button] & 0x80) ? true : false;
}
// トリガー
bool GetJoyStickTrigger( int button )
{
	// 0番のジョイスティックしか見てない
	return (g_joyStateTrigger[0][button] & 0x80) ? true : false;
}

//=============================================================================
// ジョイスティックデータ取得（Ｘ方向）
//=============================================================================
LONG GetJoyStickPositionX()
{
	return g_joyState[0].lX;
}

//=============================================================================
// ジョイスティックデータ取得（Ｙ方向）
//=============================================================================
LONG GetJoyStickPositionY()
{
	return g_joyState[0].lY;
}

//=============================================================================
// ジョイスティックデータ取得（ＲＸ方向）
//=============================================================================
LONG GetJoyStickPositionRX()
{
	return g_joyState[0].lRx;
}

//=============================================================================
// ジョイスティックデータ取得（ＲＹ方向）
//=============================================================================
LONG GetJoyStickPositionRY()
{
	return g_joyState[0].lRy;
}

//=============================================================================
// ジョイスティックデータ取得（スライダー）
//=============================================================================
LONG GetJoyStickSlider( int number )
{
	return g_joyState[0].rglSlider[number];
}

//=============================================================================
// ジョイスティックデータ取得（POV）
//=============================================================================
DWORD GetJoyStickRgdwPOV( int number )
{
	return g_joyState[0].rgdwPOV[number];
}
//=============================================================================
// ジョイスティックキーの取得
//=============================================================================
void SetUseController(bool bInput)
{
	g_bController = bInput;
}

bool GetInputTriggerPOV(int nKey)
{
	bool bInputed = false;
	
	if(g_bController)
	{
		switch(nKey)
		{
			case INPUT_KEY_UP:if(GetJoyStickRgdwPOV(0) == 0) 
								  if (g_lInputPOV != 0)
								 {
									  bInputed		= true;
									  g_lInputPOV	= 0;
								  }
			break;
			case INPUT_KEY_DOWN:if(GetJoyStickRgdwPOV(0) == 18000 && (g_lInputPOV != 18000)) 
								 {
									  bInputed		= true;
									  g_lInputPOV	= 18000;
								  }
			break;
			case INPUT_KEY_LEFT:if(GetJoyStickRgdwPOV(0) == 27000&& (g_lInputPOV != 27000)) 
								 {
									  bInputed		= true;
									  g_lInputPOV	= 27000;
								  }
			break;
			case INPUT_KEY_RIGHT:if(GetJoyStickRgdwPOV(0) == 9000&& (g_lInputPOV != 9000)) 
								 {
									  bInputed		= true;
									  g_lInputPOV	= 9000;
								  }
			break;
			case INPUT_KEY_1:if(GetJoyStickTrigger(0))bInputed = true;
			break;
			case INPUT_KEY_2:if(GetJoyStickTrigger(1))bInputed = true;
			break;
			case INPUT_KEY_3:if(GetJoyStickTrigger(2))bInputed = true;
			break;
			case INPUT_KEY_4:if(GetJoyStickTrigger(3))bInputed = true;
			break;
			case INPUT_KEY_L1:if(GetJoyStickTrigger(4))bInputed = true;
			break;
			case INPUT_KEY_L2:if(GetJoyStickTrigger(6))bInputed = true;
			break;
			case INPUT_KEY_R1:if(GetJoyStickTrigger(5))bInputed = true;
			break;
			case INPUT_KEY_R2:if(GetJoyStickTrigger(7))bInputed = true;
			break;
			case INPUT_KEY_START:if(GetJoyStickTrigger(9))bInputed = true;
			break;
		}
		if(GetJoyStickRgdwPOV(0) == -1)
			g_lInputPOV = -1;
	}
	else
	{
		switch(nKey)
		{
			case INPUT_KEY_UP:if(GetKeyboardTrigger(DIK_UP)) 
								  bInputed = true;
			break;
			case INPUT_KEY_DOWN:if(GetKeyboardTrigger(DIK_DOWN))
									bInputed = true;
			break;
			case INPUT_KEY_LEFT:if(GetKeyboardTrigger(DIK_LEFT)) 
									bInputed = true;
			break;
			case INPUT_KEY_RIGHT:if(GetKeyboardTrigger(DIK_RIGHT))
									 bInputed = true;
			break;
			case INPUT_KEY_1:if(GetKeyboardTrigger(DIK_RSHIFT)) 
								 bInputed = true;
			break;
			case INPUT_KEY_2:if(GetKeyboardTrigger(DIK_E))
								 bInputed = true;
			break;
			case INPUT_KEY_3:if(GetKeyboardTrigger(DIK_SPACE)) 
								 bInputed = true;
			break;
			case INPUT_KEY_4:if(GetKeyboardTrigger(DIK_R)) 
								 bInputed = true;
			break;
			case INPUT_KEY_L1:if(GetKeyboardTrigger(DIK_A)) 
								  bInputed = true;
			break;
			case INPUT_KEY_L2:if(GetKeyboardTrigger(DIK_Q))
								  bInputed = true;
			break;
			case INPUT_KEY_R1:if(GetKeyboardTrigger(DIK_S)) 
								  bInputed = true;
			break;
			case INPUT_KEY_R2:if(GetKeyboardTrigger(DIK_W))
								  bInputed = true;
			break;

			case INPUT_KEY_START:if(GetKeyboardTrigger(DIK_RETURN)) 
									 bInputed = true;
			break;
		}
	}

	return bInputed;
}
bool GetInputPressPOV(int nKey)
{
	bool bInputed = false;
	
	if(g_bController)
	{
		switch(nKey)
		{
			case INPUT_KEY_UP:if(GetJoyStickRgdwPOV(0) == 0)// && (g_lInputPOV != 0)) 
								 {
									  bInputed		= true;
									  g_lInputPOV	= 0;
								  }
			break;
			case INPUT_KEY_DOWN:if(GetJoyStickRgdwPOV(0) == 18000)//&& (g_lInputPOV != 18000)) 
								 {
									  bInputed		= true;
									  g_lInputPOV	= 18000;
								  }
			break;
			case INPUT_KEY_LEFT:if(GetJoyStickRgdwPOV(0) == 27000)//&& (g_lInputPOV != 27000)) 
								 {
									  bInputed		= true;
									  g_lInputPOV	= 27000;
								  }
			break;
			case INPUT_KEY_RIGHT:if(GetJoyStickRgdwPOV(0) == 9000)//&& (g_lInputPOV != 9000)) 
								 {
									  bInputed		= true;
									  g_lInputPOV	= 9000;
								  }
			break;
			case INPUT_KEY_1:if(GetJoyStickPress(0))
								 bInputed = true;
			break;
			case INPUT_KEY_2:if(GetJoyStickPress(1))bInputed = true;
			break;
			case INPUT_KEY_3:if(GetJoyStickPress(2))bInputed = true;
			break;
			case INPUT_KEY_4:if(GetJoyStickPress(3))bInputed = true;
			break;
			case INPUT_KEY_L1:if(GetJoyStickPress(4))bInputed = true;
			break;
			case INPUT_KEY_L2:if(GetJoyStickPress(6))bInputed = true;
			break;
			case INPUT_KEY_R1:if(GetJoyStickPress(5))bInputed = true;
			break;
			case INPUT_KEY_R2:if(GetJoyStickPress(7))bInputed = true;
			break;
			case INPUT_KEY_START:if(GetJoyStickPress(9))bInputed = true;
			break;
		}
			if(GetJoyStickRgdwPOV(0) == -1)
			g_lInputPOV = -1;	

	}
	else
	{
		switch(nKey)
		{
			case INPUT_KEY_UP:if(GetKeyboardPress(DIK_UP)) bInputed = true;
			break;
			case INPUT_KEY_DOWN:if(GetKeyboardPress(DIK_DOWN)) bInputed = true;
			break;
			case INPUT_KEY_LEFT:if(GetKeyboardPress(DIK_LEFT)) bInputed = true;
			break;
			case INPUT_KEY_RIGHT:if(GetKeyboardPress(DIK_RIGHT)) bInputed = true;
			break;
			case INPUT_KEY_1:if(GetKeyboardPress(DIK_RSHIFT)) bInputed = true;
			break;
			case INPUT_KEY_2:if(GetKeyboardPress(DIK_E)) bInputed = true;
			break;
			case INPUT_KEY_3:if(GetKeyboardPress(DIK_SPACE)) bInputed = true;
			break;
			case INPUT_KEY_4:if(GetKeyboardPress(DIK_SPACE)) bInputed = true;
			break;
			case INPUT_KEY_L1:if(GetKeyboardPress(DIK_A)) bInputed = true;
			break;
			case INPUT_KEY_L2:if(GetKeyboardPress(DIK_Q)) bInputed = true;
			break;
			case INPUT_KEY_R1:if(GetKeyboardPress(DIK_S)) bInputed = true;
			break;
			case INPUT_KEY_R2:if(GetKeyboardPress(DIK_W)) bInputed = true;
			break;
			case INPUT_KEY_START:if(GetKeyboardPress(DIK_RETURN)) bInputed = true;
			break;
		}
	}

	return bInputed;
}