//-----------------------------------------------------------
//CLASS_UI_EDITOR_BLOCKMENU
//-----------------------------------------------------------
#ifndef CLASS_UI_SELECTION_H
#define CLASS_UI_SELECTION_H

//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
//--------------------------------------
//マスターズインクルード
#include "Sys_C_Primitive3D.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マネージャーインクルード
//--------------------------------------
//マクロ定義
const D3DXVECTOR3 SelectionSize = D3DXVECTOR3(0.3f,0.3f,0.0f);
const D3DXVECTOR3 SelectionBGPos = D3DXVECTOR3(0.0f,0.0f,-0.001f);
//--------------------------------------
//構造体宣言
//--------------------------------------
//クラス宣言
class c_Selection
{
public:
	c_Selection();
	~c_Selection();
	void Init_Selection(LPCSTR FileName);
	void Uninit_Selection(void);
	void Update_Selection(void);
	void Draw_Selection(void);
	void Set_SelectionPos(D3DXVECTOR3 SePos,D3DXVECTOR3 BgPos);

	c_Primitive3D*			m_pSelectionEntity;
	c_Primitive3D*			m_pSelectionBG;
	D3DXVECTOR3				m_vPosFromCamera;

	float					m_fAlpha;
	bool					m_bActived;
	int						m_nRecTime;
	int						m_nMaxTime;
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