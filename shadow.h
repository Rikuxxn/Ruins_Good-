//=============================================================================
//
// 影の処理 [shadow.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "object3D.h"

// 影クラス
class CShadow : public CObject3D
{
public:
	CShadow();
	~CShadow();

	static CShadow* Create(D3DXVECTOR3 pos, int nAlpha, float fWidth, float fHeight, float fDepth);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

private:
	static int m_nIdxTexture;
	D3DXVECTOR3 m_pos;					// 位置
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス

};

#endif