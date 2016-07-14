//-----------------------------------------------------------
//�J�����}�X�^�[�N���Xh
//-----------------------------------------------------------
#ifndef _CLASS_CAMERA_MASTER_H_
#define _CLASS_CAMERA_MASTER_H_

#include "Sys_Include.h"

class c_Camera
{
#define MAX_MOVE_FRMAE			(1 * 60)
#define REVOLUTION_ROTSPEED		(0.04f)
#define REVOLUTION_MIN_RANGE	(10.0f)
#define REVOLUTION_MAX_RANGE	(30.0f)
public :
	c_Camera();
	void	ResetCameraStats(void);				// �X�e�[�^�X��������
	void	ResetCameraPointer(void);			// �|�C���^�[��������
	void	SystemSet_D3DTVIEW(void);			// D3DVIEW��ݒ�(�K�����s)
	void	MoveToDestPosAuto(void);			// ����Move�̎��s
	HRESULT InitCamera(bool bWindow);			// �J�����̏����ݒ�
	void	SetDestPos(D3DXVECTOR3* DestPos);	// DestPos�̐ݒ�
	void	UpdateCameraNormal(void);
	void	UpdateCameraRevolution(void);
	void	DrawCamera(void);
	void	UninitCamera(void);

	void	SetCameraTarget(D3DXVECTOR3* vPos,D3DXVECTOR3* vRnage);
	void	SetCameraTarget(D3DXMATRIX*  mPos,D3DXVECTOR3* vRnage);

	void	SetCameraPos(D3DXVECTOR3* vPos,D3DXVECTOR3* vRnage);
	void	SetCameraPos(D3DXVECTOR3 vPos,D3DXVECTOR3 vRnage);

	D3DXMATRIX*	GetCameraMatView(void);
	D3DXMATRIX* GetCameraMatProj(void);
	D3DXMATRIX* GetCameraMatrix(void);
	D3DXVECTOR3	GetCameraPos(void);
private:
	D3DXMATRIX					m_matProj;				// �v���W�F�N�V���� �}�g���b�N�X
	D3DXMATRIX					m_matView;				// �r���[ �}�g���b�N�X
	D3DXMATRIX					m_matMatrix;			// �J�����}�g���b�N�X
	D3DXVECTOR3					m_vCameraIdentity;		// �J�����\�{���̍��W
	D3DXVECTOR3					m_vRecPos;				// �ړ����̐�΍��W
	D3DXVECTOR3					m_vDestPos;				// �ړ����̖ڕW���W
	D3DXVECTOR3					m_vRot;					// �J�����̉�]
	D3DXVECTOR3					m_vSpeed;				// �ړ����x


	D3DXMATRIX*					m_pmTargetMatrix;		// �^�[�Q�b�g�̃}�g���b�N�X�A�h���X
	D3DXVECTOR3*				m_pvTargetPos;			// �^�[�Q�b�g��VPos�A�h���X
	D3DXVECTOR3					m_vTargerPos;			// �^�[�Q�b�g��vPos
	D3DXVECTOR3					m_vRangeFromTarget;		// ���^�[�Q�b�g����̂���

	D3DXVECTOR3*				m_pvRecPos;				// ���݂�Pos�A�h���X
	D3DXVECTOR3					m_vRangeFromRecPos;		// ��Pos����̂���

	float						m_fRevolutionRange;		// ���]���a
	bool						m_bShake;				// �U�����[�h

	int							m_nRecTime;				// ���݂̎���
	int							m_nMaxTime;				// �ő厞��
	

};

#endif