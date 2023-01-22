#pragma once

#include "ObjectBase.h"
#include "EffectManager.h"

class Timer;

using namespace My3dLib;

class Shield final : public ObjectBase
{
public:
	Shield();
	~Shield();

	// ���
	enum class State
	{
		NONE,			// ���݂��Ȃ�
		COOL_TIME,		// ���Œ�
		DEPLOYMENT,		// �W�J��
		DESTRUCTION		// �j��
	};

	void Initialize(EffectManager* inEffectManager);									// ����������
	void Finalize();									// �I������
	void Activate(const VECTOR& inPosition,
				  const VECTOR& inDirection,
				  const VECTOR& inPrevDirection);		// ����������
	void Deactivate();									// �񊈐�������
	void Update();										// �X�V����
	void Draw();										// �`�揈��

	// �����蔻��֌W
	// ����������Ă���Ƃ�����Y��ɂ�����
	void HitOtherCharacter(float magnification);		// ���̃L�����N�^�[�ƐڐG����
	void HitBullet(float magnification);				// �G�����˂����e�ƐڐG����

	// �Z�b�^�[�E�Q�b�^�[
	void SetShieldPosition(const VECTOR& inPosition,
						   const VECTOR& inDirection,
						   const VECTOR& inPrevDirection);	// �V�[���h�̈ʒu��ݒ�
	const float GetCollideRadius();							// �����蔻�苅���a��Ԃ�
	const bool isJust();									// "�W���X�g�K�[�h"���ǂ���
	State GetState() const { return state; }				// ���݂̏�Ԃ�Ԃ�
	

private:
	Shield(const Shield&);			// �R�s�[�R���X�g���N�^
	void operator=(const Shield&);	// ������Z�q
	
	static const VECTOR INITIAL_SCALE;							// �����T�C�Y
	static const float  MAX_TRUNK_POINT;						// �ő�ϋv�l
	static const float  SCALE_BY_DIRECTION_FOR_CORRECTION;		// �v���C���[�Ƃ̋���
	static const float  JUST_DEFENSE_TIME;						// "�W���X�g�K�[�h"�Ɣ��f���鎞��
	static const float  COLLIDE_RADIUS;							// �����蔻�苅���a
	static const float  COLLIDE_HEIGHT;							// �����蔻�苅����
	static const float  INCREMENT_TRUNK_POINT;					// �ڐG���ɑ�������ϋv�l��
	static const float  DECREMENT_TRUNK_POINT;					// �ϋv�l�̌�����

	EffectManager* effectManager;	// EffectManager�N���X�̃|�C���^
	Timer* timer;					// Timer�N���X�̃|�C���^

	State state;
	Sphere collisionSphere;			// �{���Ȃ狅�̂��g���ׂ��ł͂Ȃ���
									// �[�ɍU���������邱�Ƃ͏��Ȃ����ߊy������

	void (Shield::* pUpdate)();		// Update�֐��|�C���^

	float trunkPoint;				// �V�[���h�̑ϋv�l
	float elapsedtTime;				// �V�[���h��W�J���Ă���̌o�ߎ���
	VECTOR distanceToPlayer;		// �v���C���[�Ƃ̋���

	void MoveFinish();				// ���ۂɈړ�����

	void UpdateCoolTime();			// COOLTIME���X�V����
	void UpdateDeployment();		// DEPLOYMENT���X�V����
	void UpdateDestruction();		// DESTRUCTION���X�V����

	bool IncrementTrunkPoint(float magnification);		// �V�[���h�̑ϋv�l�𑝉�������
	bool DecrementTrunkPoint();							// �V�[���h�̑ϋv�l������������

};

