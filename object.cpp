//=======================================
//
// �I�u�W�F�N�g���� [object.cpp]
// Author : TANEKAWA RIKU
//
//=======================================
#include "object.h"
#include "camera.h"
#include "manager.h"

// �ÓI�����o�ϐ��錾
CObject* CObject::m_apObject[MAX_PRIORITY_2D][MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;

//=======================================
// �R���X�g���N�^
//=======================================
CObject::CObject(int nPriority)
{
	m_nID = 0;
	m_nPriority = 0;
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (m_apObject[nPriority][nCnt] == NULL)
		{
			m_apObject[nPriority][nCnt] = this;	// �������g����
			m_nPriority = nPriority;
			m_nID = nCnt;				// �������g��ID��ۑ�
			m_nNumAll++;				// �������J�E���g�A�b�v
			break;
		}
	}
	m_type = TYPE_NONE;
}
//=======================================
// �f�X�g���N�^
//=======================================
CObject::~CObject()
{
	// ���͂Ȃ�

}
//=======================================
// ���ׂẴI�u�W�F�N�g�̔j��
//=======================================
void CObject::ReleaseAll(void)
{
	for (int nPriority = 0; nPriority < MAX_PRIORITY_2D; nPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			if (m_apObject[nPriority][nCnt] != NULL)
			{
				// �I������
				m_apObject[nPriority][nCnt]->Uninit();
			}
		}
	}
}
//=======================================
// ���ׂẴI�u�W�F�N�g�̍X�V����
//=======================================
void CObject::UpdateAll(void)
{
	for (int nPriority = 0; nPriority < MAX_PRIORITY_2D; nPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			if (m_apObject[nPriority][nCnt] != NULL)
			{
				// �X�V����
				m_apObject[nPriority][nCnt]->Update();
			}
		}
	}
}
//=======================================
// ���ׂẴI�u�W�F�N�g�̕`�揈��
//=======================================
void CObject::DrawAll(void)
{
	//�J�����̎擾
	CCamera* pCamera = CManager::GetCamera();

	// �J�����̐ݒ�
	pCamera->SetCamera();

	for (int nPriority = 0; nPriority < MAX_PRIORITY_2D; nPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			if (m_apObject[nPriority][nCnt] != NULL)
			{
				// �`�揈��
				m_apObject[nPriority][nCnt]->Draw();
			}
		}
	}
}
//=======================================
// �I�u�W�F�N�g�̔j��
//=======================================
void CObject::Release(void)
{
	int nIdx = this->m_nID;
	int nPriority = this->m_nPriority;

	if (m_apObject[nPriority][nIdx] != NULL)
	{
		// �I�u�W�F�N�g�̔j��(�������g)
		delete m_apObject[nPriority][nIdx];
		m_apObject[nPriority][nIdx] = NULL;

		m_nNumAll--;	// �������J�E���g�_�E��
	}
}
//=======================================
// �I�u�W�F�N�g�̑����̎擾
//=======================================
int CObject::GetNumObject(void)
{
	return m_nNumAll;
}
//=======================================
// �I�u�W�F�N�g�̎擾
//=======================================
CObject* CObject::GetObject(int nPriority,int nIdx)
{
	return m_apObject[nPriority][nIdx];
}
//=======================================
// �^�C�v�̐ݒ菈��
//=======================================
void CObject::SetType(TYPE type)
{
	m_type = type;
}
//=======================================
// �^�C�v�̎擾
//=======================================
CObject::TYPE CObject::GetType(void)
{
	return m_type;
}
