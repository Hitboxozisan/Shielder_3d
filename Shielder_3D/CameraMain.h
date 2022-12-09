#pragma once

#include "CameraBase.h"

/// <summary>
/// ���C���J�����N���X
/// </summary>
class CameraMain : public CameraBase
{
public:
	CameraMain(CameraManager* const cameraManager);
	~CameraMain();

	void Initialize();		// ����������
	void Fainalize();		// �I������
	void Activate();		// ����������
	void Deactivate();		// �񊈐�������
	void Update();			// �X�V����

private:
	CameraMain();						// �f�t�H���g�R���X�g���N�^
	CameraMain(const CameraMain&);		// �R�s�[�R���X�g���N�^
	void operator=(const CameraMain&);	// ������Z�q

};

