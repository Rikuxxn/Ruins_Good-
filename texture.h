//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _TEXTURE_H_//このマクロ定義がされていなかったら
#define _TEXTURE_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_TEXTURE (32)

// テクスチャクラス
class CTexture
{
public:
	CTexture();
	~CTexture();

	HRESULT Load(void);
	void Unload(void);
	int Register(const char* pFilename);
	int RegisterX(const char* pFilename);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

private:
	const char* TEXTURE[MAX_TEXTURE] =
	{
		"data/TEXTURE/bg-back.png",
		"data/TEXTURE/bg-stars.png",
		"data/TEXTURE/bg_planettop.png",
		"data/TEXTURE/bg_planetunder.png",
		"data/TEXTURE/ship2.png",
		"data/TEXTURE/enemy001.png",
		"data/TEXTURE/enemy004.png",
		"data/TEXTURE/enemy003.png",
		"data/TEXTURE/effect000.jpg",
		"data/TEXTURE/explosion100.png",
		"data/TEXTURE/bullet2.png",
		"data/TEXTURE/bullet.png",
		"data/TEXTURE/num001.png",
		"data/TEXTURE/pause.png",
		"data/TEXTURE/time.png",
		"data/TEXTURE/colon.png",
		"data/TEXTURE/ground.png",
		"data/TEXTURE/wall001.jpg",
		"data/TEXTURE/selectBG.png",
		"data/TEXTURE/shadow000.jpg",
		"data/TEXTURE/playerface.png",
		"data/TEXTURE/playertex.png",
		"data/TEXTURE/playertex2.png",
	};

	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];
	static int m_nNumAll;
};

#endif