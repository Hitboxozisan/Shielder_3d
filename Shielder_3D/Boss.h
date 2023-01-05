//----------------------------------------------------------------
// <�s��E�o�O>
// �E
// <note>
// �EUpdate�֐���State���Ƃɔz��ŊǗ������ق����y���H�i���������ł���̂��j
//----------------------------------------------------------------
#pragma once

#include "Mover.h"

using namespace My3dLib;

class Timer;
class Player;

class Boss : public Mover
{
public:
	Boss(Player* inPlayer);
	~Boss();

	enum class State
	{
		NONE,		// ���݂��Ȃ�
		ATTACK,		// �U��
		SLIDE,		// ���˕Ԃ�
		DEAD		// ���S
	};

	enum class AttackState
	{
		ASSAULT = 0,	// �ːi�U��
		//BULLET,			// �ʏ�e����
		//SLOW_BULLET,	// �x���e����
		JUMP,			// �W�����v
		//KICK,			// �L�b�N
		//JUDGE,			// �ǂ��ɂ��邩���f
		//BACK,			// ��ʒ[�ɖ߂�
		THINKING,		// �s���v�l�E����

		ATTACK_AMOUST	// �s���p�^�[����
	};

	void Initialize();		// ����������
	void Fainalize();		// �I������
	void Activate();		// ����������
	void Deactivate();		// �񊈐�������
	void Update();			// �X�V����
	void Draw();			// �`�揈��

	void MoveFinish();		// �ړ��\��n�Ɏ��ۂɈړ�����

	void HitOtherCharacter(const VECTOR& forceDirection);	// ���̃L�����N�^�[�ɐڐG����
	void HitShield(const VECTOR& forceDirection);			// �V�[���h�ɐڐG����

	const float GetCollideRadius();		// �����蔻�苅���a��Ԃ�
private:
	static const VECTOR INITIAL_POSITION;		// �����ʒu
	static const VECTOR INITIAL_DIRECTION;		// ��������
	static const VECTOR INITIAL_SCALE;			// �����T�C�Y
	static const VECTOR JUMP_FORCE;				// �W�����v��
	static const float  FRICTIONAL_FORCE;		// ���C��
	static const float  GRAVITY;				// �d��
	static const float  FORCE_AT_HIT_SHIELD;	// ���ƐڐG���̗�
	static const float  COLLIDE_RADIUS;			// �����蔻�苅���a
	static const float  VIBRATE_TIME;			// �U�����鎞��
	static const float  ASSAULT_SPEED;			// �ːi���x
	static const float  ASSAULT_DISTANCE;		// �ːi���鋗��
	static const int    ASSAULT_TIME;			// �ːi��

	int	   assaultTime;					// �ːi��
	float  vibrateTime;					// �U������
	VECTOR startAssaultPosition;		// �ːi�J�n�ʒu
	VECTOR force;						// �����́i���˕Ԃ�Ƃ��Ɏ�Ɏg�p�j
	VECTOR jumpForce;					// �W�����v��

	Player* player;						// Player�N���X�̃|�C���^
	Timer* timer;						// Timer�N���X�̃|�C���^

	State state;						// ���
	AttackState attackState;			// �U���p�^�[��
	AttackState prevAttackState;		// �O��̍U���p�^�[��
	Sphere collisionSphere;				// �����蔻�苅


	void (Boss::* pUpdate)();			// Update�֐��|�C���^
	void (Boss::* pUpdateAttack)();		// UpdateAttack�֐��|�C���^

	// AttackState�ɍ��킹�čX�V������ύX����
	// ����͈ꎞ�I�Ȃ���
	void SetNextAttackUpdate();

	// ����State�����肷��i�f�o�b�O�p�j
	void SetNextAttackState();

	// �eState���Ƃ̍X�V����
	void UpdateAttack();
	void UpdateSlide();

	// �eAttackState���Ƃ̍X�V����
	void UpdateAssault();
	void UpdateJump();
	void UpdateThinking();

	void ChangeStateInitialize();		// ��ԕω����̏�����
	void ResetPositionYaw();			// Y���W��0.0f�̈ʒu�ɖ߂�
	void FaceToPlayer();				// �v���C���[�̂ق�������
	void AssaultToPlayer();				// �v���C���[�Ɍ������ēːi����
	bool Jump();						// �W�����v����
	bool Vibrate();						// �U������
	bool Slide();						// �h�䂳�ꂽ�Ƃ��̔���
};

