//===============================================	=============================
//Ship.h
//============================================================================
#ifndef _CLASS_MASTER_PRIMITIVE_H_
#define _CLASS_MASTER_PRIMITIVE_H_
//-----------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"
//-----------------------------------
//�}�X�^�[�Y�C���N���[�h
//-----------------------------------
//�C���X�^���X�C���N���[�h
//-----------------------------------
//�}�N����`
#define FILE_NAME_DEAULT_PRIMITIVE		("data/Texture/denkyu.png")
//-----------------------------------
//�\���̐錾
#ifndef DVERTEX_PRIMITIVE_3D
#define DVERTEX_PRIMITIVE_3D
typedef struct  
{	
	float		x, y, z;		// ���_
	float		nx, ny, nz;		// �@���x�N�g��
	D3DCOLOR	color;			// �f�B�t���[�Y�J���[
	float		tu, tv;			// �e�N�X�`�����W
}DVERTEX_PRIMITIVE;
#endif
//-----------------------------------
//�N���X�錾
class c_Primitive3D
{
#define MAX_V_FRAME	(5)
public:
	c_Primitive3D();
	c_Primitive3D(LPCSTR fzName);				// �R���X�g���N�^
	~c_Primitive3D();							// �f�X�g���N�^
	virtual void	SetFileName(LPCSTR fzName);		// �t�@�C�����̐ݒ�
	void			Reset_Primitive(void);			// �����ϐ��̏�����
	virtual HRESULT Init_Primitive(void);			// ������
			HRESULT	CreatePrimitiveBuffOnly(void);	// �o�b�t�@�̍쐬�̂�
			void	Uninit_Primitive(void);			// �I������

			void	SetPos(D3DXVECTOR3 Pos);						// Pos�̕ύX
			void	SetSize(D3DXVECTOR3 size);						// Size�̕ύX
			void	SetRot(D3DXVECTOR3 Ros);						// Rot�̕ύX
			void	SetAlpha(float fAlpha);							// Alpha�̕ύX
			void	SetOblique(D3DXVECTOR3* input);					// �΂ߓx���̐ݒ�
			void	SetReversal(bool bReversa);						// �������]���邩
			void	SetTextureUV(int V,int U,int Frame);			// UV�̐ݒ�


			void	SetVerTexBuff(void);							// ALL�o�b�t�@�ύX
			void	SetVerTexBuffSize(void);						// SizeBuff�̂ݍX�V
			void	SetVerTexBuffSizeOblique(void);					// �X�΍�SizeBuff�̍X�V
			void	SetVerTexBuffUV(void);							// UVBuff�̂ݍX�V
			void	SetVerTexBuffUVReversa(void);					// UVBuff�̂ݍX�V
			void	SetVerTexBuffAlpha(void);						// AlphaBuff�̂ݍX�V
		
			void	Update_PrimitiveNormal(void);					// �X�V
			void	Update_PrimitiveMatrixOnly(void);				// �}�g���b�N�X�̂ݍX�V

			void	SetTexRecUVFrame(int nFrameX,
									 int nFrameY);					//UV�t���[���̐ݒ�
			void	SetWatchCamera(bool input);						//�J���������ݒ�

	virtual void	DrawPrimitive();								// �`��
			void	DrawPrimitiveAntialiasing(void);				//�A���`�G���A�V���O�`��
			void	DrawPrimitiveOtherTexture(LPDIRECT3DTEXTURE9 pD3DTexture);

	D3DXMATRIX		GetMatrix(void);
	D3DXVECTOR3		GetPos(void);
	D3DXVECTOR3		GetSize(void);
	
protected:
	LPDIRECT3DVERTEXBUFFER9			m_pD3DVertexBuffer;
	LPDIRECT3DTEXTURE9				m_pD3DTexture;
	LPCSTR							m_pszFName;

	D3DXMATRIX						m_mMatrix;						// �}�g���b�N�X
	D3DXVECTOR3						m_vPos;							// 3D��΍��W
	D3DXVECTOR3						m_vRot;							// ���]�p�x
	D3DXVECTOR3						m_vSize;						// �T�C�Y
	D3DXVECTOR3						m_vOblique[2];					// �X�΂̓x��	
	float							m_fAlpha;						// Alpha
	bool							m_bWatchCamera;					// �v����v��
	bool							m_bUReversal;					// UV�̐������]
	int								m_nMAXUVFrame[2];				// �ő�UVFrame
	int								m_nMaxFrameU[MAX_V_FRAME];		// V���Ƃ̍ő�U�T�C�Y
	int								m_nFrameUPerTimt[MAX_V_FRAME];	// V���Ƃ�U�X�V����^�C���t���[����
	int								m_nMaxFrameV;					// V�̍ő吔,�ő�MAX_V_FRAME�@	
	int								m_nRecFrameU;					// ����UV_X�̃t���[����
	int								m_nRecFrameV;					// ����UV_Y�̃t���[����

	
};


#endif