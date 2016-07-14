//-----------------------------------------------------------
//SYS_CLASS_MESSANGER
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "Sys_C_Messenger.h"
c_Messenger::c_Messenger()
{
	m_cMessage[0] = '\0';
	for(int i = 1; i < MAX_TEXT; i ++)
	{
		m_cMessage[i] = 0x00;
	}
	m_lpMessage =NULL;
	strcpy(m_cMessage,"hello world");
	m_cFont.CreatFont(NULL,0.0f);
}
c_Messenger::~c_Messenger()
{
}

LPCSTR	c_Messenger::Update_MessengerLPC()
{
	m_cInput = 0x00;
	m_cInput = _getch();
	key = _kbhit();
	if(key != 0)
		int a = 0;


	while(1)
	{
		if(_kbhit() == 0  || (  m_cInput) != 0x0d)
			break;
		else if(m_cInput == 0x08)//Enter が押され場合
		{
			for(int i = 0; i < MAX_TEXT;i++)
			{	
				if(m_cMessage[i + 1] == '\0')
				{
					m_cMessage[i] = m_cMessage[i+1];
					m_cMessage[i+1] = '\0';
					break;
				}
			}
		}
		else if ( m_cInput > 0x40 && m_cInput < 0x7b)//a から Z まで入力できる
		{
			for(int i = 0; i < MAX_TEXT;i++)
			{
				if(m_cMessage[i] == '\0')
				{
					m_cMessage[i] = m_cInput;
					m_cMessage[i + 1] = '\0';
					break;
				}
			}
		}
	}
	
	m_lpMessage = &(m_cMessage[0]);

	return m_lpMessage;
}
void c_Messenger::Draw_MessengerInfo(void)
{
	LPCSTR info = &m_cInput;
	m_cFont.DrawCord(info,key,D3DXVECTOR3(100.0f,0.0f,0.0f));
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