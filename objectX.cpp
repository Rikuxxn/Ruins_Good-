//=======================================
//
// X�t�@�C������ [objectX.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "objectX.h"
#include "renderer.h"
#include "manager.h"

//=======================================
// �R���X�g���N�^
//=======================================
CObjectX::CObjectX()
{
	// �l�̃N���A
	m_nIdxTexture = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_pMesh = NULL;
	m_pBuffMat = NULL;								// �}�e���A���ւ̃|�C���^
	m_dwNumMat = NULL;								// �}�e���A����
	m_mtxWorld = {};								// ���[���h�}�g���b�N�X
	m_nType = 0;
	for (int nCnt = 0; nCnt < MAX_PATH; nCnt++)
	{
		m_szPath[nCnt] = NULL;
	}
	m_pShadow = NULL;
}
//=======================================
// �f�X�g���N�^
//=======================================
CObjectX::~CObjectX()
{
	// �Ȃ�
}
//=======================================
// ��������
//=======================================
CObjectX* CObjectX::Create(const char* pFilepath,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CObjectX* pObjectX;

	if (CObject::GetNumObject() < MAX_OBJECT - 1)
	{
		pObjectX = new CObjectX;

		pObjectX->m_pos = pos;
		pObjectX->m_rot = D3DXToRadian(rot);
		pObjectX->SetPath(pFilepath);	// �p�X�ۑ�

		// ����������
		pObjectX->Init();

		return pObjectX;
	}
	else
	{// �G���[
		return NULL;
	}
}
//=======================================
// ����������
//=======================================
HRESULT CObjectX::Init(void)
{
	// �e�N�X�`���̎擾
	CTexture* pTexture = CManager::GetTexture();

	// �f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(m_szPath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	// ���b�V�����ǂݍ��܂�Ă��邩�m�F
	if (m_pMesh == NULL)
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂����i���b�V����NULL�ł��j", "�G���[", MB_OK | MB_ICONERROR);
		return 0;
	}

	// ���_���̎擾
	nNumVtx = m_pMesh->GetNumVertices();

	// ���_����0�Ȃ�A���f������Ƃ݂Ȃ�
	if (nNumVtx == 0)
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂����i���_����0�ł��j", "�G���[", MB_OK | MB_ICONERROR);
		return 0;
	}
	else
	{// ���f������

		// ���_�t�H�[�}�b�g�̎擾
		sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

		// ���_�o�b�t�@�̃��b�N
		m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);


		// �ő�l�Ƃ��͂�������Ȃ�


		// ���_�o�b�t�@�̃A�����b�N
		m_pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;// �}�e���A���ւ̃|�C���^

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		m_nIdxTexture = new int[m_dwNumMat];

		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// �e�N�X�`���t�@�C�������݂���
				// �e�N�X�`���̓o�^
				m_nIdxTexture[nCntMat] = pTexture->RegisterX(pMat[nCntMat].pTextureFilename);
			}
			//else
			//{// �e�N�X�`�������݂��Ȃ�
			//	m_nIdxTexture[nCntMat] = -1;
			//}
		}
	}

	// �e�̐���
	m_pShadow = CShadow::Create(m_pos, 200, 55.0f, 0.1f, 55.0f);

	return S_OK;
}
//=======================================
// �I������
//=======================================
void CObjectX::Uninit(void)
{
	// �e�N�X�`���C���f�b�N�X�̔j��
	if (m_nIdxTexture != NULL)
	{
		delete[] m_nIdxTexture;
		m_nIdxTexture = NULL;
	}

	//���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	// �I�u�W�F�N�g�̔j��(�������g)
	this->Release();
}
//=======================================
// �X�V����
//=======================================
void CObjectX::Update(void)
{
	if (m_pShadow != NULL)
	{
		D3DXVECTOR3 shadowPos = m_pos;
		shadowPos.y = 0.05f;

		// �e�̈ʒu�ݒ�
		m_pShadow->SetPosition(shadowPos);
	}
}
//=======================================
// �`�揈��
//=======================================
void CObjectX::Draw(void)
{
	// �e�N�X�`���̎擾
	CTexture* pTexture = CManager::GetTexture();

	// �f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;	// ���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;		// �}�e���A���f�[�^�ւ̃|�C���^

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

	// ���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (m_nIdxTexture[nCntMat] == -1)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
		}
		else
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture[nCntMat]));
		}

		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//=======================================
// �ʒu�̎擾
//=======================================
D3DXVECTOR3 CObjectX::GetPos(void)
{
	return m_pos;
}
//=======================================
// X�t�@�C���p�X�̐ݒ菈��
//=======================================
void CObjectX::SetPath(const char* path)
{
	strcpy_s(m_szPath, path);
}
