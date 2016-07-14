//============================================================================
//C_Master_SE_Sound.h
//============================================================================
//-----------------------------------
//システムインクルード
#include "Sys_C_Sound.h"
#pragma warning ( disable : 4996 )
c_Sound::c_Sound()
{
	ResSoundStats();
}
c_Sound::~c_Sound()
{
}

c_Sound::c_Sound(LPCSTR szFileName)
{
	ResSoundStats();
	m_szFileName	= szFileName;
}
void c_Sound::ResSoundStats(void)
{
	m_szFileName	= NULL;
	g_pDSound		= NULL;
	g_pDSBuffer		= NULL;
	m_lStartPoint	= 0;
	m_lRecPoint		= 0;
	m_nSEReplayMode	= REPLAY_MODE_OFF;
	m_nPlayMode		= PLAY_MODE_STOP;
}

HRESULT c_Sound::UnInitSound(void)
{
	// DirectSoundの解放
	SAFE_RELEASE(g_pDSBuffer);
	SAFE_RELEASE(g_pDSound);
	return S_OK;
}
int c_Sound::CheckSoundOver(void)
{
	DWORD dwStatus;
	g_pDSBuffer->GetStatus(&dwStatus);			//現在の状態を取得

	if(m_nPlayMode != PLAY_MODE_STOP)			// すでにSTOP状態のサウンドに対してチェックしない
	if((dwStatus & DSBSTATUS_PLAYING) == 0)
	{
		m_nPlayMode = PLAY_MODE_STOP;
	}
	else
	{
		m_nPlayMode = PLAY_MODE_PLAYING;
	}
	
	return m_nPlayMode;
}
bool c_Sound::UpdateSound(void)
{
	if(CheckSoundOver() == PLAY_MODE_STOP)	//演奏が終わったら
	{
		switch(m_nSEReplayMode)
		{
		case REPLAY_MODE_START:
			//g_pDSBuffer->SetCurrentPosition(m_lStartPoint);	// 開始位置を変更
			//g_pDSBuffer->Play(0,0,0);							// 
			m_nPlayMode	= PLAY_MODE_PLAYING;
			break;
		case REPLAY_MODE_MIDDLE:
			g_pDSBuffer->SetCurrentPosition(m_lStartPoint);		// 開始位置を変更
			g_pDSBuffer->Play(0,0,0);							// 開始位置から再生する
			m_nPlayMode	= PLAY_MODE_PLAYING;
			break;
		case REPLAY_MODE_HANDLE:
			StopSound();
			m_nPlayMode	= PLAY_MODE_STOP;
			break;
		case REPLAY_MODE_OFF:								// 再生しない
			m_nPlayMode	= PLAY_MODE_STOP;
			break;
		}
	}
	if(CheckSoundOver() == PLAY_MODE_STOP && m_nSEReplayMode == REPLAY_MODE_OFF)
		return true;
	else
		return false;
}
void c_Sound::SetSoundReplayMode(int mode, LONG position)
{

}

