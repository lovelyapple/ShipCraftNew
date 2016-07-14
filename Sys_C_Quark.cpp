//-----------------------------------------------------------
//C_PARTICLE_QUARK_H
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "Sys_C_Quark.h"
c_Quark::c_Quark()
{
	ResetStatus_Quark();
}
c_Quark::~c_Quark()
{
}
void c_Quark::Update_Matrix_Quark(void)
{
	D3DXMATRIX	matRotate;		// 回転マトリックス
	D3DXMATRIX	matTrans;		// 平行移動マトリックス
	D3DXMATRIX*	pmatInv;
	D3DXVECTOR3 vDir;
	D3DM_INIT(m_mMatrix);

	D3DXMatrixRotationYawPitchRoll(&matRotate,m_vRot.y,m_vRot.x,m_vRot.z);	// 回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans,m_vPos.x,m_vPos.y,m_vPos.z);	// 平行移動マトリックスを生成

	m_mMatrix = matRotate * matTrans;
	if(m_bWatchCamera)
	{
		pmatInv = &m_mMatrix;
		float _41 = m_mMatrix._41;
		float _42 = m_mMatrix._42;
		float _43 = m_mMatrix._43;
		D3DXMatrixInverse(pmatInv, NULL, g_matView);
		pmatInv->_41 = _41;  //オフセットを切る（回転行列だけにして）
		pmatInv->_42 = _42;
		pmatInv->_43 = _43;
	}
}
int c_Quark::RunAndGetQuarkLife(void)
{
	m_nLife--;
	if(m_nLife < 0)
		return 0;
	else
		return 1;
}

void c_Quark:: RunQuarkAnimation(void)
{

	m_nRecTime ++;
	if(m_nRecTime > m_nTimePerFrame)
	{
		m_nRecTime -= m_nTimePerFrame;
		m_nRecFrame = ( m_nRecFrame + 1 ) % m_nMaxFrame;
	}

}

void c_Quark::ResetStatus_Quark(void)
{
	D3DV_INIT(m_vPos);
	D3DV_INIT(m_vDestPos);
	D3DV_INIT(m_vSpeed);
	D3DV_INIT(m_vSpeedMin);
	D3DV_INIT(m_vSpeedMax);
	D3DV_INIT(m_vRot);
	D3DM_INIT(m_mMatrix);

	DATAI_INIT(m_fAlpha);
	DATAO_INIT(m_nLife);
	DATAO_INIT(m_nTime);
	DATAO_INIT(m_nMode);
	DATAO_INIT(m_nType);

	m_bWatchCamera	= false;
}
void c_Quark::SetQuarkStats(int stats, D3DXVECTOR3 vInput)
{
	switch(stats)
	{
	case QUARK_STATS_POS:		m_vPos = vInput;
		break;
	case QUARK_STATS_DEST_POS:	m_vDestPos = vInput;
		break;
	case QUARK_STATS_SPEED:		m_vSpeed = vInput;
		break;
	case QUARK_STATS_SPEED_MIN:	m_vSpeedMin = vInput;
		break;
	case QUARK_STATS_SPEED_MAX:	m_vSpeedMax = vInput;
		break;
	case QUARK_STATS_ROT:		m_vRot = vInput;
		break;
	case QUARK_STATS_SIZE:m_vSize = vInput;
		break;
	}

}
void c_Quark::SetQuarkStats(int stats, float fInput)
{
	switch(stats)
	{
	case QUARK_STATS_ALPHA:m_fAlpha = fInput;
		break;

	}
}
void c_Quark::SetQuarkStats(int stats, int nInput)
{
	switch(stats)
	{
	case QUARK_STATS_LIFE:m_nLife = nInput;
		break;
	case QUARK_STATS_TIME:m_nTime = nInput;
		break;
	case QUARK_STATS_MAX_TIME:m_nMaxTime = nInput;
		break;
	case QUARK_STATS_MODE:m_nMode = nInput;
		break;
	case QUARK_STATS_TYPE:m_nType = nInput;
		break;
	case QUARK_STATS_MAXFRAME:m_nMaxFrame = nInput;
		break;
	case QUARK_STATS_USIZE:m_fVerTexUSize = nInput;
		break;
	case QUARK_STATS_TIMEPERFRAME:m_nTimePerFrame = nInput;
		break;
	}
}
void c_Quark::SetQuarkStats(int stats, bool bInput)
{
	switch(stats)
	{
	case QUARK_STATS_BANIMATION:m_bAnimation = bInput;
		break;

	}
}
bool c_Quark::GetAnimationFlag(void)
{
	return this->m_bAnimation;
}
D3DXVECTOR3  c_Quark::GetQuarkSize(void)
{
	return this->m_vSize;
}
D3DXVECTOR3  c_Quark::GetQuarkPos(void)
{
	return this->m_vPos;
}
float		 c_Quark::GetQuarkUsize(void)
{
	return this->m_fVerTexUSize;
}
float		 c_Quark::GetQuarkAlpha(void)
{
	return this->m_fAlpha;
}
int			 c_Quark::GetQuarkRecFrame(void)
{
	return this->m_nTimePerFrame;
}