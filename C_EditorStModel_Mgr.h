//-----------------------------------------------------------
//C_MGR_STATIONARY_H
//-----------------------------------------------------------
#ifndef C_EDITOR_STATIONARY_MODEL_MGE_H
#define C_EDITOR_STATIONARY_MODEL_MGE_H
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_C_FileNameManger.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "Sys_C_Model.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�l�[�W���[�C���N���[�h
//--------------------------------------
//�}�N����`
typedef enum
{
	EDITOR_MODEL_CRAFT_TABLE = 0,

	EDITOR_MODEL_MAX,
}EDITOR_MODEL;
//--------------------------------------
//�\���̐錾
//--------------------------------------
//�N���X�錾
class c_EditorStModel_Mgr
{
public:
	c_EditorStModel_Mgr();
	~c_EditorStModel_Mgr();
	void Init_EditorStModel_Mgr(void);
	void Uninit_EditorStModel_Mgr(void);
	void Update_EditorStModel_Mgr(void);
	void Draw_EditorStModel_Mgr(void);
private:
	c_Model*			m_pStationaryModel[EDITOR_MODEL_MAX];
	c_FileNameMgr		m_cFileNameMgr;

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