//-----------------------------------------------------------
//SYS_USER_DEFINITION_H
//-----------------------------------------------------------
#ifndef SYS_USER_DEFINITION_H
#define SYS_USER_DEFINITION_H
#include "Sys_Include.h"
//-----------------------------------------------------------
//FIELD_PLACE_2D
//-----------------------------------------------------------
class FIELDPLACE2
{
	public:
	FIELDPLACE2();
	FIELDPLACE2(int inputx,int inputy);
	int x,y;

	void FiledLimitCheckNormal(FIELDPLACE2 Limit);
	void FiledLimitCheckCenter(FIELDPLACE2 Limit);

	void AnalysPostionNormal(D3DXVECTOR3 CenterPos,D3DXVECTOR3* pos,float UnitSize);
	void AnalysPostionCenter(D3DXVECTOR3 CenterPos,D3DXVECTOR3* pos,float UnitSize);	
	FIELDPLACE2* GetFieldPlace(void);

};

//-----------------------------------------------------------
//FIELD_PLACE_3D
//-----------------------------------------------------------
class FIELDPLACE3
{
	public:
	FIELDPLACE3();
	FIELDPLACE3(int inputx,int inputy,int inputz);
	int x,y,z;

	void FiledLimitCheckNormal(FIELDPLACE3 Limit);
	void FiledLimitCheckCenter(FIELDPLACE3 LimitHalf);

	void AnalysPostionNormal(D3DXVECTOR3 CenterPos,D3DXVECTOR3* pos,float UnitSize,FIELDPLACE3 Limit);
	void AnalysPostionCenter(D3DXVECTOR3 CenterPos,D3DXVECTOR3* pos,float UnitSize);
	FIELDPLACE3* GetFieldPlace(void);

};
void SetAnti_aliasing(bool bSwitch,LPDIRECT3DDEVICE9 pDevice);

#endif