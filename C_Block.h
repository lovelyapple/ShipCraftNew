
//-----------------------------------------------------------
//CLASS_BLOCK
//-----------------------------------------------------------
#ifndef CLASS_BLOCK
#define CLASS_BLOCK
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_UserDefinition.h"
#include "Sys_C_FileNameManger.h"
#include "Sys_C_Physic.h"
//--------------------------------------
//マスターズインクルード
#include "C_3D_Test_model.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マネージャーインクルード
//--------------------------------------
//マクロ定義
//--------------------------------------
//構造体宣言
typedef struct
{
	int			nType;
	int			nHP;
	int			nWeight;
	int			nBoyance;
}BLOCK_STATS;
typedef enum
{
	BLOCK_TYPE_NORMAL = 0,
	BLOCK_TYPE_METAL,
	BLOCK_TYPE_ENGINE,
	BLOCK_TYPE_WOOD,
	BLOCK_TYPE_ACTIVE,
	BLOCK_TYPE_MAX,
}BLOCK_TYPE;
//--------------------------------------
//クラス宣言
class c_Block : public c_Model
{
public:
	c_Block();
	~c_Block();
	void UpdateBlockFieldPosInShip(D3DXVECTOR3 CenterPos,FIELDPLACE3 LimitHalf);
	void UpdateBlockMatrix(void);

	BLOCK_STATS		m_uStats;
	FIELDPLACE3		m_uPlace;
	c_FileNameMgr	m_cFileName;
	c_Physic		m_cPhysic;
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