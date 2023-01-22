#pragma once

#include "Character.h"

using namespace My3dLib;

class Shield;
class Camera;
class Timer;

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
		PREVENT,	// �h����
		DAMAGE,		// ��e
		DEAD		// ���S
	};

	void Initialize(EffectManager* const inEffectManager);		// ����������
	void Finalize();		// �I������
	void Activate();		// ����������
	void Deactivate();		// �񊈐�������
	void Update();			// �X�V����
	void Draw();			// �`�揈��

	void GameStart();											// �Q�[���J�n���i���o�p�j
	void Releaseinvincible();									// ���G��ԉ���
	void HitOtherCharacter(const VECTOR& forceDirection);		// ���̃L�����N�^�[�ƐڐG����
	void HitShieldOtherCharacter(const VECTOR& forceDirection);	// �V�[���h�����̃L�����N�^�[�ƐڐG����

	const float GetCollideRadius();			// �����蔻�苅���a��Ԃ�
	const float GetHitPoint();				// ���݂�HitPoint��Ԃ�
	const State GetCurrentState();			// ���݂̏�Ԃ�Ԃ�
		  Shield *GetShieldPointer();		// �V�[���h�̃|�C���^��Ԃ�

	//VECTOR GetShieldPosition();			// �V�[���h�̌��݈ʒu��Ԃ�
	//State GetShieldState();				// �V�[���h�̏�Ԃ�Ԃ�

private:
	static const VECTOR INITIAL_POSITION;		// �����ʒu
	static const VECTOR INITIAL_DIRECTION;		// ��������
	static const VECTOR INITIAL_SCALE;			// �����T�C�Y
	static const float  SPEED_INCREASE;			// 1�t���[���̑��x������
	static const float  SPEED_DECREASE;			// 1�t���[���̑��x������
	static const float  MAX_HIT_POINT;			// �ő�HitPoint
	static const float  MAX_NORMAL_SPEED;		// �ʏ펞�ő呬�x
	static const float  MAX_DEFENSE_SPEED;		// �h�䎞�ő呬�x
	static const float  COLLIDE_RADIUS;			// �����蔻�苅���a
	static const float  DECREMENT_HIT_POINT;	// �ڐG����HitPoint������ 
	static const float  FORCE_AT_DAMAGE;		// �ڐG���ɓ�����
	static const float  FORCE_AT_DEFENSE;		// �h�䎞�ɓ�����
	static const float  FRICTIONAL_FORCE;		// ���C��
	
	Shield* shield;								// Shield�N���X�̃|�C���^
	Camera* camera;								// Camera�N���X�̃|�C���^
	EffectManager* effectManager;				// EffectManager�N���X�̃|�C���^
	Timer* timer;								// Timer�N���X�̃|�C���^�i�Ȃ�Ƃ��ł��Ȃ����̂��j

	State  state;								// ���
	Sphere collisionSphere;						// �����蔻�苅


	int    frame;								// �o�߃t���[���i1�b�ȉ��̕`��Ɏg�p�j
	float  maxSpeed;							// �ő呬�x
	int mousePosX;
	int mousePosY;
	VECTOR mousePosition;						// �}�E�X�|�C���^�̈ʒu
	VECTOR screenPosition;						// �v���C���[�̉�ʍ��W
	VECTOR inputDirection;						// ���͕���
	VECTOR moveForce;							// �i�����Ƃ����
	VECTOR force;								// 

	void (Player::* pUpdate)();					// Update�֐��|�C���^

	// �eState���Ƃ̍X�V����
	void UpdateNomal();							// NORMAL���X�V����
	void UpdateDefense();						// DEFENSE���X�V����
	void UpdatePrevent();						// PREVENT���X�V����
	void UpdateDamage();						// DAMAGE���X�V����
	void UpdateDead();							// DEAD���X�V����

	// �펞�쓮���鏈��
	//void UpdateAlways();

	void Move();								// �ړ�����
	///void MoveFinish();						// �ړ��\��n�Ɏ��ۂɈړ�����
	void InputAction();							// ���͏���
	void ChangeSpeed(float afterSpeed);			// �ړ����x��ύX����
	void ActivateShield();						// �V�[���h��W�J����
	void DeactivateShield();					// �V�[���h�����ł�����
	void DecrementHitPoint();					// HitPoint������������i�x��Č�������̂�UI�̂ق��ŏ����j
	void InvincibleUpdate();					// ���G��ԏ���
	bool DamageBouncePlayer();					// �v���C���[�𒵂˕Ԃ��i�_���[�W�j
	bool DefenseBouncePlayer();					// �v���C���[�𒵂˕Ԃ��i�f�B�t�F���X�j
};