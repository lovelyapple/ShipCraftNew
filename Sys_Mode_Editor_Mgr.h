//-----------------------------------------------------------
//CLASS_TEST_MANAGER_H
//-----------------------------------------------------------
#pragma once
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "Sys_C_Font.h"
#include "Sys_C_Primitive3D.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
#include "C_Ship_Main.h"
#include "C_ActiveBlock.h"
//--------------------------------------
//�}�l�[�W���[�C���N���[�h
#include "C_Light_Mgr.h"
#include "C_Camera_Mgr.h"
#include "C_EditorStModel_Mgr.h"
//--------------------------------------
//UseInterface�̃C���N���[�h
#include "C_UI_BlockMenu.h"

//--------------------------------------
//�}�N����`
//--------------------------------------
//�\���̐錾
//--------------------------------------
//�N���X�錾
class c_Mgr_EditorMode
{
public:
	c_Mgr_EditorMode(c_Camera_Mgr* pCamera_Mgr,
					 c_Light_Mgr*  pLight_Mgr);			// �R���X�g���N�^�\
	void Init_Mgr_EditorMode(void);						// ����������
	void Update_Mgr_EditorMode(void);					// �X�V����
	void Uninit_Mgr_EditorMode(void);					// �J������
	void Draw_Mgr_EditorMode(void);						// �`�揈��
	
	c_Ship*							m_pShip;			// ��̓|�C���^
	c_Active_Block*					m_pAcitveBLock;		// �I���u���b�N
	c_Font*							m_pFont;			// �����\���|�C���^�[

	c_Camera_Mgr*					m_pCamera_Mgr;		// �J�����̃}�l�[�W��
	c_Light_Mgr*					m_pLight_Mgr;		// ���C�g�̃}�l�[�W��
	c_EditorStModel_Mgr*			m_pStModel_Mgr;		// �Î~���f���}�l�[�W��

	c_BlockMenu*					m_BlockMenu;		// �u���b�N�̃��j���[




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
//-----------------------------------------------------------
//End of File