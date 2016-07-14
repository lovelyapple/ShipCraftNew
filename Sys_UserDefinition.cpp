#include "Sys_UserDefinition.h"
//-----------------------------------------------------------
//FIELD_PLACE_2D
//-----------------------------------------------------------
FIELDPLACE2::FIELDPLACE2()
{
	x = 0; y= 0;
}
FIELDPLACE2::FIELDPLACE2(int inputx,int inputy)
{
	x = inputx; y = inputy;
}
void FIELDPLACE2::FiledLimitCheckNormal(FIELDPLACE2 Limit)
{
	if(x < 0) x = 0;
	else if(x > Limit.x) x = Limit.x;

	if(y < 0) y = 0;
	else if(y > Limit.y) y = Limit.y;

}
void FIELDPLACE2::FiledLimitCheckCenter(FIELDPLACE2 Limit)
{
	if(x < -Limit.x/2) x = -Limit.x/2;
	else if(x > Limit.x/2) x = Limit.x/2;

	if(y < -Limit.y/2) y = -Limit.y/2;
	else if(y > Limit.y/2) y = Limit.y/2;
}
FIELDPLACE2* FIELDPLACE2::GetFieldPlace(void)
{
	return this;
}
void FIELDPLACE2::AnalysPostionNormal(D3DXVECTOR3 CenterPos,D3DXVECTOR3* pos,float UnitSize)
{
}
void FIELDPLACE2::AnalysPostionCenter(D3DXVECTOR3 CenterPos,D3DXVECTOR3* pos,float UnitSize)
{
	pos->x = CenterPos.x + x * UnitSize;
	pos->y = CenterPos.x + y * UnitSize;
}
//-----------------------------------------------------------
//FIELD_PLACE_3D
//-----------------------------------------------------------
FIELDPLACE3::FIELDPLACE3()
{
	x = 0; y= 0; z = 0;
}
FIELDPLACE3::FIELDPLACE3(int inputx,int inputy,int inputz)
{
	x = inputx;y = inputy;z = inputz;
}
void FIELDPLACE3::FiledLimitCheckNormal(FIELDPLACE3 Limit)
{
	if(x < 0) x = 0;
	else if(x > Limit.x) x = Limit.x;

	if(y < 0) y = 0;
	else if(y > Limit.y) y = Limit.y;

	if(z < 0) z = 0;
	else if(z > Limit.y) z = Limit.y;
}

void FIELDPLACE3::FiledLimitCheckCenter(FIELDPLACE3 LimitHalf)
{
	if(x < -LimitHalf.x)		
		x = -LimitHalf.x;
	else if(x > LimitHalf.x)  
		x =  LimitHalf.x;

	if(y < -LimitHalf.y)		
		y = -LimitHalf.y;
	else if(y > LimitHalf.y)	
		y =  LimitHalf.y;

	if(z < -LimitHalf.z)		
		z = -LimitHalf.z;
	else if(z > LimitHalf.z)	
		z =  LimitHalf.z;
}
void FIELDPLACE3::AnalysPostionNormal(D3DXVECTOR3 CenterPos,D3DXVECTOR3* pos,float UnitSize,FIELDPLACE3 Limit)
{
}
void FIELDPLACE3::AnalysPostionCenter(D3DXVECTOR3 CenterPos,D3DXVECTOR3* pos,float UnitSize)
{
	pos->x = CenterPos.x + (x) * UnitSize;
	pos->y = CenterPos.y + (y) * UnitSize;
	pos->z = CenterPos.z + (z) * UnitSize;
}

FIELDPLACE3* FIELDPLACE3::GetFieldPlace(void)
{
	return this;
}
//-----------------------------------------------------------
//アンチェアリングのONとOFF
//-----------------------------------------------------------
void SetAnti_aliasing(bool bSwitch,LPDIRECT3DDEVICE9 pDevice)
{
	if(bSwitch)
	{
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER,
				D3DTEXF_LINEAR);
		pDevice->SetSamplerState(0, D3DSAMP_MINFILTER,
				D3DTEXF_LINEAR);;
	}
	else
	{
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER,
				D3DTEXF_NONE);
		pDevice->SetSamplerState(0, D3DSAMP_MINFILTER,
				D3DTEXF_NONE);
	}
}
