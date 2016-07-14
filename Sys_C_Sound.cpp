//============================================================================
//C_Master_SE_Sound.h
//============================================================================
//-----------------------------------
//�V�X�e���C���N���[�h
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
	// DirectSound�̉��
	SAFE_RELEASE(g_pDSBuffer);
	SAFE_RELEASE(g_pDSound);
	return S_OK;
}
int c_Sound::CheckSoundOver(void)
{
	DWORD dwStatus;
	g_pDSBuffer->GetStatus(&dwStatus);			//���݂̏�Ԃ��擾

	if(m_nPlayMode != PLAY_MODE_STOP)			// ���ł�STOP��Ԃ̃T�E���h�ɑ΂��ă`�F�b�N���Ȃ�
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
	if(CheckSoundOver() == PLAY_MODE_STOP)	//���t���I�������
	{
		switch(m_nSEReplayMode)
		{
		case REPLAY_MODE_START:
			//g_pDSBuffer->SetCurrentPosition(m_lStartPoint);	// �J�n�ʒu��ύX
			//g_pDSBuffer->Play(0,0,0);							// 
			m_nPlayMode	= PLAY_MODE_PLAYING;
			break;
		case REPLAY_MODE_MIDDLE:
			g_pDSBuffer->SetCurrentPosition(m_lStartPoint);		// �J�n�ʒu��ύX
			g_pDSBuffer->Play(0,0,0);							// �J�n�ʒu����Đ�����
			m_nPlayMode	= PLAY_MODE_PLAYING;
			break;
		case REPLAY_MODE_HANDLE:
			StopSound();
			m_nPlayMode	= PLAY_MODE_STOP;
			break;
		case REPLAY_MODE_OFF:								// �Đ����Ȃ�
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
	
		HMMIO hMmio=NULL;					//Windows�}���`���f�B�AAPI�̃n���h��
		DWORD dwWavSize = 0;				//WAV�f�[�^�̃T�C�Y
		WAVEFORMATEX* pwfex;				//WAV�̃t�H�[�}�b�g
		MMCKINFO ckInfo;					//�@�`�����N���
		MMCKINFO riffckInfo;				// �ŏ㕔�`�����N�iRIFF�`�����N�j�ۑ��p
		PCMWAVEFORMAT pcmWaveForm;

		//DirectSound�I�u�W�F�N�g�𐶐�
	   DirectSoundCreate8(NULL,&g_pDSound,NULL);

	   // �������x���̐ݒ�
	   g_pDSound->SetCooperativeLevel(g_hWnd,DSSCL_EXCLUSIVE );


	   LPSTR name = (LPSTR)m_szFileName;
	   // WAV�t�@�C�����̃w�b�_�[���i���f�[�^�ȊO�j�̊m�F�Ɠǂݍ���
	   hMmio = mmioOpen( name, NULL, MMIO_ALLOCBUF | MMIO_READ );

	   // �t�@�C���|�C���^��RIFF�`�����N�̐擪�ɃZ�b�g
	   mmioDescend( hMmio, &riffckInfo, NULL, 0 );

	   // �t�@�C���|�C���^��'f' 'm' 't' ' ' �`�����N�ɃZ�b�g
	   ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	   mmioDescend( hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK );

	   // �t�H�[�}�b�g��ǂݍ���
	   mmioRead( hMmio, (HPSTR) &pcmWaveForm,sizeof(pcmWaveForm));  
	   pwfex = (WAVEFORMATEX*)new CHAR[ sizeof(WAVEFORMATEX) ];   
	   memcpy( pwfex, &pcmWaveForm, sizeof(pcmWaveForm) );   
	   pwfex->cbSize = 0;	
	   mmioAscend( hMmio, &ckInfo, 0 );

	   // WAV�t�@�C�����̉��f�[�^�̓ǂݍ���	
	   ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');   
	   mmioDescend( hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK );//�f�[�^�`�����N�ɃZ�b�g
		dwWavSize = ckInfo.cksize;

	   // DirectSound�Z�J���_���[�o�b�t�@�[�쐬
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


	   // �Z�J���_���[�o�b�t�@�[�����b�N����
	   VOID* pBuffer =NULL;
	   DWORD dwBufferSize = 0; 
	   
		g_pDSBuffer->Lock( 0, dwWavSize,&pBuffer, &dwBufferSize,NULL, NULL, 0); 
	   
	
	   // �o�b�t�@�[�ɉ��f�[�^����������   
	   FILE* fp=fopen(m_szFileName,"rb");
	   fseek(fp,riffckInfo.dwDataOffset + sizeof(FOURCC),SEEK_SET);
	   BYTE* pWavData=new BYTE[ dwBufferSize ];
	   fread(pWavData,1,dwBufferSize,fp);				//�ꎞ�I�ȏꏊ(pWavData)�ɔg�`�f�[�^��ǂݍ���
	   for( DWORD i = 0; i < dwBufferSize; i++ )
	   {
		 *((BYTE*)pBuffer+i) = *((BYTE*) pWavData+i);	//�ꎞ�I�ȏꏊ�̔g�`�f�[�^���Z�J���_���o�b�t�@�[�ɃR�s�[����
	   }
	   fclose(fp);
	   delete pWavData;									// �ꎞ�I�Ȕg�`�f�[�^���J������

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
	g_pDSBuffer->SetCurrentPosition(m_lRecPoint);	// �J�n�ʒu��ύX
	g_pDSBuffer->Play(0,0,0);						// �J�n�ʒu����Đ�����
	m_lRecPoint	= 0;								// �Đ��ʒu��������
	m_nPlayMode	= PLAY_MODE_PLAYING;
}


void c_Sound::SetReplayMode(int nSEMode)
{
		m_nSEReplayMode = (REPLAY_MODE_SOUND)nSEMode;
}

