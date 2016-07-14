//-----------------------------------------------------------
//カメラマスタークラスh
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
	void	ResetCameraStats(void);				// ステータスを初期化
	void	ResetCameraPointer(void);			// ポインターを初期化
	void	SystemSet_D3DTVIEW(void);			// D3DVIEWを設定(必ず実行)
	void	MoveToDestPosAuto(void);			// 自動Moveの実行
	HRESULT InitCamera(bool bWindow);			// カメラの初期設定
	void	SetDestPos(D3DXVECTOR3* DestPos);	// DestPosの設定
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
	D3DXMATRIX					m_matProj;				// プロジェクション マトリックス
	D3DXMATRIX					m_matView;				// ビュー マトリックス
	D3DXMATRIX					m_matMatrix;			// カメラマトリックス
	D3DXVECTOR3					m_vCameraIdentity;		// カメラ―本当の座標
	D3DXVECTOR3					m_vRecPos;				// 移動中の絶対座標
	D3DXVECTOR3					m_vDestPos;				// 移動中の目標座標
	D3DXVECTOR3					m_vRot;					// カメラの回転
	D3DXVECTOR3					m_vSpeed;				// 移動速度


	D3DXMATRIX*					m_pmTargetMatrix;		// ターゲットのマトリックスアドレス
	D3DXVECTOR3*				m_pvTargetPos;			// ターゲットのVPosアドレス
	D3DXVECTOR3					m_vTargerPos;			// ターゲットのvPos
	D3DXVECTOR3					m_vRangeFromTarget;		// 現ターゲットからのずれ

	D3DXVECTOR3*				m_pvRecPos;				// 現在のPosアドレス
	D3DXVECTOR3					m_vRangeFromRecPos;		// 現Posからのずれ

	float						m_fRevolutionRange;		// 公転半径
	bool						m_bShake;				// 振動モード

	int							m_nRecTime;				// 現在の時間
	int							m_nMaxTime;				// 最大時間
	

};

#endif