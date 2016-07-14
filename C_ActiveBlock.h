//-----------------------------------------------------------
//CLASS_ACTIVE_BLOCK
//-----------------------------------------------------------
#ifndef CLASS_ACTIVE_BLOCK
#define CLASS_ACTIVE_BLOCK
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Block.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�l�[�W���[�C���N���[�h
//--------------------------------------
//�}�N����`
//--------------------------------------
//�\���̐錾
typedef enum
{
	ACTIVE_BLOCK_STATS_SELECTING = 0,	
	ACTIVE_BLOCK_STATS_CREATE,
	ACTIVE_BLOCK_STATS_DELETE,
	ACTIVE_BLOCK_STATS_MAX,
}ACTIVE_STATS;
//--------------------------------------
//�N���X�錾
class c_Active_Block : public c_Block
{

public:
			c_Active_Block();
			~c_Active_Block();
	void	InitActiveBlock(void);
	void	UpdateActiveBlock(D3DXVECTOR3 CenterPos);
	void	UninitActiveBlock(void);
	int		GetActiveBlockStats(void);
	D3DXVECTOR3			m_vCenterPos;
private:
	int					m_nActiveStats;
	
	
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
//-----------------------------------------------------------
//End of File
//-----------------------------------------------------------