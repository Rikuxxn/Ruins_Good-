//=======================================
//
// X�t�@�C������ [objectX.h]
// Author : TANEKAWA RIKU
//
//=======================================
#ifndef _OBJECTX_H_// ���̃}�N����`������Ă��Ȃ�������
#define _OBJECTX_H_// 2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "object.h"
#include "shadow.h"


// X�t�@�C���N���X
class CObjectX : public CObject
{
public:
	CObjectX();
	~CObjectX();

	// ���f���̎��
	typedef enum
	{
		TYPE_BEAR = 0,
		TYPE_WALL,
		TYPE_MAX
	}MODELTYPE;

	static CObjectX* Create(const char* pFilepath, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void);
	void SetPath(const char* path);

private:
	int* m_nIdxTexture;
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	LPD3DXMESH m_pMesh;					// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;			// �}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;					// �}�e���A����
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	int m_nType;						// ���
	char m_szPath[MAX_PATH];
	CShadow* m_pShadow;					// �e�ւ̃|�C���^

};

#endif