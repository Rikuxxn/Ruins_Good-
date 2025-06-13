//=======================================
//
// �����_�����O���� [renderer.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "renderer.h"
#include "object.h"
#include "object2D.h"
//#include "player.h"
#include "manager.h"

// �ÓI�����o�ϐ��錾
CDebugProc* CRenderer::m_pDebug = NULL;

//=======================================
// �R���X�g���N�^
//=======================================
CRenderer::CRenderer()
{
	// �l�̃N���A
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}
//=======================================
// �f�X�g���N�^
//=======================================
CRenderer::~CRenderer()
{
	// ���͂Ȃ�

}
//=======================================
// ����������
//=======================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// DirectX3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// �p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;									// �E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// DirectX3D�f�o�C�X�̐���
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		// DirectX3D�f�o�C�X�̐���
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			//DirectX3D�f�o�C�X�̐���
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	if (m_pDebug == NULL)
	{
		// �f�o�b�O�t�H���g�̏�����
		m_pDebug->Init();
	}

	return S_OK;
}
//=======================================
// �I������
//=======================================
void CRenderer::Uninit(void)
{
	// �f�o�b�O�t�H���g�̏I������
	m_pDebug->Uninit();

	// Direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}
//=======================================
// �X�V����
//=======================================
void CRenderer::Update(void)
{

	// ���ׂẴI�u�W�F�N�g�̍X�V����
	CObject::UpdateAll();

}
//=======================================
// �`�揈��
//=======================================
void CRenderer::Draw(int fps)
{
	// ��ʃN���A
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 255, 255, 255), 1.0f, 0);

	// �`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{// �`��J�n�����������ꍇ

		// ���ׂẴI�u�W�F�N�g�̕`�揈��
		CObject::DrawAll();

//#ifdef _DEBUG

		CPlayer* pPlayer = CManager::GetPlayer();	// �v���C���[�̎擾
		CCamera* pCamera = CManager::GetCamera();	// �J�����̎擾

		// FPS�l�̃f�o�b�O�\��
		m_pDebug->Print("FPS:%d", fps);
		m_pDebug->Draw(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0, 0);

		if (pPlayer && pPlayer->GetPlayerUse() == true)
		{
			D3DXVECTOR3 Pos = pPlayer->GetPos();

			m_pDebug->Print("�v���C���[�̈ʒu : (X %.1f,Y %.1f,Z %.1f)", Pos.x, Pos.y, Pos.z);
			m_pDebug->Draw(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0, 20);
		}
		else
		{
			m_pDebug->Print("�v���C���[�Ȃ��i���S or �������j");
			m_pDebug->Draw(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 0, 20);
		}

		// �J�����̊p�x�̎擾
		D3DXVECTOR3 rot = pCamera->GetRot();

		// �J�����̃f�o�b�O�\��
		m_pDebug->Print("�J�����̊p�x : (X:%.2f Y:%.2f)", rot.x,rot.y);
		m_pDebug->Draw(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0, 60);

		//// ����̃f�o�b�O�\��
		//m_pDebug->Print("�ʏ�e [SPACE]");
		//m_pDebug->Draw(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 60);
		//m_pDebug->Print("�z�[�~���O�e [H]");
		//m_pDebug->Draw(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 80);
		//m_pDebug->Print("�|�[�Y [P]");
		//m_pDebug->Draw(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 100);
		//m_pDebug->Print("�Ĕz�u [R]");
		//m_pDebug->Draw(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 120);

		//m_pDebug->Print("�G�̑��� : (%d)", CEnemy::GetNum());
		//m_pDebug->Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 0, 140);
		//m_pDebug->Print("�G(1)�̐� : (%d)", CEnemy::GetNumType1());
		//m_pDebug->Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 0, 160);
		//m_pDebug->Print("�G(2)�̐� : (%d)", CEnemy::GetNumType2());
		//m_pDebug->Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 0, 180);
		//m_pDebug->Print("�G(3)�̐� : (%d)", CEnemy::GetNumType3());
		//m_pDebug->Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 0, 200);

//#endif
		// �`��I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=======================================
// �f�o�b�O�擾
//=======================================
CDebugProc* CRenderer::GetDebug(void)
{
	return m_pDebug;
}
