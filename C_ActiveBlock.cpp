//-----------------------------------------------------------
//CLASS_ACTIVE_BLOCK
//-----------------------------------------------------------
#include "C_ActiveBlock.h"
c_Active_Block::c_Active_Block()
{

}
c_Active_Block::~c_Active_Block()
{
}
void c_Active_Block::InitActiveBlock(void)
{	
	LPCSTR lpzFileName = m_cFileName.GetFileName(FILE_TYPE_BLOCK,BLOCK_TYPE_ACTIVE);
	this->SetFileName(lpzFileName);//(ERROR_MODEL_FILE);
	this->Init_LoadModel();
}
void c_Active_Block::UninitActiveBlock(void)
{
	this->UninitModel();
}
void c_Active_Block::UpdateActiveBlock(D3DXVECTOR3 CenterPos)
{
		 if(GetInputTriggerPOV(INPUT_KEY_L1))
		m_uPlace.y ++;
	else if(GetInputTriggerPOV(INPUT_KEY_R1))
		m_uPlace.y --;
	else if(GetInputTriggerPOV(INPUT_KEY_LEFT))
		m_uPlace.x --;
	else if(GetInputTriggerPOV(INPUT_KEY_RIGHT))
		m_uPlace.x ++;
	else if(GetInputTriggerPOV(INPUT_KEY_UP))
		m_uPlace.z ++;
	else if(GetInputTriggerPOV(INPUT_KEY_DOWN))
		m_uPlace.z --;
	

	if(GetInputPressPOV(INPUT_KEY_3))
		this->m_nActiveStats = ACTIVE_BLOCK_STATS_CREATE;
	else if(GetInputPressPOV(INPUT_KEY_1))
		this->m_nActiveStats = ACTIVE_BLOCK_STATS_DELETE;
	else
		this->m_nActiveStats = ACTIVE_BLOCK_STATS_SELECTING;

	this->m_uPlace.FiledLimitCheckCenter(FIELDPLACE3(MAX_SHIP_SIZE,MAX_SHIP_SIZE,MAX_SHIP_SIZE));

	m_uPlace.AnalysPostionCenter(CenterPos,&m_vPos,BLOCK_SIZE);
	this->UpdateModel();
}
int	c_Active_Block::GetActiveBlockStats(void)
{
	return this->m_nActiveStats;
}
//-----------------------------------------------------------
//End of File
//-----------------------------------------------------------