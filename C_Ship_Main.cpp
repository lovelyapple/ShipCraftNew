//-----------------------------------------------------------
//CLASS_SHIP_MAIN
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "C_Ship_Main.h"
c_Ship::c_Ship()
{
	m_vCenterPos = ShipPos;
}
c_Ship::~c_Ship()
{
}
void c_Ship::InitShip(void)
{
	for(int y = 0; y < SHIP_FULL_SIZE; y ++)
		for(int z = 0; z < SHIP_FULL_SIZE; z++)
			for(int x = 0; x < SHIP_FULL_SIZE ; x ++)
				m_pBlock[y][z][x] = NULL;
}
void c_Ship::UninitShip(void)
{
	for(int y = 0; y < SHIP_FULL_SIZE; y ++)
		for(int z = 0; z < SHIP_FULL_SIZE; z++)
			for(int x = 0; x < SHIP_FULL_SIZE ; x ++)
			{
				FIELDPLACE3 place =  FIELDPLACE3(x,y,z);
				DeleteBlock(place);
			}
}
void c_Ship::UpdateShip(void)
{
	FIELDPLACE3 Limit = FIELDPLACE3(MAX_SHIP_SIZE,MAX_SHIP_SIZE,MAX_SHIP_SIZE);
	for(int y = 0; y < SHIP_FULL_SIZE; y ++)
		for(int z = 0; z < SHIP_FULL_SIZE; z++)
			for(int x = 0; x < SHIP_FULL_SIZE ; x ++)
			{
				if(! m_pBlock[y][z][x]) continue;
				
				m_pBlock[y][z][x]->UpdateBlockFieldPosInShip(m_vCenterPos,Limit);
				m_pBlock[y][z][x]->UpdateBlockMatrix();
			}
	if(GetKeyboardTrigger(DIK_N))
		this->SaveRecentlyShip();
	if(GetKeyboardTrigger(DIK_M))
		this->LoadShipFromFile(m_lpzFileName);
}
void c_Ship::DrawShip(void)
{
	for(int y = 0; y < SHIP_FULL_SIZE; y ++)
		for(int z = 0; z < SHIP_FULL_SIZE; z++)
			for(int x = 0; x < SHIP_FULL_SIZE ; x ++)
			{
				if(m_pBlock[y][z][x])
					m_pBlock[y][z][x]->DrawModel();
			}

}
void c_Ship::CreateBlock(FIELDPLACE3 place,int nType)
{

	if(!m_pBlock[place.y][place.z][place.x])
	{
		m_pBlock[place.y][place.z][place.x] = new c_Block;

		m_pBlock[place.y][place.z][place.x]->SetFileName(m_cFileMgr.GetFileName(FILE_TYPE_BLOCK,nType));
		m_pBlock[place.y][place.z][place.x]->m_uPlace.x = place.x;
		m_pBlock[place.y][place.z][place.x]->m_uPlace.y = place.y;
		m_pBlock[place.y][place.z][place.x]->m_uPlace.z = place.z;
		m_pBlock[place.y][place.z][place.x]->m_uStats.nType = nType;
		m_pBlock[place.y][place.z][place.x]->Init_LoadModel();
	}

}
void c_Ship::DeleteBlock(FIELDPLACE3 place)
{
	if(m_pBlock[place.y][place.z][place.x])
	{
		m_pBlock[place.y][place.z][place.x]->UninitModel();
		SAFE_DELETE(m_pBlock[place.y][place.z][place.x]);
		
	}

}
HRESULT c_Ship::SaveRecentlyShip(void)
{
	FILE* fp;
	if((fp = fopen(this->m_lpzFileName,"w")) == NULL)
	{
		return S_FALSE;
	}
	else
	{
		for(int y = 0; y < SHIP_FULL_SIZE; y ++)
			for(int z = 0; z < SHIP_FULL_SIZE; z++)
				for(int x = 0; x < SHIP_FULL_SIZE ; x ++)
					{
						if(m_pBlock[y][z][x] == NULL)
						{
							fprintf(fp,"%d,",99);
						}
						else
						{	
							fprintf(fp,"%d,",m_pBlock[y][z][x]->m_uStats.nType);
						}

						if(x == SHIP_FULL_SIZE-1)
						{
							fprintf(fp,"\n",99);
						}

					}
	}
	fclose(fp);
	return S_OK;
}
HRESULT	c_Ship::LoadShipFromFile(LPCSTR FileName)
{
	UninitShip();

	this->m_lpzFileName = FileName;
	FILE* fpc;
	if((fpc = fopen(m_lpzFileName,"r")) == NULL)
	{
		return 1;
	}
	else
	{
		for(int y = 0; y < SHIP_FULL_SIZE; y ++)
			for(int z = 0; z < SHIP_FULL_SIZE; z++)
				{
					int block[SHIP_FULL_SIZE];
					for(int i = 0;i < SHIP_FULL_SIZE; i++)	block[i] = 99;

					fscanf(fpc,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",
						&block[0],&block[1],&block[2],&block[3],&block[4],
						&block[5],&block[6],&block[7],&block[8],&block[9],
						&block[10]);
					
					FIELDPLACE3 place[SHIP_FULL_SIZE];
					for(int i = 0;i < SHIP_FULL_SIZE; i++)
					{
						if(block[i] == 99) continue;
						else
						{
							FIELDPLACE3 place;
							place.x = i;
							place.y = y;
							place.z = z;
							this->CreateBlock(place,block[i]);
						}
					}
				}
	}
		fclose(fpc);
	return S_OK;
}
void c_Ship::SetShipName(LPCSTR FileName)
{
	this->m_lpzFileName = FileName;
}
D3DXVECTOR3 c_Ship::GetCenterpos(void)
{
	return this->m_vCenterPos;
}
void c_Ship::ShipPlaceChange(FIELDPLACE3* place)
{
	place->x += MAX_SHIP_SIZE;
	place->y += MAX_SHIP_SIZE;
	place->z += MAX_SHIP_SIZE;
}
//--------------------------------------
//マスターズインクルード
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マネージャーインクルード
//--------------------------------------
//マクロ定義
//--------------------------------------
//構造体宣言
//--------------------------------------
//クラス宣言
//--------------------------------------
//オブジェクトグローバル変数宣言
//--------------------------------------
//係数グローバル変数宣言
//--------------------------------------
//プロトタイプ宣言
//--------------------------------------
//初期化処理
//--------------------------------------
//終了処理
//--------------------------------------
//更新処理
//--------------------------------------
//描画処理
//-----------------------------------------------------------
//End of File
//-----------------------------------------------------------