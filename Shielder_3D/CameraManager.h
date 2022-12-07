#pragma once

class Camera;

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
		MAIN = 0,
		LOCK_ON
	};

	void Initialize();		// ����������
	void Finalize();		// �I������
	void Update();
	void Draw();

	void SetNextCamera();		// ���̃J�������Z�b�g
	void GetCurrentCamera();	// ���݂̃J������Ԃ�

private:
	CameraManager(const CameraManager&);	// �R�s�[�R���X�g���N�^
	void operator=(const CameraManager&);	// �R�s�[������Z�q

	Camera* eachCamera[Camera::LOCK_ON];	// �e�J�����̃C���X�^���X
	Camera* currentPointer;					// ���݂̃J�����̃|�C���^

	void ChangeCamera();					// �J������ύX����
};

