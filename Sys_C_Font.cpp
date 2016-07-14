//============================================================================
//C_Font.h
//============================================================================
//-----------------------------------
//システムインクルード
#include "Sys_C_Font.h"
#include <string.h>
//-----------------------------------
//マスターズインクルード

c_Font::c_Font()
{
	D3DV_INIT(m_vPos); 
	m_pFont = NULL;
	m_fsize = 10.0f;
	m_lFontStyle = "Terminal";
}
c_Font::c_Font(LPCSTR lpzFont)
{
	D3DV_INIT(m_vPos); 
	m_pFont = NULL;
	m_fsize = 10.0f;
	m_lFontStyle = lpzFont;
}
c_Font::~c_Font()
{
	if(m_pFont != NULL)
	{// デバッグ情報表示用フォントを設定
		m_pFont->Release();
		m_pFont = NULL;
	}
}
void c_Font::CreatFont(LPCSTR style,float fsize)
{
	if(style != NULL)
		m_lFontStyle = style;

	if(fsize != 0.0f)
	m_fsize = fsize;

	D3DXCreateFont(g_pD3DDevice, m_fsize, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
	OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T(style), &m_pFont);

}
void c_Font::SetFontPos(D3DXVECTOR3 pos)
{
	this->m_vPos.x = pos.x;
	this->m_vPos.y = pos.y;
	this->m_vPos.z = 0;
}

void c_Font::Draw()
{
	
	RECT rect = {m_vPos.x, m_vPos.y, SCREEN_WIDTH_WIN, SCREEN_HEIGHT_WIN};
	char aStr[25];

	wsprintf(&aStr[0], "あいうえお\n");

	// テキスト描画
	m_pFont -> DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
}
void c_Font::DrawMessage(LPCSTR message)
{
	
	RECT rect = {m_vPos.x, m_vPos.y, SCREEN_WIDTH_WIN, SCREEN_HEIGHT_WIN};
	char aStr[128];

	wsprintf(&aStr[0], message);

	// テキスト描画
	m_pFont -> DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
}

void c_Font::DrawCord(LPCSTR message,int data,D3DXVECTOR3 pos)
{
	RECT rect = {pos.x, pos.y, SCREEN_WIDTH_WIN, SCREEN_HEIGHT_WIN};
	char aStr[128];
	char bStr[128];
	wsprintf(&aStr[0], message);
	wsprintf(&bStr[0], "%d\n",data);
	strcat_s(aStr,128,bStr);

	// テキスト描画
	m_pFont -> DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
}
void c_Font::DrawCord(LPCSTR message,long data,D3DXVECTOR3 pos)
{
	RECT rect = {pos.x, pos.y, SCREEN_WIDTH_WIN, SCREEN_HEIGHT_WIN};
	char aStr[128];
	char bStr[128];
	wsprintf(&aStr[0], message);
	wsprintf(&bStr[0], "%ld\n",data);
	strcat(aStr,bStr);

	// テキスト描画
	m_pFont -> DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
}
void c_Font::DrawCord(LPCSTR message,float data,D3DXVECTOR3 pos)
{
	RECT rect = {(LONG)pos.x, (LONG)pos.y, SCREEN_WIDTH_WIN, SCREEN_HEIGHT_WIN};
	char aStr[64];
	char bStr[64];
	wsprintf(&aStr[0], message);
	wsprintf(&bStr[0], "%f\n",data);
	strcat(aStr,bStr);

	// テキスト描画
	m_pFont -> DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
}
//-----------------------------------------------------------
//End of File
//-----------------------------------------------------------