//============================================================================
//sound.h
//============================================================================
#ifndef _C_MASTER_SE_SOUND_H_
#define _C_MASTER_SE_SOUND_H_
//-----------------------------------
//システムインクルード
#include"Sys_Global_Variable.h"
#include "Sys_Macro.h"


#include "Sys_Input.h"

//-----------------------------------
//マクロ定義

typedef enum
{
	REPLAY_MODE_START = 0,	// 最初から再生	
	REPLAY_MODE_MIDDLE,		// 指定位置から再生
	REPLAY_MODE_HANDLE,		// 手動再生
	REPLAY_MODE_OFF,		// ループ再生しない
	REPLAY_MODE_MAX,

}REPLAY_MODE_SOUND;
typedef enum
{
	PLAY_MODE_PLAYING = 0,
	PLAY_MODE_STOP,
	PLAY_MODE_MAX,
}PLAY_MODE;
//----------------------------------


//----------------------------------
//クラス宣言

class c_Sound 
{
public:
	c_Sound();
	c_Sound(LPCSTR szFileName);
	~c_Sound();

	HRESULT InitSound(int mode, LONG position = 0);	// 読み込み初期化
	HRESULT	UnInitSound(void);						// サウンドの開放
	void	ResSoundStats(void);					// サウンドステータスの初期化
	bool	UpdateSound(void);						// 更新処理

	void	ChangeVolume(int nVolume);				// 音量変更
	void	PlaySoundOnce(void);					// 再生
	void	PlaySoundCycle(void);					// 繰り返し再生
	void	StopSound(void);						// 一時停止
	void	PlaySoundContinue(void);			
	void	SetReplayMode(int nSEMode);				// リプレイモードの変更
	int		CheckSoundOver(void);					// サウンドの放送状態チェック

	void	SetSoundReplayMode(int Replaymode, LONG position = 0);//モードの設定
	
private:
	// サウンド関係変数
	LPDIRECTSOUND8				g_pDSound;			// SEのDirectSoudオブジェクト
	LPDIRECTSOUNDBUFFER			g_pDSBuffer;		// SEのDirectSoundセカンダリーバッファー
	
	LPCSTR						m_szFileName;		// このサウンドの名前
	REPLAY_MODE_SOUND			m_nSEReplayMode;	// リプレイモード

	LONG						m_lStartPoint;		// SE用ループ再生位置
	LONG						m_lRecPoint;		// 現在の再生位置

	int							m_nPlayMode;		// 再生するか

protected:

};
#endif