//-----------------------------------------------------------
//CLASS_Camera_MANAGER_H
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "C_Camera_Mgr.h"
c_Camera_Mgr::c_Camera_Mgr()
{
	for(int nCamera = 0; nCamera < CAMERA_MAX; nCamera++)
		m_pSysCamera[nCamera] = NULL;
}
void c_Camera_Mgr::Init_CameraMgr(void)
{
	m_pSysCamera[CAMERA_MAIN] = new c_Camera;
	m_pSysCamera[CAMERA_MAIN]-> InitCamera(true);
	m_pSysCamera[CAMERA_MAIN]-> SetCameraPos(D3DXVECTOR3(0.0f,3.0f,-10.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pSysCamera[CAMERA_MAIN]-> SystemSet_D3DTVIEW();

}
void c_Camera_Mgr::Uninit_CameraMgr(void)
{
	m_pSysCamera[CAMERA_MAIN]->UninitCamera();
	SAFE_DELETE(m_pSysCamera[CAMERA_MAIN]);	
}
void c_Camera_Mgr::Update_CameraMgr(void)
{
	m_pSysCamera[CAMERA_MAIN]->UpdateCameraRevolution();
}
void c_Camera_Mgr::Draw_CameraMgr(void)
{
	m_pSysCamera[CAMERA_MAIN]->DrawCamera();
}
