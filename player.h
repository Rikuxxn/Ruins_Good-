//=============================================================================
//
// �v���C���[���� [player.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "object.h"
#include "model.h"
#include "shadow.h"
#include "motion.h"

#define MAX_PARTS (32)		// �ő�p�[�c��
#define PLAYER_SPEED (0.90f)// �ړ��X�s�[�h

// �v���C���[�N���X
class CPlayer : public CObject
{
public:
	CPlayer();
	~CPlayer();

	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetRot(void);
	bool GetPlayerUse(void);

private:
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXVECTOR3 m_rotDest;				// ����
	D3DXVECTOR3 m_move;					// �ړ���
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	CModel* m_apModel[MAX_PARTS];		// ���f��(�p�[�c)�ւ̃|�C���^
	int m_nNumModel;					// ���f��(�p�[�c)�̑���
	bool m_playerUse;					// �g���Ă��邩�ǂ���
	CShadow* m_pShadow;					// �e�ւ̃|�C���^
	CMotion* m_pMotion;					// ���[�V�����ւ̃|�C���^
	CMotion::TYPE m_currentMotion;		// ���݂̃��[�V����
};

#endif
