#pragma once

#include "Character.h"

using namespace My3dLib;

class Shield;
class Camera;

class Player : public Character
{
public:
	Player(Camera* const);
	~Player();

	// ���
	enum class State
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

	void GameStart();					// �Q�[���J�n���i���o�p�j
	void Releaseinvincible();			// ���G��ԉ���

	float GetCollideRadius();			// �����蔻�苅���a��Ԃ�
	State GetCurrentState();			// ���݂̏�Ԃ�Ԃ�
	Shield *GetShieldPointer();			// ���̃|�C���^��Ԃ�

	//VECTOR GetShieldPosition();			// ���̌��݈ʒu��Ԃ�
	//State GetShieldState();				// ���̏�Ԃ�Ԃ�

private:
	static const VECTOR INITIAL_POSITION;		// �����ʒu
	static const VECTOR INITIAL_DIRECTION;		// ��������
	static const VECTOR INITIAL_SCALE;			// �����T�C�Y
	static const float  SPEED_INCREASE;			// 1�t���[���̑��x������
	static const float  SPEED_DECREASE;			// 1�t���[���̑��x������
	static const float  MAX_NORMAL_SPEED;		// �ʏ펞�ő呬�x
	static const float  MAX_DEFENSE_SPEED;		// �h�䎞�ő呬�x
	static const float  COLLIDE_RADIUS;			// �����蔻�苅���a
	static const float  MAX_HITPOINT;			// �ő�HitPoint
	
	Shield* shield;								// Shield�N���X�̃|�C���^
	Camera* camera;								// Camera�N���X�̃|�C���^

	State state;								// ���
	Sphere collisionSphere;						// �����蔻�苅

	VECTOR inputDirection;						// ���͕���

	float maxSpeed;								// �ő呬�x
	float collideRadius;						// �����蔻�苅���a

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