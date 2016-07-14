//-----------------------------------------------------------
//CLASS_TEST_MANAGER_H 

//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "Sys_Mode_Editor_Mgr.h"
c_Mgr_EditorMode::c_Mgr_EditorMode(c_Camera_Mgr* pCamera_Mgr,c_Light_Mgr* pLight_Mgr)
{
	m_pCamera_Mgr	= pCamera_Mgr;
	m_pLight_Mgr	= pLight_Mgr;
}
void c_Mgr_EditorMode::Uninit_Mgr_EditorMode(void)
{
	m_pCamera_Mgr	= NULL;
	m_pLight_Mgr	= NULL;

	m_pCamera_Mgr	= NULL;

	m_pShip->UninitShip();
	SAFE_DELETE(m_pShip);
	m_BlockMenu->Uninit_BlockMenu();
	SAFE_DELETE(m_BlockMenu);
	SAFE_DELETE(m_pFont);
}
void c_Mgr_EditorMode::Init_Mgr_EditorMode(void)
{
	m_pShip			= new c_Ship;
	m_pShip->InitShip();
	m_pShip->SetShipName(DEFAULT_SHIP_NAME);

	m_pFont			= new c_Font;
	m_pFont->CreatFont(NULL,0.0f);
	
	m_pAcitveBLock	= new c_Active_Block;
	m_pAcitveBLock->InitActiveBlock();
	m_pAcitveBLock->m_vCenterPos = m_pShip->GetCenterpos();

	this->m_pStModel_Mgr = new c_EditorStModel_Mgr;
	m_pStModel_Mgr->Init_EditorStModel_Mgr();

	m_BlockMenu		= new c_BlockMenu;
	m_BlockMenu->Init_BlockMenu(m_pCamera_Mgr);
}
void c_Mgr_EditorMode::Update_Mgr_EditorMode(void)
{
	m_pAcitveBLock->UpdateActiveBlock(m_pShip->GetCenterpos());
	int ActiveLBlockStats = m_pAcitveBLock->GetActiveBlockStats();
	int nType = m_BlockMenu->GetRecentSelection();
	FIELDPLACE3 placeInShip = *m_pAcitveBLock->m_uPlace.GetFieldPlace();
	m_pShip->ShipPlaceChange(&placeInShip);
	switch(ActiveLBlockStats)
	{
	case   ACTIVE_BLOCK_STATS_CREATE:
			m_pShip->CreateBlock(placeInShip,nType);
		break;
	case  ACTIVE_BLOCK_STATS_DELETE:
			m_pShip->DeleteBlock(placeInShip);
		break;
	}

	m_pShip->UpdateShip();
	
	m_pStModel_Mgr->Update_EditorStModel_Mgr();
	m_pCamera_Mgr->Update_CameraMgr();
	
	m_BlockMenu->Update_BlockMenu();

}

void c_Mgr_EditorMode::Draw_Mgr_EditorMode(void)
{
	m_pCamera_Mgr->Draw_CameraMgr();
	m_pAcitveBLock->DrawModel();
	m_pShip->DrawShip();
	m_pStModel_Mgr->Draw_EditorStModel_Mgr();
	SetAnti_aliasing(false,g_pD3DDevice);
	m_BlockMenu->Draw_BlockMenu();
	SetAnti_aliasing(true,g_pD3DDevice);

	FIELDPLACE3 place = *m_pAcitveBLock->m_uPlace.GetFieldPlace();
	m_pFont->DrawCord("Place.x",place.x,D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pFont->DrawCord("Place.y",place.y,D3DXVECTOR3(0.0f,16.0f,0.0f));
	m_pFont->DrawCord("Place.z",place.z,D3DXVECTOR3(0.0f,32.0f,0.0f));
}

//-----------------------------------------------------------
//End of File