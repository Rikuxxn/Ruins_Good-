//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _TEXTURE_H_// ���̃}�N����`������Ă��Ȃ�������
#define _TEXTURE_H_// 2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define MAX_TEXTURE (32)

// �e�N�X�`���N���X
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
		"data/TEXTURE/eye.png"
	};

	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];
	static int m_nNumAll;
};

#endif