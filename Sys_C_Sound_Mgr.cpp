//============================================================================
//C_MGR_SOUND.h
//============================================================================
//-----------------------------------
//システムインクルード
#include "Sys_C_Sound_Mgr.h"
const char* FileNameBGM[] = {
	"data/Sound/BGM/BGM_Sample.wav",
};
const char* FileNameSE[] = {
	"data/Sound/SE/IceSlash.wav",
};
c_Mgr_Sound::c_Mgr_Sound()
{

}
c_Mgr_Sound::~c_Mgr_Sound()
{
}
void c_Mgr_Sound::Init_SoundMgr(void)
{
	for(int nS = 0; nS < MAX_SOUND_BG; nS++)
		m_pSoundBG[nS] = NULL;

	for(int nS = 0; nS < MAX_SOUND_SE; nS++)
		m_pSoundSE[nS] = NULL;

}
void c_Mgr_Sound::Uninit_SoundMgr(void)
{
	for(int nS = 0; nS < MAX_SOUND_BG; nS++)
		if(m_pSoundBG[nS])
		{
			m_pSoundBG[nS]->UnInitSound();
			SAFE_DELETE(m_pSoundBG[nS]);
		}
	for(int nS = 0; nS < MAX_SOUND_SE; nS++)
		if(m_pSoundSE[nS])
		{
			m_pSoundSE[nS]->UnInitSound();
			SAFE_DELETE(m_pSoundSE[nS]);
		}

}

void c_Mgr_Sound::Update_SoundMgr(void)
{
	for(int nS = 0; nS < MAX_SOUND_BG; nS++)
	{
		if(!m_pSoundBG[nS]) continue;
			if(m_pSoundBG[nS]->UpdateSound())
			{
				m_pSoundBG[nS]->UnInitSound();
				SAFE_DELETE(m_pSoundBG[nS]);
			}
	}

	for(int nS = 0; nS < MAX_SOUND_SE; nS++)
	{
		if(!m_pSoundSE[nS]) continue;
			if(m_pSoundSE[nS]->UpdateSound())
			{
				m_pSoundSE[nS]->UnInitSound();
				SAFE_DELETE(m_pSoundSE[nS]);
			}
	}
}
HRESULT c_Mgr_Sound::CreatSoundBG(int FileName,int nReplayMode,long StartPos)
{
	for(int nS = 0; nS < MAX_SOUND_BG; nS++)
	{
		if(m_pSoundBG[nS]) continue;
		if(nS >= MAX_SOUND_BG) return S_FALSE;
		
		m_pSoundBG[nS] = new c_Sound(FileNameBGM[FileName]);
		m_pSoundBG[nS]->InitSound(nReplayMode,StartPos);
		m_pSoundBG[nS]->PlaySoundCycle();
		break;
	}
	return S_OK;
}
HRESULT c_Mgr_Sound::CreatSoundSE(int FileName,int nReplayMode,long StartPos)
{
	for(int nS = 0; nS < MAX_SOUND_SE; nS++)
	{
		if(m_pSoundSE[nS]) continue;
		if(nS >= MAX_SOUND_SE) return S_FALSE;
		
		m_pSoundSE[nS] = new c_Sound(FileNameSE[FileName]);
		m_pSoundSE[nS]->InitSound(nReplayMode,StartPos);
		if(nReplayMode != REPLAY_MODE_OFF)
		m_pSoundSE[nS]->PlaySoundCycle();

		break;
	}
	return S_OK;
}
void c_Mgr_Sound::StopSound(int SoundType,int SoundNumber)
{
	if(SoundType == 0)
	{
		if(!m_pSoundBG[SoundNumber]){}
		else
			m_pSoundBG[SoundNumber]->StopSound();
	}
	else
	{
		if(!m_pSoundSE[SoundNumber]){}
		else
			m_pSoundSE[SoundNumber]->StopSound();
	}


}
void c_Mgr_Sound::ContinueSound(int SoundType,int SoundNumber)
{
	if(SoundType == 0)
	{
		if(!m_pSoundBG[SoundNumber]){}
		else
			m_pSoundBG[SoundNumber]->PlaySoundContinue();
	}
	else
	{
		if(!m_pSoundSE[SoundNumber]){}
		else
			m_pSoundSE[SoundNumber]->PlaySoundContinue();
	}
}