HRESULT c_Sound::InitSound(int Replaymode, LONG position)
{
	
		HMMIO hMmio=NULL;					//WindowsマルチメディアAPIのハンドル
		DWORD dwWavSize = 0;				//WAVデータのサイズ
		WAVEFORMATEX* pwfex;				//WAVのフォーマット
		MMCKINFO ckInfo;					//　チャンク情報
		MMCKINFO riffckInfo;				// 最上部チャンク（RIFFチャンク）保存用
		PCMWAVEFORMAT pcmWaveForm;

		//DirectSoundオブジェクトを生成
	   DirectSoundCreate8(NULL,&g_pDSound,NULL);

	   // 協調レベルの設定
	   g_pDSound->SetCooperativeLevel(g_hWnd,DSSCL_EXCLUSIVE );


	   LPSTR name = (LPSTR)m_szFileName;
	   // WAVファイル内のヘッダー情報（音データ以外）の確認と読み込み
	   hMmio = mmioOpen( name, NULL, MMIO_ALLOCBUF | MMIO_READ );

	   // ファイルポインタをRIFFチャンクの先頭にセット
	   mmioDescend( hMmio, &riffckInfo, NULL, 0 );

	   // ファイルポインタを'f' 'm' 't' ' ' チャンクにセット
	   ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	   mmioDescend( hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK );

	   // フォーマットを読み込む
	   mmioRead( hMmio, (HPSTR) &pcmWaveForm,sizeof(pcmWaveForm));  
	   pwfex = (WAVEFORMATEX*)new CHAR[ sizeof(WAVEFORMATEX) ];   
	   memcpy( pwfex, &pcmWaveForm, sizeof(pcmWaveForm) );   
	   pwfex->cbSize = 0;	
	   mmioAscend( hMmio, &ckInfo, 0 );

	   // WAVファイル内の音データの読み込み	
	   ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');   
	   mmioDescend( hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK );//データチャンクにセット
		dwWavSize = ckInfo.cksize;

	   // DirectSoundセカンダリーバッファー作成
		DSBUFFERDESC dsbd;  
	   ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
	   dsbd.dwSize = sizeof(DSBUFFERDESC);
	   dsbd.dwFlags = NULL;
	   dsbd.dwBufferBytes = dwWavSize;
	   dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
	   dsbd.lpwfxFormat = pwfex;

	   ///////////////////////////////////////////////////////////////////////////////
	   HRESULT hr;
		hr = g_pDSound->CreateSoundBuffer( &dsbd, &g_pDSBuffer, NULL );  
	   delete pwfex;


	   // セカンダリーバッファーをロックする
	   VOID* pBuffer =NULL;
	   DWORD dwBufferSize = 0; 
	   
		g_pDSBuffer->Lock( 0, dwWavSize,&pBuffer, &dwBufferSize,NULL, NULL, 0); 
	   
	
	   // バッファーに音データを書き込む   
	   FILE* fp=fopen(m_szFileName,"rb");
	   fseek(fp,riffckInfo.dwDataOffset + sizeof(FOURCC),SEEK_SET);
	   BYTE* pWavData=new BYTE[ dwBufferSize ];
	   fread(pWavData,1,dwBufferSize,fp);				//一時的な場所(pWavData)に波形データを読み込み
	   for( DWORD i = 0; i < dwBufferSize; i++ )
	   {
		 *((BYTE*)pBuffer+i) = *((BYTE*) pWavData+i);	//一時的な場所の波形データをセカンダリバッファーにコピーする
	   }
	   fclose(fp);
	   delete pWavData;									// 一時的な波形データを開放する

		g_pDSBuffer->Unlock( pBuffer, dwBufferSize, NULL, 0 );

		m_nSEReplayMode = (REPLAY_MODE_SOUND)Replaymode;
		m_lStartPoint	= position;
   return S_OK;
}
void c_Sound::ChangeVolume(int nVolume)
{

	g_pDSBuffer->SetVolume(nVolume);
}
void c_Sound::PlaySoundOnce()
{
	g_pDSBuffer->Play(0,0,0);
	m_nSEReplayMode = REPLAY_MODE_OFF;
	m_nPlayMode = PLAY_MODE_PLAYING;
}
void c_Sound::PlaySoundCycle()
{
	g_pDSBuffer->Play(0,0,1);
	m_nSEReplayMode = REPLAY_MODE_START;
	m_nPlayMode = PLAY_MODE_PLAYING;
}
void c_Sound::StopSound()
{
	g_pDSBuffer->Stop();
	g_pDSBuffer->GetCurrentPosition((LPDWORD)&m_lRecPoint,NULL);
}
void c_Sound::PlaySoundContinue(void)
{
	g_pDSBuffer->SetCurrentPosition(m_lRecPoint);	// 開始位置を変更
	g_pDSBuffer->Play(0,0,0);						// 開始位置から再生する
	m_lRecPoint	= 0;								// 再生位置を初期化
	m_nPlayMode	= PLAY_MODE_PLAYING;
}


void c_Sound::SetReplayMode(int nSEMode)
{
		m_nSEReplayMode = (REPLAY_MODE_SOUND)nSEMode;
}

