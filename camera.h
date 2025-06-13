//=============================================================================
//
// �J�������� [camera.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _CAMERA_H_//���̃}�N����`������Ă��Ȃ�������
#define _CAMERA_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	// �J�����̎��
	typedef enum
	{
		MODE_EDIT = 0,	// �G�f�B�^�[�J����
		MODE_GAME,		// �Q�[���J����
		MODE_MAX
	}MODE;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void EditCamera(void);
	void GameCamera(void);
	void CameraWithGamepad(float stickX, float stickY);
	D3DXVECTOR3 GetRot(void);

private:
	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posVDest;		// �ړI�̎��_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_posRDest;		// �ړI�̒����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot;			// ����
	float m_fDistance;			// ���_���璍���_�̋���
	MODE m_Mode;				// �J�����̃��[�h
};

#endif