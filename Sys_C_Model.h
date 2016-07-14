//-----------------------------------------------------------
//モデルマスタークラスcpp
//-----------------------------------------------------------
#ifndef _C_MODEL_H_
#define _C_MODEL_H_
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
//--------------------------------------
//マスターズインクルード

//--------------------------------------
//マクロ定義

//--------------------------------------
//構造体宣言
#ifndef MODEL_STRUCT
#define MODEL_STRUCT
typedef struct
{
	LPD3DXMESH			pMesh;		//メッシュオブジェクト
	DWORD				dwNumMtrl;	//マテリアル数
	D3DMATERIAL9*		pMtrl;		//マテリアル配列
	LPDIRECT3DTEXTURE9*	pTexture;	//テクスチャ配列
	D3DXATTRIBUTERANGE*	pAttr;		//属性テーブル
	DWORD				dwNumAttr;	//属性数
	D3DXVECTOR3			vCenter;	//境界球中心座標
	float				fRadius;	//境界球半径
	D3DXVECTOR3			vBBox;		//境界ボックス（ハーフサイズ）
}MODEL;
#endif
//--------------------------------------
//クラス宣言
class c_Model
{
public:
	c_Model();
	c_Model(LPCSTR File);
	c_Model(LPCSTR File , D3DXVECTOR3 pos);
	~c_Model();
	void	SetFileName(LPCSTR FileName);
	HRESULT Init_LoadModel(void);
	virtual void UpdateModel(void);
	virtual void DrawModel(void);	
	virtual void UninitModel(void);

	void ReleaseModel(void);
	D3DXMATRIX* GetModelMatrix(void);
	D3DXVECTOR3* GetModelPos(void);
	D3DXVECTOR3	m_vPos;

	HRESULT		 LoadModelShader(void);
	void		UninitModelShader(void);
	MODEL*		m_pModel;
private:
protected:

	
	LPCSTR		m_pszFName;

	D3DXMATRIX	m_matrix;

	
	D3DXVECTOR3	m_vAngle;
	D3DXVECTOR3	m_vScale;

};

#endif