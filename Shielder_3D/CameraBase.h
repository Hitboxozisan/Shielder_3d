#pragma once

class CameraManager;

/// <summary>
/// �J�����x�[�X�N���X
/// </summary>
class CameraBase
{
public:
	CameraBase(CameraManager* const cameraManager);
	virtual ~CameraBase();

	virtual void Initialize() = 0;		// ����������
	virtual void Fainalize() = 0;		// �I������
	virtual void Activate() = 0;		// ����������
	virtual void Deactivate() = 0;		// �񊈐�������
	virtual void Update() = 0;			// �X�V����

	void MoveFinish();					// �ړ��\��n�Ɏ��ۂɈړ�����

	void SetActorPosition(VECTOR inActorPosition);			// �A�N�^�[�̍��W��ݒ肷��
	void SetTargetPosition(VECTOR inTargetPosition);		// �����_��ݒ肷��
	const int GetId() const;			// ���ʔԍ���Ԃ�
	const VECTOR GetPosition() const;	// ���݈ʒu��Ԃ�
	const VECTOR GetDirection() const;	// ���݂̌�����Ԃ�

	void DebugMoveCamera();				// �J�����̈ʒu�E�����𓮂���

protected:
	CameraManager* parent;	// �J�����}�l�[�W���[�̃|�C���^

	int	   id;						// �J�����̎��ʔԍ��i����͎g�p���Ȃ�������̂��߁j
	float  rangeTarget;				// �^�[�Q�b�g�Ƃ̋���
	VECTOR position;				// ���݈ʒu
	VECTOR nextPosition;			// ���t���[���ł̃|�W�V����
	VECTOR prevPosition;			// �O�t���[���ł̃|�W�V����
	VECTOR direction;				// �J�����̌���
	VECTOR nextDirection;			// ���t���[���̌���
	VECTOR prevDirection;			// �O�t���[���ł̌���
	VECTOR actorPosition;			// �A�N�^�[�̈ʒu
	VECTOR targetPosition;			// �����_�̈ʒu
	VECTOR rockOnTargetPosition;

private:
	CameraBase();						// �f�t�H���g�R���X�g���N�^
	CameraBase(const CameraBase&);		// �R�s�[�R���X�g���N�^
	void operator=(const CameraBase&);	// ������Z�q

	static const float SPEED;

	float speed;						// �ړ����x
};

