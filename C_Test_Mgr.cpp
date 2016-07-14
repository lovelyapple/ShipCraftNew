//-----------------------------------------------------------
//CLASS_TEST_MANAGER_H
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "C_Test_Mgr.h"
c_Test_Mgr::c_Test_Mgr()
{
	m_pTestMessage	= new c_UI_MessageBox;
}
void c_Test_Mgr::Init_Test_Mgr(void)
{
	m_pTestMessage->Init_MessageBox();
}
void c_Test_Mgr::Update_Test_Mgr(void)
{

	m_pTestMessage->Update_MessageBox();
}
void c_Test_Mgr::Uninit_Test_Mgr(void)
{
	m_pTestMessage->Uninit_MessageBox();
	SAFE_DELETE(m_pTestMessage);
}
void c_Test_Mgr::Draw_Test_Mgr(void)
{
	m_pTestMessage->Draw_MessageBox();
}
void c_Test_Mgr:: UseTestMgr(bool bInput)
{
	m_bTestVersion = bInput;
}
bool c_Test_Mgr::GetTestMgrUse(void)
{
	return m_bTestVersion;
}

//-----------------------------------------------------------
//End of File