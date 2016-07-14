//-----------------------------------------------------------
//CLASS_UI_EDITOR_BLOCKMENU
//-----------------------------------------------------------
#ifndef CLASS_UI_EDITOR_BLOCKMENU
#define CLASS_UI_EDITOR_BLOCKMENU

//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "C_Camera_Mgr.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_UI_Selection.h"
#include "C_Block.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�l�[�W���[�C���N���[�h
//--------------------------------------
//�}�N����`
const D3DXVECTOR3 BlockMenuPos = D3DXVECTOR3(-2.0f,-1.5f,4.0f);
#define MAX_BLOCK_SELECTION		(BLOCK_TYPE_MAX - 1)
//--------------------------------------
//�\���̐錾
//--------------------------------------
//�N���X�錾
class c_BlockMenu
{
public:
	c_BlockMenu();
	~c_BlockMenu();
	void Init_BlockMenu(c_Camera_Mgr* pCameraMgr);
	void Uninit_BlockMenu(void);
	void Update_BlockMenu(void);
	void Draw_BlockMenu(void);
	c_Camera_Mgr*		m_pGameCamera;
	int	 GetRecentSelection(void);
private:
	c_Selection*		m_pSelection[MAX_BLOCK_SELECTION];
	c_FileNameMgr		m_FileMgr;
	int					m_nRecSelection;
	
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