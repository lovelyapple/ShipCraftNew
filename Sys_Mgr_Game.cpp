//-----------------------------------------------------------
//SYS_MGR_GAME_H
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "Sys_Mgr_Game.h"

//---------------------------------------------------------
//MGRのインクルード
c_Mgr_Sound*		g_pMgr_Sound;		// サウンドマネージャ		
c_Test_Mgr*			g_pMgr_Test;		// テストオブジェクトマネージャ
c_Camera_Mgr*		g_pMgr_Camera;		// カメラマネージャ
c_Mgr_EditorMode*	g_pMgr_Editor;		// エディタマネージャ
c_Light_Mgr*		g_pMgr_Light;		// ライトマネージャ
HRESULT Init_SysGame(void)
{
	//-----------------------------------------------------
	//テストオブジェクトモード
	g_pMgr_Test	= new c_Test_Mgr;
	g_pMgr_Test->UseTestMgr(true);
	if(g_pMgr_Test->GetTestMgrUse())
		g_pMgr_Test->Init_Test_Mgr();
	//テストオブジェクトモード
	//-----------------------------------------------------

	//-----------------------------------------------------
	//システムのMgr処理
	g_pMgr_Sound = new c_Mgr_Sound;
	g_pMgr_Sound->Init_SoundMgr();
	//g_pMgr_Sound->CreatSoundBG(0,REPLAY_MODE_START);

	g_pMgr_Camera = new c_Camera_Mgr;
	g_pMgr_Camera->Init_CameraMgr();

	g_pMgr_Light	= new c_Light_Mgr;
	g_pMgr_Light->Init_LightMgr();
	//システムのMgr処理
	//-----------------------------------------------------

	//-----------------------------------------------------
	//エディタモード
	g_pMgr_Editor = new  c_Mgr_EditorMode(g_pMgr_Camera,g_pMgr_Light);
	g_pMgr_Editor->Init_Mgr_EditorMode();
	//エディタモード
	//-----------------------------------------------------



	return S_OK;
}

void	Uninit_SysGame(void)
{
	//-----------------------------------------------------
	//システムのMgr処理
	g_pMgr_Sound->Uninit_SoundMgr();
	SAFE_DELETE(g_pMgr_Sound);
	g_pMgr_Camera->Uninit_CameraMgr();
	SAFE_DELETE(g_pMgr_Camera);
	//システムのMgr処理
	//-----------------------------------------------------
	//-----------------------------------------------------
	//エディタモード
	g_pMgr_Editor->Uninit_Mgr_EditorMode();
	SAFE_DELETE(g_pMgr_Editor);
	g_pMgr_Light->Uninit_LightMgr();
	SAFE_DELETE(g_pMgr_Light);
	//エディタモード
	//-----------------------------------------------------
	//-----------------------------------------------------
	//テストオブジェクトモード
	if(g_pMgr_Test->GetTestMgrUse())
		g_pMgr_Test->Uninit_Test_Mgr();
	SAFE_DELETE(g_pMgr_Test);
	//テストオブジェクトモード
	//-----------------------------------------------------

}

void	Update_SysGame(void)
{
	//-----------------------------------------------------
	//システムのMgr処理	
	g_pMgr_Sound->Update_SoundMgr();
	if(GetKeyboardTrigger(DIK_9))
		g_pMgr_Sound->StopSound(0,0);
	if(GetKeyboardTrigger(DIK_0))
		g_pMgr_Sound->ContinueSound(0,0);

	g_pMgr_Camera->Update_CameraMgr();
	//システムのMgr処理
	//-----------------------------------------------------
	//-----------------------------------------------------
	//エディタモード
	g_pMgr_Editor->Update_Mgr_EditorMode();
	//エディタモード
	//-----------------------------------------------------
	//-----------------------------------------------------
	//テストオブジェクトモード
	if(g_pMgr_Test->GetTestMgrUse())
		g_pMgr_Test->Update_Test_Mgr();
	//テストオブジェクトモード
	//-----------------------------------------------------


}

void	Draw_SysGame(void)
{
	//-----------------------------------------------------
	//システムのMgr処理	
	g_pMgr_Camera->Draw_CameraMgr();
	g_pMgr_Light->Draw_LightMgr();
	//システムのMgr処理
	//-----------------------------------------------------
	//-----------------------------------------------------
	//エディタモード
	g_pMgr_Editor->Draw_Mgr_EditorMode();
	//エディタモード
	//-----------------------------------------------------
	//-----------------------------------------------------
	//テストオブジェクトモード
	if(g_pMgr_Test->GetTestMgrUse())
		g_pMgr_Test->Draw_Test_Mgr();
	//テストオブジェクトモード
	//-----------------------------------------------------

}
