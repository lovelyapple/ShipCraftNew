//-----------------------------------------------------------
//CLASS_UI_EDITOR_BLOCKMENU
//-----------------------------------------------------------

//--------------------------------------
//システムインクルード
#include "C_UI_BlockMenu.h"

c_BlockMenu::c_BlockMenu()
{
	for(int nS = 0; nS < MAX_BLOCK_SELECTION; nS ++)
	{
		m_pSelection[nS] = NULL;
	}
	m_pGameCamera = NULL;
	m_nRecSelection = 0;
}
c_BlockMenu::~c_BlockMenu()
{
}
void c_BlockMenu::Init_BlockMenu(c_Camera_Mgr* pCameraMgr)
{
	m_pGameCamera = pCameraMgr;
	D3DXMATRIX CamaraMatrix;
	CamaraMatrix = *m_pGameCamera->m_pSysCamera[0]->GetCameraMatrix();
	for(int nS = 0; nS < MAX_BLOCK_SELECTION; nS ++)
	{
		//if(!m_pSelection[nS]) continue;
		m_pSelection[nS] = new c_Selection;
		LPCSTR lpzName = m_FileMgr.GetFileName(FILE_TYPE_BLOCK_MENU,nS);
		m_pSelection[nS]->Init_Selection(lpzName);

		D3DXVECTOR3 SePos;
		D3DXVECTOR3 BgPos;
		D3DXVECTOR3 ListPos = BlockMenuPos;
		ListPos.x += SelectionSize.x * 2 * nS;
		D3DXVec3TransformCoord(&SePos,&ListPos,&CamaraMatrix);
		ListPos	  += SelectionBGPos;
		D3DXVec3TransformCoord(&BgPos,&ListPos,&CamaraMatrix);
		m_pSelection[nS]->Set_SelectionPos(SePos,BgPos);
	}
}
void c_BlockMenu::Uninit_BlockMenu(void)
{
	for(int nS = 0; nS < MAX_BLOCK_SELECTION; nS ++)
	{
		if(!m_pSelection[nS]) continue;
		m_pSelection[nS]->Uninit_Selection();
		SAFE_DELETE(m_pSelection[nS]);
	}
	m_pGameCamera = NULL;
}
void c_BlockMenu::Update_BlockMenu(void)
{
	D3DXMATRIX	CamaraMatrix;
	CamaraMatrix = *m_pGameCamera->m_pSysCamera[0]->GetCameraMatrix();	
	for(int nS = 0; nS < MAX_BLOCK_SELECTION; nS ++)
	{
		if(!m_pSelection[nS]) continue;
		if(m_nRecSelection == nS)
			m_pSelection[nS]->m_bActived = true;
		else
			m_pSelection[nS]->m_bActived = false;

		D3DXVECTOR3 SePos;
		D3DXVECTOR3 BgPos;
		D3DXVECTOR3 ListPos = BlockMenuPos;
		ListPos.x += SelectionSize.x * 2 * nS;
		D3DXVec3TransformCoord(&SePos,&ListPos,&CamaraMatrix);
		ListPos	  += SelectionBGPos;
		D3DXVec3TransformCoord(&BgPos,&ListPos,&CamaraMatrix);
		m_pSelection[nS]->Set_SelectionPos(SePos,BgPos);

		m_pSelection[nS]->Update_Selection();
	}

	if(GetInputTriggerPOV(INPUT_KEY_R2))
	{
		m_nRecSelection = (m_nRecSelection + 1) % MAX_BLOCK_SELECTION;
	}
	else if(GetInputTriggerPOV(INPUT_KEY_L2))
	{
		m_nRecSelection = (MAX_BLOCK_SELECTION + m_nRecSelection - 1) % MAX_BLOCK_SELECTION;
	}

}
void c_BlockMenu::Draw_BlockMenu(void)
{
	for(int nS = 0; nS < MAX_BLOCK_SELECTION; nS ++)
	{
		if(!m_pSelection[nS]) continue;
		m_pSelection[nS]->Draw_Selection();
	}
}
int c_BlockMenu::GetRecentSelection(void)
{
	return this->m_nRecSelection;

}

//-----------------------------------------------------------
//End of File
//-----------------------------------------------------------