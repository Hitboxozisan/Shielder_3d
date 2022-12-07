#pragma once

#include "Camera.h"

/// <summary>
/// ���C���J�����N���X
/// </summary>
class CameraMain : public Camera
{
public:
	CameraMain(CameraManager* const cameraManager);
	~CameraMain();

	void Initialize();		// ����������
	void Fainalize();		// �I������
	void Activate();		// ����������
	void Deactivate();		// �񊈐�������
	void Update();			// �X�V����
	void Draw();			// �`�揈��

private:
	//CameraMain();

};

