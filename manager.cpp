//=======================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "sound.h"
#include "object3D.h"
#include "objectX.h"
#include "objectBillboard.h"
#include "meshfield.h"

// �ÓI�����o�ϐ��錾
CRenderer* CManager::m_pRenderer = NULL;
CObject2D* CManager::m_pObject2D = NULL;
CInputKeyboard* CManager::m_pInputKeyboard = NULL;
CInputJoypad* CManager::m_pInputJoypad = NULL;
CInputMouse* CManager::m_pInputMouse = NULL;
CSound* CManager::m_pSound = NULL;
CPlayer* CManager::m_pPlayer = NULL;
CEffect* CManager::m_pEffect = NULL;
CScore* CManager::m_pScore = NULL;
CTime* CManager::m_pTime = NULL;
CColon* CManager::m_pColon = NULL;
CPause* CManager::m_pPause = NULL;
CTexture* CManager::m_pTexture = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;
CModel* CManager::m_pModel = NULL;
CMotion* CManager::m_pMotion = NULL;

bool CManager::m_isPaused = false;

//=======================================
// �R���X�g���N�^
//=======================================
CManager::CManager()
{
	// �l�̃N���A
	m_fps = 0;
	m_isPaused = false;
}
//=======================================
// �f�X�g���N�^
//=======================================
CManager::~CManager()
{

}
//=======================================
// ����������
//=======================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �����_���[�̐���
	m_pRenderer = new CRenderer;

	// �����_���[�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}
	
	// �L�[�{�[�h�̐���
	m_pInputKeyboard = new CInputKeyboard;

	// �L�[�{�[�h�̏���������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return -1;
	}

	// �W���C�p�b�h�̐���
	m_pInputJoypad = new CInputJoypad;

	// �W���C�p�b�h�̏���������
	if (FAILED(m_pInputJoypad->Init()))
	{
		return E_FAIL;
	}

	// �}�E�X�̐���
	m_pInputMouse = new CInputMouse;

	// �}�E�X�̏���������
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �T�E���h�̐���
	m_pSound = new CSound;

	// �T�E���h�̏���������
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
	}

	// �J�����̐���
	m_pCamera = new CCamera;

	// �J�����̏���������
	m_pCamera->Init();

	// ���C�g�̐���
	m_pLight = new CLight;

	// ���C�g�̏���������
	m_pLight->Init();


	// �e�N�X�`���̐���
	m_pTexture = new CTexture;

	// �e�N�X�`���̓ǂݍ���
	m_pTexture->Load();

	// ���C�g�̐ݒ菈��
	CLight::AddLight(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CLight::AddLight(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CLight::AddLight(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CLight::AddLight(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CLight::AddLight(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CLight::AddLight(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ���b�V���t�B�[���h�̐���
	CMeshfield::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1200.0f, 1200.0f);

	// ���f���̐���
	CObjectX::Create("data/MODELS/bear.x", D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CObjectX::Create("data/MODELS/wall.x", D3DXVECTOR3(500.0f, 110.0f, 0.0f), D3DXVECTOR3(0.0f, 90.0f, 0.0f));

	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 6.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//// �r���{�[�h�̐���
	//CObjectBillboard::Create(CObjectBillboard::TYPE_ONE, D3DXVECTOR3(0.0f, 20.0f, -350.0f), 120.0f, 60.0f);

	// �X�R�A�̐���
	m_pScore = CScore::Create(920.0f,10.0f,42.0f,58.0f);

	// �^�C���̐���
	m_pTime = CTime::Create(12,15,600.0f,10.0f,42.0f,58.0f);

	// �R�����̐���
	m_pColon = CColon::Create(D3DXVECTOR3(600.0f + 2 * 42.0f, 10.0f, 0.0f), 42.0f / 2, 58.0f);

	//// �|�[�Y�̐���
	//m_pPause = CPause::Create(D3DXVECTOR3(490.0f, 340.0f, 0.0f), 400.0f, 90.0f);

	//m_pSound->Play(CSound::SOUND_LABEL_GAMEBGM);

	return S_OK;
}
//=======================================
// �I������
//=======================================
void CManager::Uninit(void)
{
	// ���ׂẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		// �S�Ẵe�N�X�`���̔j��
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = NULL;
	}

	// �L�[�{�[�h�̏I������
	m_pInputKeyboard->Uninit();

	// �W���C�p�b�h�̏I������
	m_pInputJoypad->Uninit();

	// �}�E�X�̏I������
	m_pInputMouse->Uninit();

	// �T�E���h�̏I������
	m_pSound->Uninit();

	// �|�[�Y�̔j��
	if (m_pPause != NULL)
	{
		// �|�[�Y�̏I������
		m_pPause->Uninit();

		delete m_pPause;
		m_pPause = NULL;
	}

	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		// �����_���[�̏I������
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// �W���C�p�b�h�̔j��
	if (m_pInputJoypad != NULL)
	{
		// �W���C�p�b�h�̏I������
		m_pInputJoypad->Uninit();

		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}

	// �}�E�X�̔j��
	if (m_pInputMouse != NULL)
	{
		// �}�E�X�̏I������
		m_pInputMouse->Uninit();

		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{
		// �}�E�X�̏I������
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	// �J�����̔j��
	if (m_pCamera != NULL)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ���C�g�̔j��
	if (m_pLight != NULL)
	{
		delete m_pLight;
		m_pLight = NULL;
	}

	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		// �����_���[�̏I������
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}
//=======================================
// �X�V����
//=======================================
void CManager::Update(void)
{
	// �L�[�{�[�h�̍X�V
	m_pInputKeyboard->Update();

	// P�L�[�Ń|�[�YON/OFF
	if (m_pInputKeyboard->GetTrigger(DIK_P))
	{
		m_isPaused = !m_isPaused;
	}

	// �|�[�Y���̓Q�[���X�V���Ȃ�
	if (m_isPaused == true)
	{
		// �|�[�Y�̍X�V����
		m_pPause->Update();

		return;
	}

	// �W���C�p�b�h�̍X�V
	m_pInputJoypad->Update();

	// �}�E�X�̍X�V
	m_pInputMouse->Update();

	// �J�����̍X�V
	m_pCamera->Update();

	// ���C�g�̍X�V
	m_pLight->Update();

	// �����_���[�̍X�V
	m_pRenderer->Update();
}
//=======================================
// �`�揈��
//=======================================
void CManager::Draw(void)
{
	// �����_���[�̕`��
	m_pRenderer->Draw(m_fps);

	// �|�[�Y����������
	if (m_isPaused)
	{
		// �|�[�Y�̕`�揈��
		m_pPause->Draw();
	}
}
//=======================================
// �����_���[�̎擾
//=======================================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}
//=======================================
// 2D�I�u�W�F�N�g�̎擾
//=======================================
CObject2D* CManager::GetObject2D(void)
{
	return m_pObject2D;
}
//=======================================
// �L�[�{�[�h�̎擾
//=======================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//=======================================
// �W���C�p�b�h�̎擾
//=======================================
CInputJoypad* CManager::GetInputJoypad(void)
{
	return m_pInputJoypad;
}
//=======================================
// �}�E�X�̎擾
//=======================================
CInputMouse* CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}
//=======================================
// �T�E���h�̎擾
//=======================================
CSound* CManager::GetSound(void)
{
	return m_pSound;
}
//=======================================
// �v���C���[�̎擾
//=======================================
CPlayer* CManager::GetPlayer(void)
{
	return m_pPlayer;
}
//=======================================
// �G�t�F�N�g�̎擾
//=======================================
CEffect* CManager::GetEffect(void)
{
	return m_pEffect;
}
//=======================================
// �X�R�A�̎擾
//=======================================
CScore* CManager::GetScore(void)
{
	return m_pScore;
}
//=======================================
// �^�C���̎擾
//=======================================
CTime* CManager::GetTime(void)
{
	return m_pTime;
}
//=======================================
// �R�����̎擾
//=======================================
CColon* CManager::GetColon(void)
{
	return m_pColon;
}
//=======================================
// �|�[�Y�̎擾
//=======================================
CPause* CManager::GetPause(void)
{
	return m_pPause;
}
//=======================================
// �e�N�X�`���̎擾
//=======================================
CTexture* CManager::GetTexture(void)
{
	return m_pTexture;
}
//=======================================
// �J�����̎擾
//=======================================
CCamera* CManager::GetCamera(void)
{
	return m_pCamera;
}
//=======================================
// ���C�g�̎擾
//=======================================
CLight* CManager::GetLight(void)
{
	return m_pLight;
}
//=======================================
// ���f���̎擾
//=======================================
CModel* CManager::GetModel(void)
{
	return m_pModel;
}
//=======================================
// ���[�V�����̎擾
//=======================================
CMotion* CManager::GetMotion(void)
{
	return m_pMotion;
}
//=======================================
// �|�[�Y�����ǂ����̎擾
//=======================================
bool CManager::GetisPaused(void)
{
	return m_isPaused;
}
