#pragma once

class CameraBase;
class Player;

/// <summary>
/// �J�����}�l�[�W���[
/// </summary>
class CameraManager final
{
public:
	CameraManager();
	~CameraManager();

	// �J�����̎��
	enum Camera
	{
		MAIN = 0,		// ��Ɏg�p����J����
		//START,		// �Q�[���J�n���̉��o�p�J����

		CAMERA_AMOUNT	// �J�����̎�ސ�
	};

	void Initialize();		// ����������
	void Finalize();		// �I������
	void Update();			// �X�V����

	//void SetRockOnPosition();
	void SetActorPosition(VECTOR inActorPosition);	// �A�N�^�[�̈ʒu��ݒ肷��
	void SetTargetPosition(VECTOR inPosition);		// �����_��ݒ肷��
	void SetNextCamera(Camera next);				// ���̃J�������Z�b�g
	//Camera GetCurrentCamera();					// ���݂̃J������Ԃ�

	VECTOR GetPosition();							// �J�����̌��ݒn��Ԃ�
	VECTOR GetDirection();							// �J�����̌�����Ԃ�

private:
	CameraManager(const CameraManager&);	// �R�s�[�R���X�g���N�^
	void operator=(const CameraManager&);	// �R�s�[������Z�q

	CameraBase* eachCameras[Camera::CAMERA_AMOUNT];	// �e�J�����̃C���X�^���X
	CameraBase* currentPointer;						// ���݂̃J�����̃|�C���^
	Camera		currentCamera;						// ���݂̃J����
	Camera		nextCamera;							// ���̃J����

	//Player* const player;							// �v���C���[�N���X�̃|�C���^

	void ChangeCamera();							// �J������ύX����
};

