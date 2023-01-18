#pragma once

class Boss;

/// <summary>
/// �J�����N���X
/// </summary>
class Camera
{
public:
	Camera();
	~Camera();

	void Initialize(Boss* inBoss);			// ����������
	void Finalize();						// �I������
	void Activate(VECTOR inPlayerPos,
				  VECTOR inEnemyPos);		// ����������
	void Deactivate();						// �񊈐�������
	void Update(VECTOR inPlayerPos,
				VECTOR inEnemyPos);			// �X�V����
	void ChangeCamera();					// �J������؂�ւ���i�Ǐ]�E���b�N�I���j

	VECTOR GetPosition();					// ���݈ʒu��Ԃ�
	VECTOR GetTargetPosition();				// ���݂̒����_��Ԃ�
	bool IsRockOn();						// ���b�N�I������

private:
	
	// �萔
	static const float TARGET_DISTANCE;
	static const float HORIZONTAL_DISTANCE;
	static const float VERTICAL_DISTANCE;

	static const float CAMERA_DISTANCE;				// �J�����ƃv���C���[�̋���
	static const float DISPLACE_DISTANCE;			// ���S����̂���̋���
	static const float ROCKON_POSSIBLE_DISTANCE;	// ���b�N�I���\����
	static const float ERROR_ADMISSIBLE_DISTANCE;	// ���b�N�I�����Ώۂ�ǂ�Ȃ��덷����
	static const float ROCKON_DISTANCE;				// ���b�N�I�����̃J��������
	static const float ROCKON_VERTICAL_DISTANCE;	// ���b�N�I�����̃J������

	Boss* boss;						// Boss�N���X�̃|�C���^

	// �ϐ�
	float targetDistance;			// �^�[�Q�b�g����
	float horizontalDistance;		// ��������
	float verticalDistance;			// ��������
	
	float cameraRadius;				// �J������]���a
	float cameraYaw;				// ����������]�p�i���[�j
	float cameraPitch;				// ����������]�p�i�s�b�`�j
	float rockOnDistance;			// ���b�N�I���\����
	VECTOR position;				// �J�����̈ʒu
	VECTOR actorPosition;			// �v���C���[�̈ʒu
	VECTOR enemyPosition;			// �G�̈ʒu�i��Ƀ��b�N�I���Ɏg�p�j
	VECTOR targetPosition;			// �����_�̈ʒu

	bool isRockOn;					// ���b�N�I�����Ă��邩

	void UpdatePosition(VECTOR inPlayerPos, VECTOR inEnemyPos);	// actor �� enemy �̌��݈ʒu�̍X�V
	void CalculatingCamerePos();	// �J�����̈ʒu���v�Z 
	void CalculatingTagetPos();		// �����_�̈ʒu���v�Z
	void RotateCamera();			// �J��������]������
	void TargetRockon();			// ���b�N�I���Ώۂ�����
	void ChangeTargetPosition();	// �����_��Ώۂ܂ňړ�������
	
	bool isRockOnPossible();		// ���b�N�I���\��

	void InputAction();				// ���͏���
};

