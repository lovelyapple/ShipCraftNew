//-----------------------------------------------------------
//CLASS_UI_EDITOR_BLOCKMENU
//-----------------------------------------------------------
#ifndef CLASS_UI_SELECTION_H
#define CLASS_UI_SELECTION_H

//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "Sys_C_Primitive3D.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�l�[�W���[�C���N���[�h
//--------------------------------------
//�}�N����`
const D3DXVECTOR3 SelectionSize = D3DXVECTOR3(0.3f,0.3f,0.0f);
const D3DXVECTOR3 SelectionBGPos = D3DXVECTOR3(0.0f,0.0f,-0.001f);
//--------------------------------------
//�\���̐錾
//--------------------------------------
//�N���X�錾
class c_Selection
{
public:
	c_Selection();
	~c_Selection();
	void Init_Selection(LPCSTR FileName);
	void Uninit_Selection(void);
	void Update_Selection(void);
	void Draw_Selection(void);
	void Set_SelectionPos(D3DXVECTOR3 SePos,D3DXVECTOR3 BgPos);

	c_Primitive3D*			m_pSelectionEntity;
	c_Primitive3D*			m_pSelectionBG;
	D3DXVECTOR3				m_vPosFromCamera;

	float					m_fAlpha;
	bool					m_bActived;
	int						m_nRecTime;
	int						m_nMaxTime;
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