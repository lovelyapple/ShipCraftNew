//-----------------------------------------------------------
//CLASS_UI_EDITOR_BLOCKMENU
//-----------------------------------------------------------
#ifndef CLASS_UI_EDITOR_BLOCKMENU
#define CLASS_UI_EDITOR_BLOCKMENU

//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "C_Camera_Mgr.h"
//--------------------------------------
//マスターズインクルード
#include "C_UI_Selection.h"
#include "C_Block.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マネージャーインクルード
//--------------------------------------
//マクロ定義
const D3DXVECTOR3 BlockMenuPos = D3DXVECTOR3(-2.0f,-1.5f,4.0f);
#define MAX_BLOCK_SELECTION		(BLOCK_TYPE_MAX - 1)
//--------------------------------------
//構造体宣言
//--------------------------------------
//クラス宣言
class c_BlockMenu
{
public:
	c_BlockMenu();
	~c_BlockMenu();
	void Init_BlockMenu(c_Camera_Mgr* pCameraMgr);
	void Uninit_BlockMenu(void);
	void Update_BlockMenu(void);
	void Draw_BlockMenu(void);
	c_Camera_Mgr*		m_pGameCamera;
	int	 GetRecentSelection(void);
private:
	c_Selection*		m_pSelection[MAX_BLOCK_SELECTION];
	c_FileNameMgr		m_FileMgr;
	int					m_nRecSelection;
	
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