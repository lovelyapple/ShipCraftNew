//-----------------------------------------------------------
//C_PARTICLE_QUARK_H
//-----------------------------------------------------------
#ifndef C_PARTICLE_QUARK_H
#define C_PARTICLE_QUARK_H
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�N����`
typedef enum
{
	QUARK_STATS_POS = 0,
	QUARK_STATS_DEST_POS,
	QUARK_STATS_SPEED,
	QUARK_STATS_SPEED_MIN,
	QUARK_STATS_SPEED_MAX,
	QUARK_STATS_SIZE,
	QUARK_STATS_ROT,

	QUARK_STATS_MATRIX,

	QUARK_STATS_ALPHA,

	QUARK_STATS_LIFE,
	QUARK_STATS_TIME,
	QUARK_STATS_MAX_TIME,
	QUARK_STATS_MODE,
	QUARK_STATS_TYPE,

	QUARK_STATS_BANIMATION,
	QUARK_STATS_MAXFRAME,
	QUARK_STATS_USIZE,
	QUARK_STATS_TIMEPERFRAME,
}QUARK_STATS;
//--------------------------------------
//�\���̐錾
//--------------------------------------
//�N���X�錾
class c_Quark
{
public:
	c_Quark();
	~c_Quark();
	void Update_Matrix_Quark(void);
	void ResetStatus_Quark(void);
	void SetQuarkStats(int stats, D3DXVECTOR3 vInput);
	void SetQuarkStats(int stats, float fInput);
	void SetQuarkStats(int stats, int	nInput);
	void SetQuarkStats(int stats, bool  bInput);
	int		RunAndGetQuarkLife(void);
	bool	GetAnimationFlag(void);
	void	RunQuarkAnimation(void);

	D3DXVECTOR3 GetQuarkSize(void);
	D3DXVECTOR3 GetQuarkPos(void);
	float		GetQuarkUsize(void);
	float		GetQuarkAlpha(void);
	int			GetQuarkRecFrame(void);


private:
	D3DXVECTOR3				m_vPos;
	D3DXVECTOR3				m_vDestPos;
	D3DXVECTOR3				m_vSize;
	D3DXVECTOR3				m_vSpeed;
	D3DXVECTOR3				m_vSpeedMin;
	D3DXVECTOR3				m_vSpeedMax;
	D3DXVECTOR3				m_vRot;
	D3DXMATRIX				m_mMatrix;

	bool					m_bWatchCamera;
	float					m_fAlpha;
	int						m_nLife;
	int						m_nTime;
	int						m_nMaxTime;
	int						m_nMode;
	int						m_nType;

	bool					m_bAnimation;
	int						m_nRecTime;
	int						m_nRecFrame;
	int						m_nMaxFrame;
	int						m_fVerTexUSize;
	int						m_nTimePerFrame;
};
//--------------------------------------
//�I�u�W�F�N�g�O���[�o���ϐ��錾
//--------------------------------------
//�W���O���[�o���ϐ��錾
//--------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------
//����������
//--------------------------------------
//�I������
//--------------------------------------
//�X�V����
//--------------------------------------
//�`�揈��
#endif