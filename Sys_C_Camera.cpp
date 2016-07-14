//-----------------------------------------------------------
//カメラマスタークラスcpp
//-----------------------------------------------------------
#include "Sys_C_Camera.h"
c_Camera::c_Camera()
{
	ResetCameraStats();
	InitCamera(true);
}
void c_Camera::ResetCameraPointer(void)
{
	m_pmTargetMatrix = NULL;
	m_pvTargetPos = NULL;
	m_pvRecPos = NULL;
}

void c_Camera::ResetCameraStats(void)
{
	D3DM_INIT(m_matProj);
	D3DM_INIT(m_matView);
	D3DM_INIT(m_matMatrix);

	D3DV_INIT(m_vRecPos);
	D3DV_INIT(m_vRot);
	D3DV_INIT(m_vDestPos);
	D3DV_INIT(m_vSpeed);
	D3DV_INIT(m_vRangeFromRecPos);
	D3DV_INIT(m_vRangeFromTarget);
	D3DV_INIT(m_vTargerPos);

	ResetCameraPointer();

	m_bShake = false;
	m_nRecTime = 0;
	m_nMaxTime = 0;
}
void c_Camera::SetDestPos(D3DXVECTOR3* DestPos)
{
	m_nRecTime	= MAX_MOVE_FRMAE;
	m_vDestPos = *DestPos;
	m_vDestPos.z = -10.0f;
	m_vSpeed = (m_vDestPos - m_vRecPos) / MAX_MOVE_FRMAE;// / m_nMoveframe;
}
void c_Camera::SystemSet_D3DTVIEW(void)
{
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);

	g_matView				= &m_matView;					
	g_pMatrixProjection		= &m_matProj;
}
void c_Camera::MoveToDestPosAuto(void)
{
	if(m_vRecPos != m_vDestPos)
	{
		m_vRecPos += m_vSpeed;
		m_nRecTime--;
		if(m_nRecTime <= 0)
		{
			m_nRecTime	= MAX_MOVE_FRMAE;
			m_vRecPos		= m_vDestPos;
			D3DV_INIT(m_vSpeed);		
		}
	}
}

