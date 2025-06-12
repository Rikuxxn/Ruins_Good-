//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "player.h"
#include "texture.h"
#include "manager.h"
#include "model.h"
#include "shadow.h"

//=======================================
// �R���X�g���N�^
//=======================================
CPlayer::CPlayer()
{
	// �l�̃N���A
	m_pos = INIT_VEC3;								// �ʒu
	m_rot = INIT_VEC3;								// ����
	m_rotDest = INIT_VEC3;							// ����
	m_move = INIT_VEC3;								// �ړ���
	m_mtxWorld = {};								// ���[���h�}�g���b�N�X
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_apModel[nCnt] = {};						// ���f��(�p�[�c)�ւ̃|�C���^
	}
	m_nNumModel = 0;								// ���f��(�p�[�c)�̑���
	m_playerUse = true;								// �g���Ă��邩�ǂ���
	m_pShadow = NULL;								// �e�ւ̃|�C���^
	m_pMotion = NULL;								// ���[�V�����ւ̃|�C���^
}
//=======================================
// �f�X�g���N�^
//=======================================
CPlayer::~CPlayer()
{
	// �Ȃ�
}
//=======================================
// ��������
//=======================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer* pPlayer;

	if (CObject::GetNumObject() < MAX_OBJECT - 1)
	{
		pPlayer = new CPlayer;

		// ����������
		pPlayer->Init();

		pPlayer->m_pos = pos;
		pPlayer->m_rot = D3DXToRadian(rot);

		return pPlayer;
	}
	else
	{// �G���[
		return NULL;
	}
}
//=======================================
// ����������
//=======================================
HRESULT CPlayer::Init(void)
{
	CModel* pModels[MAX_PARTS];
	int nNumModels = 0;

	// �p�[�c�̓ǂݍ���
	m_pMotion = CMotion::Load("data/motion.txt", pModels, nNumModels);

	for (int nCnt = 0; nCnt < nNumModels && nCnt < MAX_PARTS; nCnt++)
	{
		m_apModel[nCnt] = pModels[nCnt];

		// �I�t�Z�b�g�l��
		m_apModel[nCnt]->SetOffsetPos(m_apModel[nCnt]->GetPos());
		m_apModel[nCnt]->SetOffsetRot(m_apModel[nCnt]->GetRot());
	}

	// �p�[�c������
	m_nNumModel = nNumModels;

	// �v���C���[���g���Ă���
	m_playerUse = true;

	// �e�̐���
	m_pShadow = CShadow::Create(m_pos, 100, 25.0f, 0.1f, 25.0f);

	return S_OK;
}
//=======================================
// �I������
//=======================================
void CPlayer::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// �I�u�W�F�N�g�̔j��(�������g)
	this->Release();
}
//=======================================
// �X�V����
//=======================================
void CPlayer::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();

	// �W���C�p�b�h�̎擾
	CInputJoypad* pInputJoypad = CManager::GetInputJoypad();

	// �W���C�X�e�B�b�N���̎擾
	XINPUT_STATE* pStick = CInputJoypad::GetStickAngle();

	// �J�����̎擾
	CCamera* pCamera = CManager::GetCamera();

	// �J�����̊p�x�̎擾
	D3DXVECTOR3 CamRot = pCamera->GetRot();

	// �ړ����͂����邩���肷��t���O
	bool bIsMoving = false;

	// ��l�� �Q�[���p�b�h�̈ړ�����
	if (pInputJoypad->GetStick() == true)
	{
		// ���X�e�B�b�N�̓��͂��擾
		float stickX = pStick->Gamepad.sThumbLX;
		float stickY = pStick->Gamepad.sThumbLY;

		// �f�b�h�]�[������
		const float DEADZONE = 10922.0f;

		if (fabsf(stickX) < DEADZONE)
		{
			stickX = 0.0f;
		}
		if (fabsf(stickY) < DEADZONE)
		{
			stickY = 0.0f;
		}

		// �X�e�B�b�N���O�����ɓ|����Ă��邩�`�F�b�N
		bool isStickForward = (stickY > DEADZONE);

		// ���K��
		float magnitude = sqrtf(stickX * stickX + stickY * stickY);
		if (magnitude > 0.0f)
		{
			stickX /= magnitude;
			stickY /= magnitude;
		}

		// �J�����̉�]���擾
		float cameraYaw = CamRot.y;

		// �ړ��x�N�g���v�Z
		float moveX = -(stickX * cosf(cameraYaw) + stickY * sinf(cameraYaw));
		float moveZ = stickX * sinf(-cameraYaw) + stickY * cosf(cameraYaw);

		// �ړ��������]
		moveZ = -moveZ;

		// �v���C���[�̈ړ��X�V�i�ʏ푬�x�j
		m_move.x += moveX * PLAYER_SPEED;
		m_move.z += moveZ * PLAYER_SPEED;

		// �v���C���[�̌������X�V
		m_rotDest.y = atan2f(-moveX, -moveZ);

		bIsMoving = true;
	}

	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		bIsMoving = true;

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			// �ړ��ʂ��X�V(����������)
			m_move.x -= sinf(CamRot.y + -D3DX_PI * 0.25f) * PLAYER_SPEED;
			m_move.z -= cosf(CamRot.y + -D3DX_PI * 0.25f) * PLAYER_SPEED;

			m_rotDest.y = CamRot.y - D3DX_PI * 0.25f;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{
			// �ړ��ʂ��X�V(����������)
			m_move.x -= sinf(CamRot.y + -D3DX_PI * 0.75f) * PLAYER_SPEED;
			m_move.z -= cosf(CamRot.y + -D3DX_PI * 0.75f) * PLAYER_SPEED;

			m_rotDest.y = CamRot.y - D3DX_PI * 0.75f;
		}
		else
		{
			// �ړ��ʂ��X�V(����������)
			m_move.z -= sinf(CamRot.y) * PLAYER_SPEED;
			m_move.x += cosf(CamRot.y) * PLAYER_SPEED;

			m_rotDest.y = CamRot.y - D3DX_PI * 0.5f;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		bIsMoving = true;

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			// �ړ��ʂ��X�V(����������)
			m_move.x -= sinf(CamRot.y + D3DX_PI * 0.25f) * PLAYER_SPEED;
			m_move.z -= cosf(CamRot.y + D3DX_PI * 0.25f) * PLAYER_SPEED;

			m_rotDest.y = CamRot.y + (D3DX_PI * 0.25f);
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{
			// �ړ��ʂ��X�V(����������)
			m_move.x -= sinf(CamRot.y + D3DX_PI * 0.75f) * PLAYER_SPEED;
			m_move.z -= cosf(CamRot.y + D3DX_PI * 0.75f) * PLAYER_SPEED;

			m_rotDest.y = CamRot.y + (D3DX_PI * 0.75f);
		}
		else
		{
			// �ړ��ʂ��X�V(����������)
			m_move.z += sinf(CamRot.y) * PLAYER_SPEED;
			m_move.x -= cosf(CamRot.y) * PLAYER_SPEED;

			m_rotDest.y = CamRot.y + D3DX_PI * 0.5f;
		}

	}
	else if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		bIsMoving = true;

		// �ړ��ʂ��X�V(����������)
		m_move.x -= sinf(CamRot.y) * PLAYER_SPEED;
		m_move.z -= cosf(CamRot.y) * PLAYER_SPEED;

		m_rotDest.y = CamRot.y;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		bIsMoving = true;

		// �ړ��ʂ��X�V(����������)
		m_move.x += sinf(CamRot.y) * PLAYER_SPEED;
		m_move.z += cosf(CamRot.y) * PLAYER_SPEED;

		m_rotDest.y = CamRot.y + D3DX_PI;
	}

	// ���[�V�����؂�ւ�
	static CMotion::TYPE currentMotion = CMotion::TYPE_NEUTRAL;

	if (bIsMoving)
	{
		if (currentMotion != CMotion::TYPE_MOVE)
		{
			m_pMotion->StartBlendMotion(CMotion::TYPE_MOVE, 15);
			currentMotion = CMotion::TYPE_MOVE;
		}
	}
	else
	{
		if (currentMotion != CMotion::TYPE_NEUTRAL)
		{
			m_pMotion->StartBlendMotion(CMotion::TYPE_NEUTRAL, 20);
			currentMotion = CMotion::TYPE_NEUTRAL;
		}
	}

	// �����̐��K��
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	m_rot.y += (m_rotDest.y - m_rot.y) * 0.2f;

	// �ʒu���X�V
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;
	m_pos.y += m_move.y;

	if (m_pShadow != NULL)
	{
		D3DXVECTOR3 shadowPos = m_pos;
		shadowPos.y = 0.05f;

		// �e�̈ʒu�ݒ�
		m_pShadow->SetPosition(shadowPos);
	}

	// �ړ��ʂ��X�V(����������)
	m_move.x += (0.0f - m_move.x) * 0.3f;
	m_move.z += (0.0f - m_move.z) * 0.3f;
	m_move.y += (0.0f - m_move.y) * 0.1f;

	int nNumModels = 15;

	// ���[�V�����̍X�V����
	m_pMotion->Update(m_apModel, nNumModels);
}
//=======================================
// �`�揈��
//=======================================
void CPlayer::Draw(void)
{
	// �f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntMat = 0; nCntMat < m_nNumModel; nCntMat++)
	{
		// ���f��(�p�[�c)�̕`��
		if (m_apModel[nCntMat])
		{
			m_apModel[nCntMat]->Draw();
		}
	}
}
//=======================================
// �ʒu�̎擾
//=======================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}
//=======================================
// �����̎擾
//=======================================
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}
//=======================================
// �v���C���[�̔���擾
//=======================================
bool CPlayer::GetPlayerUse(void)
{
	return m_playerUse;
}
