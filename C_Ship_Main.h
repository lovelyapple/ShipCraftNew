//-----------------------------------------------------------
//CLASS_SHIP_MAIN
//-----------------------------------------------------------
#ifndef CLASS_SHIP_MAIN
#define CLASS_SHIP_MAIN
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_C_Physic.h"
//--------------------------------------
//マスターズインクルード
#include "C_Block.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マネージャーインクルード
//--------------------------------------
//マクロ定義
const D3DXVECTOR3	ShipPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
#define DEFAULT_SHIP_NAME		("data/Ship/ShipSample.csv")
//--------------------------------------
//クラス宣言
class c_Ship
{
#define SHIP_FULL_SIZE	(MAX_SHIP_SIZE * 2 + 1)
public:
	c_Ship();
	~c_Ship();
	void InitShip(void);
	void UninitShip(void);
	void UpdateShip(void);
	void DrawShip(void);
	D3DXVECTOR3 GetCenterpos(void);

	void CreateBlock(FIELDPLACE3 place,int nType);
	void DeleteBlock(FIELDPLACE3 place);
	void ShipPlaceChange(FIELDPLACE3* place);

	HRESULT SaveRecentlyShip(void);
	HRESULT	LoadShipFromFile(LPCSTR FileName);
	void	SetShipName(LPCSTR FileName);
private:
	c_Block*		m_pBlock[SHIP_FULL_SIZE][SHIP_FULL_SIZE][SHIP_FULL_SIZE];
	c_FileNameMgr	m_cFileMgr;
	LPCSTR			m_lpzFileName;
	D3DXVECTOR3		m_vCenterPos;

};
//--------------------------------------
//構造体宣言

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