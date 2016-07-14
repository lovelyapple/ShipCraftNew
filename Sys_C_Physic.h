//-----------------------------------------------------------
//物理エンジン
//-----------------------------------------------------------
#ifndef _C_PHYSIC_H_
#define _C_PHYSIC_H_
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
//--------------------------------------
//マスターズインクルード
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マクロ定義
#define COLLISION_RANGE			(10)
#define PHYSIC_G_VALUE			(9.8f * 0.1f)
//--------------------------------------
//構造体宣言
//--------------------------------------
//クラス宣言
class c_Physic
{
public:
	typedef enum
	{
		HIT_DIR_UP = 0,
		HIT_DIR_DOWN,
		HIT_DIR_LEFT,
		HIT_DIR_RIGHT,
		HIT_DIR_MAX,
	}HIT_DIR;
	c_Physic();
	~c_Physic();

	bool HitBoxWorld_2D(D3DXVECTOR3 Apos,float Ah, float Aw, 
							  D3DXVECTOR3 Bpos,float Bh, float Bw,
							  float fCheckRange); 
	void FreeFallRealTime(D3DXVECTOR3* Speed);
	void HitExclusion2D(D3DXVECTOR3 &BodyPos, float BodySizeX, float BodySizeY,
							D3DXVECTOR3 &BoxPos,	float BoxSizeX,	 float BoxSizeY,
							D3DXVECTOR3 &BodySpeed, float ExclusionRange);
	bool HitCheckDirection2D(D3DXVECTOR3 BodyPos, float BodySizeX,float BodySizeY,
						D3DXVECTOR3 BoxPos, float BoxSizeX,float BoxSizeY,
						D3DXVECTOR3 BodySpeed,HIT_DIR Direction,float checkRange);
	void EllipseRevolution(int mF, int *rF, float *X,float *Y,float a,float b);
private:
};
#endif