//============================================================================
//C_Font.h
//============================================================================
#ifndef _CLASS_FONT_H_
#define _CLASS_FONT_H_
//-----------------------------------
//システムインクルード
#include"Sys_Global_Variable.h"
#include "Sys_Macro.h"
//-----------------------------------
//マスターズインクルード
//-----------------------------------
//マクロ定義
#define FONT_SIZE	(18)
//クラス宣言
class c_Font
{
public:
	c_Font();	//コンスト
	c_Font(LPCSTR lpzFont);	//コンスト
	~c_Font();	//デスコン
	void CreatFont(LPCSTR style,float fsize);				//フォントの種類、サイズ設定
	void SetFontPos(D3DXVECTOR3 pos);						//フォントの表示位置設定
	virtual void Draw();									//フォント描画
	void DrawMessage(LPCSTR message);						// メッセージを描画する
	void DrawCord(LPCSTR message,int data,D3DXVECTOR3 pos);	//フォント種類、描画(int)設定
	void DrawCord(LPCSTR message,long data,D3DXVECTOR3 pos);
	void DrawCord(LPCSTR message,float data,D3DXVECTOR3 pos);	//フォント種類、描画(float)設定

private:
	LPD3DXFONT		m_pFont;
	D3DXVECTOR3		m_vPos;
	float m_fsize;
	LPCSTR			m_lFontStyle;


protected:
};


#endif