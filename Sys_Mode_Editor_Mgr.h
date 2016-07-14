//-----------------------------------------------------------
//CLASS_TEST_MANAGER_H
//-----------------------------------------------------------
#pragma once
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
//--------------------------------------
//マスターズインクルード
#include "Sys_C_Font.h"
#include "Sys_C_Primitive3D.h"
//--------------------------------------
//インスタンスインクルード
#include "C_Ship_Main.h"
#include "C_ActiveBlock.h"
//--------------------------------------
//マネージャーインクルード
#include "C_Light_Mgr.h"
#include "C_Camera_Mgr.h"
#include "C_EditorStModel_Mgr.h"
//--------------------------------------
//UseInterfaceのインクルード
#include "C_UI_BlockMenu.h"

//--------------------------------------
//マクロ定義
//--------------------------------------
//構造体宣言
//--------------------------------------
//クラス宣言
class c_Mgr_EditorMode
{
public:
	c_Mgr_EditorMode(c_Camera_Mgr* pCamera_Mgr,
					 c_Light_Mgr*  pLight_Mgr);			// コンストラクタ―
	void Init_Mgr_EditorMode(void);						// 初期化処理
	void Update_Mgr_EditorMode(void);					// 更新処理
	void Uninit_Mgr_EditorMode(void);					// 開放処理
	void Draw_Mgr_EditorMode(void);						// 描画処理
	
	c_Ship*							m_pShip;			// 戦艦ポインタ
	c_Active_Block*					m_pAcitveBLock;		// 選択ブロック
	c_Font*							m_pFont;			// 文字表示ポインター

	c_Camera_Mgr*					m_pCamera_Mgr;		// カメラのマネージャ
	c_Light_Mgr*					m_pLight_Mgr;		// ライトのマネージャ
	c_EditorStModel_Mgr*			m_pStModel_Mgr;		// 静止モデルマネージャ

	c_BlockMenu*					m_BlockMenu;		// ブロックのメニュー




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
//-----------------------------------------------------------
//End of File