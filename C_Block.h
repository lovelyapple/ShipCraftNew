
//-----------------------------------------------------------
//CLASS_BLOCK
//-----------------------------------------------------------
#ifndef CLASS_BLOCK
#define CLASS_BLOCK
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_UserDefinition.h"
#include "Sys_C_FileNameManger.h"
#include "Sys_C_Physic.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_3D_Test_model.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�l�[�W���[�C���N���[�h
//--------------------------------------
//�}�N����`
//--------------------------------------
//�\���̐錾
typedef struct
{
	int			nType;
	int			nHP;
	int			nWeight;
	int			nBoyance;
}BLOCK_STATS;
typedef enum
{
	BLOCK_TYPE_NORMAL = 0,
	BLOCK_TYPE_METAL,
	BLOCK_TYPE_ENGINE,
	BLOCK_TYPE_WOOD,
	BLOCK_TYPE_ACTIVE,
	BLOCK_TYPE_MAX,
}BLOCK_TYPE;
//--------------------------------------
//�N���X�錾
class c_Block : public c_Model
{
public:
	c_Block();
	~c_Block();
	void UpdateBlockFieldPosInShip(D3DXVECTOR3 CenterPos,FIELDPLACE3 LimitHalf);
	void UpdateBlockMatrix(void);

	BLOCK_STATS		m_uStats;
	FIELDPLACE3		m_uPlace;
	c_FileNameMgr	m_cFileName;
	c_Physic		m_cPhysic;
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