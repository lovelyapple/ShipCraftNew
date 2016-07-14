//-----------------------------------------------------------
//Lightマスターズクラス
//-----------------------------------------------------------
#ifndef _C_LIGHT_
#define _C_LIGHT_
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_C_Physic.h"
//--------------------------------------
//マスターズインクルード
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マクロ定義

//--------------------------------------
//構造体宣言
typedef enum
{
	LIGHT_STATS_POSITION = 0,
	LIGHT_STATS_DIRCATION,
	LIGHT_STATS_RANGE,
	LIGHT_STATS_FALLOFF,
	LIGHT_STATS_DIFFUSE,
	LIGHT_STATS_AMBIENT,
	LIGHT_STATS_SPECULAR,
	LIGHT_STATS_THETA,
	LIGHT_STATS_PHI,
	LIGHT_STATS_ATTE01,
	LIGHT_STATS_ATTE02,
	LIGHT_STATS_ATTE03,
}LIGHT_STATS;
//--------------------------------------
//クラス宣言
class c_Light
{
#define MAX_MOVE_TIME		(4 * 60)
#define REVLUTION_RANGE_A	(6.0f)
#define REVLUTION_RANGE_B	(4.0f)
public:
	typedef enum
	{
		MOVE_MODE_REVOLUTION = 0,
		MOVE_MODE_MAX,
	}MOVE_MODE;
	c_Light();
	~c_Light();
	void CreatLightTYPE(D3DLIGHTTYPE nType,int  name);
	void CreatLightPointDefault(int name);
	void CreatLightSunDefault(int name);
	void CreatLightSpotDefault(int name,D3DXVECTOR3* target,D3DXVECTOR3 pos);
	void CreatLightSpotDefault(int name,D3DXVECTOR3  target,D3DXVECTOR3 pos);
	void SetLightState(int STATE,D3DXVECTOR3 pos);
	void SetLightState(int STATE,float fInput);
	void SetLightState(int STATE,D3DXCOLOR fInput);


	void ActiveLightSYS(void);
	void SwitchForLight(bool);

	virtual void UpdateLight(void);
	virtual void UninitLight(void);

	D3DLIGHT9*		m_pLight;
	int				m_nLightNumber;
	bool			m_bLookAtTarget;
	D3DXVECTOR3*	m_vTargetPos;

	c_Physic		m_Physic;
	int				m_nMoveMode;
	int				m_nRecTime;
	int				m_nMaxTime;
};

#endif