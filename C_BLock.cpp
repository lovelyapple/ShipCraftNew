//-----------------------------------------------------------
//CLASS_BLOCK
//-----------------------------------------------------------
#include "C_Block.h"
c_Block::c_Block()
{
}
c_Block::~c_Block()
{
}
void c_Block::UpdateBlockFieldPosInShip(D3DXVECTOR3 CenterPos,FIELDPLACE3 LimitHalf)
{
	FIELDPLACE3 Realplace = m_uPlace;
	Realplace.x -= LimitHalf.x;
	Realplace.y -= LimitHalf.y;
	Realplace.z -= LimitHalf.z;
	Realplace.AnalysPostionCenter(CenterPos,&m_vPos,BLOCK_SIZE);
}
void c_Block::UpdateBlockMatrix(void)
{
	this->UpdateModel();
}

//-----------------------------------------------------------
//End of File
//-----------------------------------------------------------