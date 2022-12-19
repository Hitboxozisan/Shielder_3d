#pragma once

#include "Character.h"


class Shield;
class CameraManager;

class Player : public Character
{
public:
	Player(CameraManager* const);
	~Player();

	// ���
	enum State
	{
		NONE,		// ���݂��Ȃ�
		NORMAL,		// �ʏ�
		DEFENSE,	// �h��
		DEAD		// ���S
	};

	void Initialize();		// ����������
	void Finalize();		// �I������
	void Activate();		// ����������
	void Deactivate();		// �񊈐�������
	void Update();			// �X�V����
	void Draw();			// �`�揈��

	void GameStart();			// �Q�[���J�n���i���o�p�j
	void Releaseinvincible();	// ���G��ԉ���

private:
	static const VECTOR INITIAL_POSITION;		// �����ʒu
	static const VECTOR INITIAL_DIRECTION;		// ��������
	static const VECTOR INITIAL_SCALE;			// �����T�C�Y
	static const float  SPEED_INCREASE;			// 1�t���[���̑��x������
	static const float  SPEED_DECREASE;			// 1�t���[���̑��x������
	static const float  MAX_NORMAL_SPEED;		// �ʏ펞�ő呬�x
	static const float  MAX_DEFENSE_SPEED;		// �h�䎞�ő呬�x
	static const float  MAX_HITPOINT;			// �ő�HitPoint

	Shield* shield;								// Shield�N���X�̃|�C���^
	CameraManager* cameraManager;				// CameraManager�N���X�̃|�C���^

	State state;								// ���
	VECTOR inputDirection;						// ���͕���

	float maxSpeed;								// �ő呬�x

	void (Player::* pUpdate)();					// Update�֐��|�C���^

	// �eState���Ƃ̍X�V����
	void UpdateNomal();							// NORMAL���X�V����
	void UpdateDefense();						// DEFENSE���X�V����
	void UpdateDead();							// DEAD���X�V����

	void Move();								// �ړ�����
	///void MoveFinish();						// �ړ��\��n�Ɏ��ۂɈړ�����
	void InputAction();							// ���͏���
	void ChangeSpeed(float afterSpeed);			// �ړ����x��ύX����
	void ActivateShield();						// ����W�J����
	void DeactivateShield();					// �������ł�����
};