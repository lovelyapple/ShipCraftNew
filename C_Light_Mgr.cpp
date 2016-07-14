//-----------------------------------------------------------
//CLASS_LIGHT_MANAGER_H
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "C_Light_Mgr.h"
c_Light_Mgr::c_Light_Mgr()
{
	m_pSunLight = 0;
	for(int nL = 0; nL < MAX_LIGHT_IN_LIST;nL ++)
	{
		m_pSpotList[nL] = NULL;
		m_pPointList[nL] = NULL;
	}
	for(int nLs = 0; nLs < MAX_LIGHT_IN_SYS;nLs ++)
		m_pSysLight[nLs] = NULL;
}
void c_Light_Mgr::Init_LightMgr(void)
{
	//==================================================
	//必ず実行
	m_pSysLight[0] = new c_Light;
	m_pSysLight[0]->CreatLightSunDefault(0);
	m_pSysLight[0]->ActiveLightSYS();
	//==================================================
	
	int* Num = new int;
	Create_PointLight(Num);
	Create_SpotLight(Num,D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,-3.0f));
	int NumberSys = *m_pPointList[*Num];
	m_pSysLight[NumberSys]->m_bLookAtTarget = true;
	m_pSysLight[NumberSys]->m_nMoveMode = 0;

}
void c_Light_Mgr::Uninit_LightMgr(void)
{
	m_pSunLight = NULL;
	for(int nL = 0; nL < MAX_LIGHT_IN_LIST;nL ++)
	{
		m_pSpotList[nL] = NULL;
		m_pPointList[nL] = NULL;
	}
	for(int nLs = 0; nLs < MAX_LIGHT_IN_SYS;nLs ++)
		m_pSysLight[nLs] = NULL;
}
void c_Light_Mgr::Update_LightMgr(void)
{
	for(int nLs = 0; nLs < MAX_LIGHT_IN_SYS;nLs ++)
		if(!m_pSysLight[nLs]) continue;
		else
			m_pSysLight[nLs]->UpdateLight();

}
void c_Light_Mgr::Draw_LightMgr(void)
{
}
HRESULT c_Light_Mgr::Create_PointLight(int* Number)
{
	HRESULT hr;
	int Num;
	hr = CheckLightIntList(&Num);
	if(hr == S_FALSE)	//まずライト配列の中に空き状態を確認
		return hr;
	else	
	{
		//ポイントライト配列の空き状態を確認
		for(int nL = 0; nL < MAX_LIGHT_IN_LIST;nL ++)
		{
			if(m_pPointList[nL]) continue;
			if(nL >= MAX_LIGHT_IN_LIST) 
			{
				hr = S_FALSE;
				break;
			}
			else//空いてるなら、先ライト配列からもらった番号を使ってライト作成
			{
				//ポイントライト配列に要素追加
				m_pPointList[nL]  = new int;
				*m_pPointList[nL]	 = Num;
				//ライト配列の作成
				m_pSysLight[Num] = new c_Light;
				m_pSysLight[Num]->CreatLightPointDefault(Num);
				*Number = nL;
				hr = S_OK;
				break;
			}

		}
	}
	return hr;
}
HRESULT c_Light_Mgr::Create_SpotLight(int* Number,D3DXVECTOR3 Target,D3DXVECTOR3 vPos)
{
	HRESULT hr;
	int Num;
	hr = CheckLightIntList(&Num);//まずライト配列の中に空き状態を確認
	if(hr == S_FALSE)	
		return hr;
	else	
	{
		//ポイントライト配列の空き状態を確認
		for(int nL = 0; nL < MAX_LIGHT_IN_LIST;nL ++)
		{
			if(m_pSpotList[nL]) continue;
			if(nL >= MAX_LIGHT_IN_LIST) 
			{
				hr = S_FALSE;
				break;
			}
			else//空いてるなら、先ライト配列からもらった番号を使ってライト作成
			{
				//ポイントライト配列に要素追加
				m_pSpotList[nL]  = new int;
				*m_pSpotList[nL]	 = Num;
				//ライト配列の作成
				m_pSysLight[Num] = new c_Light;
				m_pSysLight[Num]->CreatLightSpotDefault(Num,Target,vPos);
				*Number = nL;
				hr = S_OK;
				break;
			}

		}
	}
	return hr;
}
HRESULT c_Light_Mgr::CheckLightIntList(int* Num)
{

	for(int nLs = 0; nLs < MAX_LIGHT_IN_SYS;nLs ++)
	{
		if(m_pSysLight[nLs]) continue;
		if(nLs >= MAX_LIGHT_IN_SYS - 1) return S_FALSE;
		*Num  = nLs;
		break;
	}
	return S_OK;
}

void c_Light_Mgr::DeleteLight(int type,int Number)
{
	switch(type)
	{
	case 0 :
		m_pSysLight[*m_pSpotList[Number]]->SwitchForLight(false);
		SAFE_DELETE(m_pSpotList[Number]);
		SAFE_DELETE(m_pSysLight[*m_pSpotList[Number]]);
		break;
	case 1:
		m_pSysLight[*m_pPointList[Number]]->SwitchForLight(false);
		SAFE_DELETE(m_pPointList[Number]);
		SAFE_DELETE(m_pSysLight[*m_pSpotList[Number]]);
		break;
	default:
		break;
	}
}
