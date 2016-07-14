//-----------------------------------------------------------
//CLASS_UI_INPUTUWINDOW_SHIP_H
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "C_UI_MessageBox.h"
c_UI_MessageBox::c_UI_MessageBox()
{
	m_pPlate	= NULL;
	m_pFont		= NULL;
	m_bInput	= true;
}
c_UI_MessageBox::~c_UI_MessageBox()
{
}
void c_UI_MessageBox::Init_MessageBox(void)
{
	m_pPlate = new c_Primitive2D(FILENAME_MESSAGEBOX_DEAULT_TEX);
	m_pPlate->CreatTexture_Primitive2D();
	m_pPlate->MakeVertexBuff_Primitive2D();
	m_pPlate->m_vPos = MessageBoxPos;
	m_pPlate->m_fTexSizePro.x = MessageBoxSize.x;
	m_pPlate->m_fTexSizePro.y = MessageBoxSize.y;

	m_pFont = new c_Font;
	m_pFont->CreatFont("HGP創英角ﾎﾟｯﾌﾟ体",30.0f);
	m_pFont->SetFontPos(m_pPlate->m_vPos + MessageFontPos);
}
void c_UI_MessageBox::Update_MessageBox(void)
{
	if(m_bInput)
	{
		m_lpzText = m_cMessenger.Update_MessengerLPC();

		if(GetKeyboardTrigger(DIK_RETURN))
			m_bInput = false;
	}

	m_pPlate->SetVerTexBuff_Primitive2DCenter();
}
void c_UI_MessageBox::Openinput(void)
{
	m_bInput = true;
}
void c_UI_MessageBox::Uninit_MessageBox(void)
{
	m_pPlate->Uninit_Primitive2D();
	SAFE_DELETE(m_pPlate);
	SAFE_DELETE(m_pFont);

}
void c_UI_MessageBox::Draw_MessageBox(void)
{
	//m_pPlate->Draw_Primitive2D();
	m_pFont->DrawMessage(this->m_lpzText);
	m_cMessenger.Draw_MessengerInfo();
}
//-----------------------------------------------------------
//End of File
//-----------------------------------------------------------