HRESULT c_Camera::InitCamera(bool bWindow)
{
	float fAspect_ratio = ASPECT_RATIO_WIN;
	if(bWindow == false)
		fAspect_ratio = ASPECT_RATIO_FULL;
	//プロジェクション・マトリックス設定
	D3DXMatrixPerspectiveFovLH(&m_matProj,
		D3DXToRadian(FOVY),
		fAspect_ratio,
		NEAR_CLIP, FAR_CLIP);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_matProj);

	//ビュー　マトリックス設定　//設定しなくてもよい
	m_vRecPos = D3DXVECTOR3(SCREEN_WIDTH_WIN * 0.5f,		// 視点座標(X)
							 0.0f,							// 視点座標(Y)
	-SCREEN_HEIGHT_WIN * 0.5f / tanf(D3DXToRadian(FOVY) * 0.5f));	// 視点座標(Z)

	D3DXMatrixLookAtLH(&m_matView,
		&m_vCameraIdentity,	// 視点座標(Z)
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// 注視点座標
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// アップベクトル
	return S_OK;
}
void c_Camera::UpdateCameraNormal(void)
{
	//位置情報マトリックス生成
	D3DXMATRIX matrix;
	D3DM_INIT(matrix);
	D3DXMatrixTranslation(&matrix,m_vRecPos.x,m_vRecPos.y,m_vRecPos.z);
	
	//現在マトリックスからのズレを計算
	D3DXVec3TransformCoord(&m_vCameraIdentity,&m_vRangeFromRecPos,&matrix);
	
	//目標までのVec3生成
	D3DXVECTOR3 vLook;
	if(m_pmTargetMatrix)
	D3DXVec3TransformCoord(&vLook,&m_vRangeFromTarget,m_pmTargetMatrix);
	else
	D3DXVec3TransformCoord(&vLook,&m_vRangeFromTarget,&matrix);
	//vUp生成
	D3DXVECTOR3 vUP;
	D3DXVec3TransformCoord(&vUP,&D3DXVECTOR3(0.0f,1.0f,0.0f),&matrix);

	//D3DXMATRIX matRot;
	//m_vRot = m_vCameraIdentity - vLook;
	//D3DXMatrixIdentity(&matRot);
	//D3DXMatrixRotationYawPitchRoll(&matRot,m_vRot.y,m_vRot.x,m_vRot.z);
	//m_matMatrix = matRot * matrix;
	//最終合算
	D3DXMatrixLookAtLH(&m_matView,&m_vCameraIdentity,&vLook,&vUP);
	//D3DXVec3TransformCoord(&m_vRecPos,
	//	&D3DXVECTOR3(0.0f,150.0f,-300.0f),
	//	&GetModelMatrix());

	//D3DXVECTOR3 vLook;
	//D3DXVec3TransformCoord(&vLook,
	//	&D3DXVECTOR3(0.0f,100.0f,0.0f),
	//	&GetModelMatrix());

	//D3DXVECTOR3 vUP;
	//D3DXVec3TransformNormal(&vUP,
	//	&D3DXVECTOR3(0.0f,1.0f,0.0f),
	//	&GetModelMatrix());

	//D3DXMatrixLookAtLH(&m_matView,
	//	&m_vRecPos,&vLook,&vUP);
	//D3DM_INIT(m_matView);
	//D3DXMatrixTranslation(&m_matView,m_vRecPos.x,m_vRecPos.y,m_vRecPos.z);
}
void c_Camera::UpdateCameraRevolution(void)
{
	D3DXMATRIX	matrixRotation;
	D3DXMATRIX Rotmatrix_X;//テスト用
	D3DXMATRIX Rotmatrix_Y;
	D3DM_INIT(matrixRotation);
	D3DM_INIT(Rotmatrix_X);
	D3DM_INIT(Rotmatrix_Y);

	if(GetMouseLeftPress())
	{
		if(GetMouseAxisX()>0)
		{
			m_vRot.y += REVOLUTION_ROTSPEED;
	
		}else if(GetMouseAxisX()<0)
		{
			m_vRot.y -= REVOLUTION_ROTSPEED;
		}

		if(GetMouseAxisY()>0)
		{
			m_vRot.x += REVOLUTION_ROTSPEED;
		}else if(GetMouseAxisY()<0)
		{
			m_vRot.x -= REVOLUTION_ROTSPEED;
		}
	}
	//ホイルのデータを取得して、
	int MouseHoilu = 0;
	MouseHoilu = g_nMouseHoilu;//

	if(MouseHoilu > 0)
		m_fRevolutionRange += 0.1f;
	else if(MouseHoilu < 0)
		m_fRevolutionRange -= 0.1f;

	if(m_fRevolutionRange <= REVOLUTION_MIN_RANGE) m_fRevolutionRange = REVOLUTION_MIN_RANGE;
	if(m_fRevolutionRange >= REVOLUTION_MAX_RANGE) m_fRevolutionRange = REVOLUTION_MAX_RANGE;

	if(m_vRot.x < 0 )		m_vRot.x = 0;
	if(m_vRot.x > 3.14f/2)	m_vRot.x = 3.14f/2;

	D3DXMatrixRotationX(&Rotmatrix_X,m_vRot.x);
	D3DXMatrixRotationY(&Rotmatrix_Y,m_vRot.y);

	matrixRotation = Rotmatrix_X * Rotmatrix_Y  ;

	D3DXVec3TransformCoord(&m_vCameraIdentity,
		&D3DXVECTOR3(0.0f,0,-m_fRevolutionRange),
		&matrixRotation);

		D3DXVECTOR3 vLook;
		if(m_pmTargetMatrix)
		D3DXVec3TransformCoord(&vLook,&m_vRangeFromTarget,m_pmTargetMatrix);
		else
		vLook = m_vTargerPos;
	D3DXVECTOR3 vUP;

	D3DXVec3TransformNormal(&vUP,
		&D3DXVECTOR3(0.0f,1.0f,0.0f),
		&matrixRotation);



	D3DXMATRIX matPos;
	D3DXMatrixIdentity(&matPos);
	D3DXMatrixTranslation(&matPos,m_vCameraIdentity.x,m_vCameraIdentity.y,m_vCameraIdentity.z);

	m_matMatrix = matrixRotation * matPos;


	D3DXMatrixLookAtLH(&m_matView,
		&m_vCameraIdentity,&vLook,&vUP);
}
void c_Camera::SetCameraTarget(D3DXMATRIX*  mPos,D3DXVECTOR3* vRnage)
{
	m_pmTargetMatrix	= mPos;
	m_vRangeFromTarget	= *vRnage;
}
void c_Camera::SetCameraTarget(D3DXVECTOR3* vPos,D3DXVECTOR3* vRnage)
{
	m_pvTargetPos		= vPos;
	m_vRangeFromTarget	= *vRnage;
}
void c_Camera::SetCameraPos(D3DXVECTOR3* vPos,D3DXVECTOR3* vRnage)
{
	m_pvRecPos			= vPos;
	m_vRangeFromRecPos	= *vRnage;
}
void c_Camera::SetCameraPos(D3DXVECTOR3 vPos,D3DXVECTOR3 vRnage)
{
	m_vRecPos			= vPos;
	m_vRangeFromRecPos	= vRnage;
}
D3DXMATRIX*	c_Camera::GetCameraMatView(void)
{
	return &this->m_matView;
}

D3DXMATRIX* c_Camera::GetCameraMatProj(void)
{
	return &this->m_matProj;
}
D3DXMATRIX* c_Camera::GetCameraMatrix(void)
{
	return &this->m_matMatrix;
}
D3DXVECTOR3 c_Camera::GetCameraPos(void)
{
	return this->m_vCameraIdentity;
}

//---------------------------------------------------------------------------------------
// カメラ設定 (全ての描画より先に呼び出す必要がある)
//---------------------------------------------------------------------------------------
void c_Camera::DrawCamera()
{
	// プロジェクション マトリックス設定
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

	// ビュー マトリックス設定
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);
	//SetCameraShader(&m_vRecPos, &m_matView, &m_matProj);
}
void c_Camera::UninitCamera(void)
{
	//do Noth
}

