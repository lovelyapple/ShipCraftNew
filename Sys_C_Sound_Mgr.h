//============================================================================
//C_MGR_SOUND.h
//============================================================================
#ifndef _CLASS_SOUND_MGR_H
#define _CLASS_SOUND_MGR_H

//-----------------------------------
//システムインクルード
#include"Sys_Global_Variable.h"
#include "Sys_Macro.h"

//-----------------------------------
//マスターズインクルード
#include "Sys_C_Sound.h"


//-----------------------------------
//マクロ定義
typedef enum
{
	SOUND_BGM_PLAY = 0,
	SOUND_BGM_MAX,
}SOUND_BGM;
typedef enum
{
	SOUND_SE_SAMPLE = 0,
	SOUND_SE_MAX,
}SOUND_SE;
//-----------------------------------
//クラス宣言
class c_Mgr_Sound 
{
#define MAX_SOUND_BG		(8)
#define MAX_SOUND_SE		(8)
public:
	c_Mgr_Sound();
	~c_Mgr_Sound();
	void Init_SoundMgr(void);
	void Uninit_SoundMgr(void);
	void Update_SoundMgr(void);
	HRESULT CreatSoundBG(int FileNumber, int nReplayMode,long StartPos = 0);
	HRESULT CreatSoundSE(int FileNumber, int nReplayMode,long StartPos = 0);

	void StopSound(int SoundType,int SoundNumber);
	void ContinueSound(int SoundType,int SoundNumber);
private:
	c_Sound*		m_pSoundBG[MAX_SOUND_BG];
	c_Sound*		m_pSoundSE[MAX_SOUND_SE];


};

#endif