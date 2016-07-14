//============================================================================
//sound.h
//============================================================================
#ifndef _C_MASTER_SE_SOUND_H_
#define _C_MASTER_SE_SOUND_H_
//-----------------------------------
//�V�X�e���C���N���[�h
#include"Sys_Global_Variable.h"
#include "Sys_Macro.h"


#include "Sys_Input.h"

//-----------------------------------
//�}�N����`

typedef enum
{
	REPLAY_MODE_START = 0,	// �ŏ�����Đ�	
	REPLAY_MODE_MIDDLE,		// �w��ʒu����Đ�
	REPLAY_MODE_HANDLE,		// �蓮�Đ�
	REPLAY_MODE_OFF,		// ���[�v�Đ����Ȃ�
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
//�N���X�錾

class c_Sound 
{
public:
	c_Sound();
	c_Sound(LPCSTR szFileName);
	~c_Sound();

	HRESULT InitSound(int mode, LONG position = 0);	// �ǂݍ��ݏ�����
	HRESULT	UnInitSound(void);						// �T�E���h�̊J��
	void	ResSoundStats(void);					// �T�E���h�X�e�[�^�X�̏�����
	bool	UpdateSound(void);						// �X�V����

	void	ChangeVolume(int nVolume);				// ���ʕύX
	void	PlaySoundOnce(void);					// �Đ�
	void	PlaySoundCycle(void);					// �J��Ԃ��Đ�
	void	StopSound(void);						// �ꎞ��~
	void	PlaySoundContinue(void);			
	void	SetReplayMode(int nSEMode);				// ���v���C���[�h�̕ύX
	int		CheckSoundOver(void);					// �T�E���h�̕�����ԃ`�F�b�N

	void	SetSoundReplayMode(int Replaymode, LONG position = 0);//���[�h�̐ݒ�
	
private:
	// �T�E���h�֌W�ϐ�
	LPDIRECTSOUND8				g_pDSound;			// SE��DirectSoud�I�u�W�F�N�g
	LPDIRECTSOUNDBUFFER			g_pDSBuffer;		// SE��DirectSound�Z�J���_���[�o�b�t�@�[
	
	LPCSTR						m_szFileName;		// ���̃T�E���h�̖��O
	REPLAY_MODE_SOUND			m_nSEReplayMode;	// ���v���C���[�h

	LONG						m_lStartPoint;		// SE�p���[�v�Đ��ʒu
	LONG						m_lRecPoint;		// ���݂̍Đ��ʒu

	int							m_nPlayMode;		// �Đ����邩

protected:

};
#endif