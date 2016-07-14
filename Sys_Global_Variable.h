//------------------------------------------------------
//グローバル変数ヘッダー
//------------------------------------------------------
#ifndef _SYS_G_VARIABLE_
#define _SYS_G_VARIABLE_

#include "Sys_Include.h"


//---------------------------
//アプリケーション変数
extern HINSTANCE	g_hInstance;	// インスタンス・ハンドル
extern HWND			g_hWnd;			// ウインドウ・ハンドル
extern HMENU		g_hMenu;		// メニュー・ハンドル

extern const char*	g_AppTitle;
extern const char*	g_WndClass;

extern  int			g_FPS;			//　フレームカウント
extern DWORD		g_dwExecLastTime;					// FPS計測用
extern DWORD		g_dwFPSLastTime;					// 最後FPSを測った時間
extern DWORD		g_dwCurrentTime;					// 現在の時間
extern DWORD		g_dwFrameCount;						// フレーム数
extern RECT			g_rectWindow;	//最後のウィンドウ情報を保存する変数
//ウィンド・フルースクリーン関連
extern bool			g_bWindow;

extern SIZE			g_sizeWindowMode;		//ウインドウモード
extern SIZE			g_sizeFullScreenMode;	//フルスクリーンモード
extern D3DFORMAT	g_formatFull;			//ディスプレイ（バックバッファフォーマット）
extern int			g_nMouseHoilu;			//マウスのホイルを取得
//アプリケーションの動作フラグ
extern bool			g_bActive;				//アクティブ状態

//---------------------------
//DirectX関連変数

//インターフェイス
extern LPDIRECT3D9				g_pD3D;			// Direct3Dインターフェイス
extern LPDIRECT3DDEVICE9		g_pD3DDevice;	// Direct3DDeviceインターフェイス
extern D3DPRESENT_PARAMETERS	g_D3DPP;		// D3DDeviceの設定(現在)

extern D3DPRESENT_PARAMETERS	g_D3DPPWindow;	// D3DDeviceの設定(ウインドウ・モード用)
extern D3DPRESENT_PARAMETERS	g_D3DPPFull;	// D3DDeviceの設定(フルスクリーン・モード用)
extern D3DXMATRIX*	g_matView;					// ヴューマトリックスポインター
extern D3DXMATRIX*	g_pMatrixProjection;		// プロジェクションマトリックスポインター

extern bool	g_bDeviceLost;						//デバイスの消失フラグ

//2D描画用のスプライト機能-->>>>>>>.ここにはいらない
//LPD3DXSPRITE			g_pD3DXSprite = NULL;	// スプライト
//LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;	// スプライトに使うテクスチャ
//WCHAR g_szSpriteFile[] = L"..\\Media\\canvas.dds";	// スプライトに使う画像ファイル



#endif