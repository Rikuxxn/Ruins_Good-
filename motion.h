//=============================================================================
//
// ���[�V�������� [motion.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "model.h"

#define MAX_WORD (1024)		// �ő啶����
#define MAX_PARTS (32)		// �ő�p�[�c��
#define MAX_KEY (128)		// �ő�L�[��

// ���[�V�����N���X
class CMotion
{
public:
	CMotion();
	~CMotion();

	// ���[�V�����̎��
	typedef enum
	{
		TYPE_NEUTRAL = 0,	// �ҋ@
		TYPE_MOVE,			// �ړ�
		TYPE_ACTION,		// �A�N�V����
		TYPE_MAX
	}TYPE;

	static CMotion* Load(const char* pFilepath, CModel* pModel[], int& nNumModel);
	void Update(CModel* pModel[], int& nNumModel);
	void StartBlendMotion(TYPE motionTypeBlend, int nFrameBlend);
	void SetMotion(TYPE motionType);

private:

	// �L�[�\����
	typedef struct
	{
		float fPosX;							// �ʒu(X)
		float fPosY;							// �ʒu(Y)
		float fPosZ;							// �ʒu(Z)
		float fRotX;							// ����(X)
		float fRotY;							// ����(Y)
		float fRotZ;							// ����(Z)
	}KEY;

	// �L�[���\����
	typedef struct
	{
		int nFrame;								// �Đ��t���[��
		KEY aKey[MAX_PARTS];					// �e�p�[�c�̃L�[�v�f
	}KEY_INFO;

	// ���[�V�������̍\����
	typedef struct
	{
		bool bLoop;								// ���[�v���邩�ǂ���
		int nNumKey;							// �L�[�̑���
		KEY_INFO aKeyInfo[MAX_KEY];				// �L�[���
		int startKey, startFrame;
	}MOTION_INFO;

	MOTION_INFO m_aMotionInfo[TYPE_MAX];		// ���[�V�������
	TYPE m_motionType;							// ���[�V�����̎��
	int m_nNumMotion;							// ���[�V��������
	bool m_bLoopMotion;							// ���[�v���邩�ǂ���
	int m_nNumKey;								// �L�[�̑���
	int m_nKey;									// ���݂̃L�[No.
	int m_nCounterMotion;						// ���[�V�����̃J�E���^�[

	bool m_bFinishMotion;						// ���݂̃��[�V�������I�����Ă��邩�ǂ���
	bool m_bBlendMotion;						// �u�����h���[�V���������邩�ǂ���
	TYPE m_motionTypeBlend;						// �u�����h���[�V���������邩�ǂ���
	bool m_bLoopMotionBlend;					// �u�����h���[�V���������[�v���邩�ǂ���
	int m_nNumKeyBlend;							// �u�����h���[�V�����̃L�[��
	int m_nKeyBlend;							// �u�����h���[�V�����̌��݂̃L�[No.
	int m_nCounterMotionBlend;					// �u�����h���[�V�����̃J�E���^�[
	int m_nFrameBlend;							// �u�����h�̃t���[����(���t���[�������ău�����h���邩)
	int m_nCounterBlend;						// �u�����h�J�E���^�[

};

#endif