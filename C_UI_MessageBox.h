//-----------------------------------------------------------
//CLASS_UI_INPUTUWINDOW_SHIP_H
//-----------------------------------------------------------
#ifndef CLASS_UI_MESSAGE_BOX_H
#define CLASS_UI_MESSAGE_BOX_H
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_C_Font.h"
#include "Sys_C_Messenger.h"
//--------------------------------------
//マスターズインクルード
#include "Sys_C_Primitive2D.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マネージャーインクルード
//--------------------------------------
//マクロ定義
const D3DXVECTOR3 MessageBoxPos		= D3DXVECTOR3(SCREEN_WIDTH_WIN/2,SCREEN_HEIGHT_WIN/2,0.0f);
const D3DXVECTOR3 MessageBoxSize	= D3DXVECTOR3(100.0f,30.0f,0.0f);
const D3DXVECTOR3 MessageFontPos	= D3DXVECTOR3(-MessageBoxSize.x,-MessageBoxSize.y * 0.5f,0.0f);
#define FILENAME_MESSAGEBOX_DEAULT_TEX	("data/Texture/MessageBoxDefault.png")
#define MAX_TEXT	(128)
//--------------------------------------
//クラス宣言
class c_UI_MessageBox
{
public:
	c_UI_MessageBox();
	~c_UI_MessageBox();
	void Init_MessageBox(void);
	void Update_MessageBox(void);
	void Uninit_MessageBox(void);
	void Draw_MessageBox(void);
	void Openinput(void);
private:
	c_Primitive2D*				m_pPlate;
	c_Font*						m_pFont;
	LPCSTR						m_lpzText;
	c_Messenger					m_cMessenger;
	bool						m_bInput;

};
//--------------------------------------
//オブジェクトグローバル変数宣言
//--------------------------------------
//係数グローバル変数宣言
//--------------------------------------
//プロトタイプ宣言
//--------------------------------------
//初期化処理
//--------------------------------------
//終了処理
//--------------------------------------
//更新処理
//--------------------------------------
//描画処理
#endif
//-----------------------------------------------------------
//End of File
//-----------------------------------------------------------