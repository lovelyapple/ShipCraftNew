//===============================================	=============================
//Ship.h
//============================================================================
#ifndef _CLASS_MASTER_PRIMITIVE_H_
#define _CLASS_MASTER_PRIMITIVE_H_
//-----------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"
//-----------------------------------
//マスターズインクルード
//-----------------------------------
//インスタンスインクルード
//-----------------------------------
//マクロ定義
#define FILE_NAME_DEAULT_PRIMITIVE		("data/Texture/denkyu.png")
//-----------------------------------
//構造体宣言
#ifndef DVERTEX_PRIMITIVE_3D
#define DVERTEX_PRIMITIVE_3D
typedef struct  
{	
	float		x, y, z;		// 頂点
	float		nx, ny, nz;		// 法線ベクトル
	D3DCOLOR	color;			// ディフューズカラー
	float		tu, tv;			// テクスチャ座標
}DVERTEX_PRIMITIVE;
#endif
//-----------------------------------
//クラス宣言
class c_Primitive3D
{
#define MAX_V_FRAME	(5)
public:
	c_Primitive3D();
	c_Primitive3D(LPCSTR fzName);				// コンストラクタ
	~c_Primitive3D();							// デストラクタ
	virtual void	SetFileName(LPCSTR fzName);		// ファイル名の設定
	void			Reset_Primitive(void);			// 内部変数の初期化
	virtual HRESULT Init_Primitive(void);			// 初期化
			HRESULT	CreatePrimitiveBuffOnly(void);	// バッファの作成のみ
			void	Uninit_Primitive(void);			// 終了処理

			void	SetPos(D3DXVECTOR3 Pos);						// Posの変更
			void	SetSize(D3DXVECTOR3 size);						// Sizeの変更
			void	SetRot(D3DXVECTOR3 Ros);						// Rotの変更
			void	SetAlpha(float fAlpha);							// Alphaの変更
			void	SetOblique(D3DXVECTOR3* input);					// 斜め度合の設定
			void	SetReversal(bool bReversa);						// 水平反転するか
			void	SetTextureUV(int V,int U,int Frame);			// UVの設定


			void	SetVerTexBuff(void);							// ALLバッファ変更
			void	SetVerTexBuffSize(void);						// SizeBuffのみ更新
			void	SetVerTexBuffSizeOblique(void);					// 傾斜込SizeBuffの更新
			void	SetVerTexBuffUV(void);							// UVBuffのみ更新
			void	SetVerTexBuffUVReversa(void);					// UVBuffのみ更新
			void	SetVerTexBuffAlpha(void);						// AlphaBuffのみ更新
		
			void	Update_PrimitiveNormal(void);					// 更新
			void	Update_PrimitiveMatrixOnly(void);				// マトリックスのみ更新

			void	SetTexRecUVFrame(int nFrameX,
									 int nFrameY);					//UVフレームの設定
			void	SetWatchCamera(bool input);						//カメラ注視設定

	virtual void	DrawPrimitive();								// 描画
			void	DrawPrimitiveAntialiasing(void);				//アンチエリアシング描画
			void	DrawPrimitiveOtherTexture(LPDIRECT3DTEXTURE9 pD3DTexture);

	D3DXMATRIX		GetMatrix(void);
	D3DXVECTOR3		GetPos(void);
	D3DXVECTOR3		GetSize(void);
	
protected:
	LPDIRECT3DVERTEXBUFFER9			m_pD3DVertexBuffer;
	LPDIRECT3DTEXTURE9				m_pD3DTexture;
	LPCSTR							m_pszFName;

	D3DXMATRIX						m_mMatrix;						// マトリックス
	D3DXVECTOR3						m_vPos;							// 3D絶対座標
	D3DXVECTOR3						m_vRot;							// 自転角度
	D3DXVECTOR3						m_vSize;						// サイズ
	D3DXVECTOR3						m_vOblique[2];					// 傾斜の度合	
	float							m_fAlpha;						// Alpha
	bool							m_bWatchCamera;					// プリ道v部
	bool							m_bUReversal;					// UVの水平反転
	int								m_nMAXUVFrame[2];				// 最大UVFrame
	int								m_nMaxFrameU[MAX_V_FRAME];		// Vごとの最大Uサイズ
	int								m_nFrameUPerTimt[MAX_V_FRAME];	// VごとのU更新するタイムフレーム数
	int								m_nMaxFrameV;					// Vの最大数,最大MAX_V_FRAME　	
	int								m_nRecFrameU;					// 現在UV_Xのフレーム数
	int								m_nRecFrameV;					// 現在UV_Yのフレーム数

	
};


#endif