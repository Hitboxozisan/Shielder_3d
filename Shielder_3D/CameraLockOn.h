#pragma once

#include "CameraBase.h"

class CameraLockOn : public CameraBase
{
public:
	CameraLockOn(CameraManager* const cameraManager);
	~CameraLockOn();

	void Initialize();		// ����������
	void Fainalize();		// �I������
	void Activate();		// ����������
	void Deactivate();		// �񊈐�������
	void Update();			// �X�V����

private:
	CameraLockOn();							// �f�t�H���g�R���X�g���N�^
	CameraLockOn(const CameraLockOn&);		// �R�s�[�R���X�g���N�^
	void operator=(const CameraLockOn&);	// ������Z�q
};

