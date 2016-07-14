//-----------------------------------------------------------
//CLASS_SHIP_MAIN
//-----------------------------------------------------------
#ifndef CLASS_SHIP_MAIN
#define CLASS_SHIP_MAIN
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_C_Physic.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Block.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�l�[�W���[�C���N���[�h
//--------------------------------------
//�}�N����`
const D3DXVECTOR3	ShipPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
#define DEFAULT_SHIP_NAME		("data/Ship/ShipSample.csv")
//--------------------------------------
//�N���X�錾
class c_Ship
{
#define SHIP_FULL_SIZE	(MAX_SHIP_SIZE * 2 + 1)
public:
	c_Ship();
	~c_Ship();
	void InitShip(void);
	void UninitShip(void);
	void UpdateShip(void);
	void DrawShip(void);
	D3DXVECTOR3 GetCenterpos(void);

	void CreateBlock(FIELDPLACE3 place,int nType);
	void DeleteBlock(FIELDPLACE3 place);
	void ShipPlaceChange(FIELDPLACE3* place);

	HRESULT SaveRecentlyShip(void);
	HRESULT	LoadShipFromFile(LPCSTR FileName);
	void	SetShipName(LPCSTR FileName);
private:
	c_Block*		m_pBlock[SHIP_FULL_SIZE][SHIP_FULL_SIZE][SHIP_FULL_SIZE];
	c_FileNameMgr	m_cFileMgr;
	LPCSTR			m_lpzFileName;
	D3DXVECTOR3		m_vCenterPos;

};
//--------------------------------------
//�\���̐錾

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