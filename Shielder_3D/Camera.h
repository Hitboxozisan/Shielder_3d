#pragma once

class CameraManager;

//-----------------------------------------------------------------------------
// �J�����x�[�X�N���X
//-----------------------------------------------------------------------------
class Camera
{
public:
	Camera(CameraManager* const cameraManager);
	virtual ~Camera();

	virtual void Initialize() = 0;		// ����������
	virtual void Fainalize() = 0;		// �I������
	virtual void Activate() = 0;		// ����������
	virtual void Deactivate() = 0;		// �񊈐�������
	virtual void Update() = 0;			// �X�V����
	virtual void Draw() = 0;			// �`�揈��

	int GetId();			// ���ʔԍ���Ԃ�

protected:
	CameraManager* parent;	// �J�����}�l�[�W���[�̃|�C���^

	int id;					// �J�����̎��ʔԍ��i����͎g�p���Ȃ�������̂��߁j
	VECTOR position;		// ���݈ʒu
	VECTOR nextPosition;	// ���t���[���ł̃|�W�V����
	VECTOR prevPosition;	// �O�t���[���ł̃|�W�V����
	VECTOR direction;		// �J�����̌���
	VECTOR nextDirection;	// ���t���[���̌���
	VECTOR prevDirection;	// �O�t���[���ł̌���

private:
	Camera();						// �f�t�H���g�R���X�g���N�^
	Camera(const Camera&);			// �R�s�[�R���X�g���N�^
	void operator=(const Camera&);	// ������Z�q

};

