//-----------------------------------------------------------
//CLASS_UI_INPUTUWINDOW_SHIP_H
//-----------------------------------------------------------
#ifndef CLASS_UI_MESSAGE_BOX_H
#define CLASS_UI_MESSAGE_BOX_H
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_C_Font.h"
#include "Sys_C_Messenger.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "Sys_C_Primitive2D.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�l�[�W���[�C���N���[�h
//--------------------------------------
//�}�N����`
const D3DXVECTOR3 MessageBoxPos		= D3DXVECTOR3(SCREEN_WIDTH_WIN/2,SCREEN_HEIGHT_WIN/2,0.0f);
const D3DXVECTOR3 MessageBoxSize	= D3DXVECTOR3(100.0f,30.0f,0.0f);
const D3DXVECTOR3 MessageFontPos	= D3DXVECTOR3(-MessageBoxSize.x,-MessageBoxSize.y * 0.5f,0.0f);
#define FILENAME_MESSAGEBOX_DEAULT_TEX	("data/Texture/MessageBoxDefault.png")
#define MAX_TEXT	(128)
//--------------------------------------
//�N���X�錾
class c_UI_MessageBox
{
public:
	c_UI_MessageBox();
	~c_UI_MessageBox();
	void Init_MessageBox(void);
	void Update_MessageBox(void);
	void Uninit_MessageBox(void);
	void Draw_MessageBox(void);
	void Openinput(void);
private:
	c_Primitive2D*				m_pPlate;
	c_Font*						m_pFont;
	LPCSTR						m_lpzText;
	c_Messenger					m_cMessenger;
	bool						m_bInput;

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