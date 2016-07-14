//-----------------------------------------------------------
//C_MGR_STATIONARY_H
//-----------------------------------------------------------
#ifndef C_EDITOR_STATIONARY_MODEL_MGE_H
#define C_EDITOR_STATIONARY_MODEL_MGE_H
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_C_FileNameManger.h"
//--------------------------------------
//マスターズインクルード
#include "Sys_C_Model.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マネージャーインクルード
//--------------------------------------
//マクロ定義
typedef enum
{
	EDITOR_MODEL_CRAFT_TABLE = 0,

	EDITOR_MODEL_MAX,
}EDITOR_MODEL;
//--------------------------------------
//構造体宣言
//--------------------------------------
//クラス宣言
class c_EditorStModel_Mgr
{
public:
	c_EditorStModel_Mgr();
	~c_EditorStModel_Mgr();
	void Init_EditorStModel_Mgr(void);
	void Uninit_EditorStModel_Mgr(void);
	void Update_EditorStModel_Mgr(void);
	void Draw_EditorStModel_Mgr(void);
private:
	c_Model*			m_pStationaryModel[EDITOR_MODEL_MAX];
	c_FileNameMgr		m_cFileNameMgr;

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