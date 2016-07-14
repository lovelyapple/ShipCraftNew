//-----------------------------------------------------------
//CLASS_LIGHT_MANAGER_H
//-----------------------------------------------------------
#ifndef CLASS_LIGHT_MANAGER_H
#define CLASS_LIGHT_MANAGER_H
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "Sys_C_Light.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�l�[�W���[�C���N���[�h
//--------------------------------------
//�}�N����`
//--------------------------------------
//�\���̐錾
//--------------------------------------
//�N���X�錾
class c_Light_Mgr
{
#define MAX_LIGHT_IN_LIST				(32)
#define MAX_LIGHT_IN_SYS				(MAX_LIGHT_IN_LIST * 2 + 1)
public:
	c_Light_Mgr();														// �R���X�g���N�^�@
	void	Init_LightMgr(void);										// ������
	void	Uninit_LightMgr(void);										// �J��
	void	Update_LightMgr(void);										// �X�V
	void	Draw_LightMgr(void);										// �`��
	HRESULT	Create_SpotLight(int* Number,D3DXVECTOR3 Target,D3DXVECTOR3 vPos);		// �X�|�b�g���C�g�쐬
	HRESULT	Create_PointLight(int* Number);											// �X�|�b�g���C�g�쐬
	HRESULT	CheckLightIntList(int* Num);								// ���C�g�i���o�[�̎擾
	void	DeleteLight(int type,int Number);							// ���C�g�̍폜
	int						m_pSunLight;								// �V������̃|�C���^
	int*					m_pSpotList[MAX_LIGHT_IN_LIST];				// �X�|�b�g���C�g�̃|�C���^�z��
	int*					m_pPointList[MAX_LIGHT_IN_LIST];			// �|�C���g���C�g�̃|�C���^�z��

	c_Light*				m_pSysLight[MAX_LIGHT_IN_SYS];				// �V�X�e����̃��C�g�i���o�[
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
