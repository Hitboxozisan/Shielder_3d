#pragma once

#include "CameraBase.h"

/// <summary>
/// ���C���J�����N���X
/// </summary>
class CameraMain final : public CameraBase
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

	void FollowTarget();				// �^�[�Q�b�g��Ǐ]����
	void RotateCamera();				// �J��������]������
	void InputAction();					// ���͏���

	static const float INITIALIZE_RANGE_TARGET;		// �^�[�Q�b�g�Ƃ̋����i�����l�j
	static const float RANGE_POSSIBLE_ROCKON;		// ���b�N�I���\����
	//static const float CAMERA_NEAR;					// �J�����`��͈́i��O�j
	//static const float CAMERA_FAR;					// �J�����`��͈́i���j

	float cameraRadius;				// �J������]���a
	float cameraYaw;				// ����������]�p�i���[�j
	float cameraPitch;				// ����������]�p�i�s�b�`�j
};

