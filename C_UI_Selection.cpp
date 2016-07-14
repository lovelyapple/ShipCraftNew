//-----------------------------------------------------------
//CLASS_UI_EDITOR_BLOCKMENU
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "C_UI_Selection.h"
//--------------------------------------
//マスターズインクルード
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マネージャーインクルード
c_Selection::c_Selection()
{
	m_pSelectionEntity	= NULL;
	m_pSelectionBG		= NULL;
	m_nRecTime		= 0;
	m_nMaxTime		= 1 * 60;
	m_bActived		= false;
}
c_Selection::~c_Selection()
{
}
void c_Selection::Init_Selection(LPCSTR FileName)
{
	HRESULT hr;
	m_pSelectionEntity = new c_Primitive3D;
	m_pSelectionEntity->SetFileName(FileName);
	m_pSelectionEntity->SetSize(SelectionSize);
	hr = m_pSelectionEntity->Init_Primitive();
	m_pSelectionEntity->SetWatchCamera(true);
	

	m_pSelectionBG = new c_Primitive3D;
	hr = m_pSelectionBG->CreatePrimitiveBuffOnly();
	m_pSelectionBG->SetWatchCamera(true);
	m_pSelectionBG->SetSize(SelectionSize);
}
void c_Selection::Uninit_Selection(void)
{
	m_pSelectionEntity->Uninit_Primitive();
	SAFE_DELETE(m_pSelectionEntity);
	m_pSelectionBG->Uninit_Primitive();
	SAFE_DELETE(m_pSelectionBG);
}
void c_Selection::Update_Selection(void)
{
	m_pSelectionEntity->Update_PrimitiveNormal();
	m_pSelectionBG->Update_PrimitiveMatrixOnly();
	float Alpha = 0.0f;
	if(m_bActived)
	{
		m_nRecTime = (m_nRecTime + 1) % m_nMaxTime;
		Alpha = (sinf(((float)(m_nRecTime) * 2 * 3.14f / m_nMaxTime ))  + 1.0f) / 2;
		Alpha *= 0.5f;
		Alpha += 0.1f;
	}
	else
		Alpha = 0.1f;
	m_pSelectionBG->SetVerTexBuffSize();
	m_pSelectionBG->SetAlpha(Alpha);
	m_pSelectionBG->SetVerTexBuffAlpha();
}
void c_Selection::Draw_Selection(void)
{
	m_pSelectionEntity->DrawPrimitive();
	m_pSelectionBG->DrawPrimitiveOtherTexture(NULL);
}
void c_Selection::Set_SelectionPos(D3DXVECTOR3 SePos,D3DXVECTOR3 BgPos)
{
	m_pSelectionEntity->SetPos(SePos);
	m_pSelectionBG->SetPos(BgPos);
}


//-----------------------------------------------------------
//End of File
//-----------------------------------------------------------