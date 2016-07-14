//-----------------------------------------------------------
//CLASS_LIGHT_MANAGER_H
//-----------------------------------------------------------
#ifndef CLASS_LIGHT_MANAGER_H
#define CLASS_LIGHT_MANAGER_H
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
//--------------------------------------
//マスターズインクルード
#include "Sys_C_Light.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マネージャーインクルード
//--------------------------------------
//マクロ定義
//--------------------------------------
//構造体宣言
//--------------------------------------
//クラス宣言
class c_Light_Mgr
{
#define MAX_LIGHT_IN_LIST				(32)
#define MAX_LIGHT_IN_SYS				(MAX_LIGHT_IN_LIST * 2 + 1)
public:
	c_Light_Mgr();														// コンストラクタ　
	void	Init_LightMgr(void);										// 初期化
	void	Uninit_LightMgr(void);										// 開放
	void	Update_LightMgr(void);										// 更新
	void	Draw_LightMgr(void);										// 描画
	HRESULT	Create_SpotLight(int* Number,D3DXVECTOR3 Target,D3DXVECTOR3 vPos);		// スポットライト作成
	HRESULT	Create_PointLight(int* Number);											// スポットライト作成
	HRESULT	CheckLightIntList(int* Num);								// ライトナンバーの取得
	void	DeleteLight(int type,int Number);							// ライトの削除
	int						m_pSunLight;								// 天候光源のポインタ
	int*					m_pSpotList[MAX_LIGHT_IN_LIST];				// スポットライトのポインタ配列
	int*					m_pPointList[MAX_LIGHT_IN_LIST];			// ポイントライトのポインタ配列

	c_Light*				m_pSysLight[MAX_LIGHT_IN_SYS];				// システム上のライトナンバー
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
