//-----------------------------------------------------------
//C_MGR_STATIONARY_H
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "C_EditorStModel_Mgr.h"
c_EditorStModel_Mgr::c_EditorStModel_Mgr(){
	for(int nM = 0; nM < EDITOR_MODEL_MAX; nM++)
		m_pStationaryModel[nM] = NULL;
}

c_EditorStModel_Mgr::~c_EditorStModel_Mgr()
{
}
void c_EditorStModel_Mgr::Init_EditorStModel_Mgr(void)
{//FILE_TYPE_EDITOR
	LPCSTR lpzFileName;
	lpzFileName = m_cFileNameMgr.GetFileName(FILE_TYPE_EDITOR,EDITOR_MODEL_CRAFT_TABLE);
	m_pStationaryModel[EDITOR_MODEL_CRAFT_TABLE]  = new c_Model;
	m_pStationaryModel[EDITOR_MODEL_CRAFT_TABLE]->SetFileName(lpzFileName);

	for(int nM = 0; nM < EDITOR_MODEL_MAX; nM++)
		if(m_pStationaryModel[nM])
		m_pStationaryModel[nM]->Init_LoadModel();

}
void c_EditorStModel_Mgr::Uninit_EditorStModel_Mgr(void)
{
	for(int nM = 0; nM < EDITOR_MODEL_MAX; nM++)
		if(m_pStationaryModel[nM])
		{
			m_pStationaryModel[nM]->UninitModel();
			SAFE_DELETE(m_pStationaryModel[nM]);
		}
}
void c_EditorStModel_Mgr::Update_EditorStModel_Mgr(void)
{
	for(int nM = 0; nM < EDITOR_MODEL_MAX; nM++)
		if(m_pStationaryModel[nM])
		{
			m_pStationaryModel[nM]->UpdateModel();
		}
}
void c_EditorStModel_Mgr::Draw_EditorStModel_Mgr(void)
{
	for(int nM = 0; nM < EDITOR_MODEL_MAX; nM++)
		if(m_pStationaryModel[nM])
		{
			m_pStationaryModel[nM]->DrawModel();
		}
}

//-----------------------------------------------------------
//End of File
//-----------------------------------------------------------