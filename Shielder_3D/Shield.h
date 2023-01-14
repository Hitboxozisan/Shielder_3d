#pragma once

#include "ObjectBase.h"
#include "EffectManager.h"

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

	void HitOtherCharacter();								// ���̃L�����N�^�[�ƐڐG����
	void DecrementHitPoint();								// �ϋv�l������������

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
	static const float  MAX_HITPOINT;							// �ő�ϋv�l
	static const float  SCALE_BY_DIRECTION_FOR_CORRECTION;		// �v���C���[�Ƃ̋���
	static const float  JUST_DEFENSE_TIME;						// "�W���X�g�K�[�h"�Ɣ��f���鎞��
	static const float  COLLIDE_RADIUS;							// �����蔻�苅���a
	static const float  COLLIDE_HEIGHT;							// �����蔻�苅����

	EffectManager* effectManager;	// EffectManager�N���X�̃|�C���^

	State state;
	Sphere collisionSphere;			// �{���Ȃ狅�̂��g���ׂ��ł͂Ȃ���
									// �[�ɍU���������邱�Ƃ͏��Ȃ����ߊy������

	void (Shield::* pUpdate)();		// Update�֐��|�C���^

	float hitPoint;					// �V�[���h�̑ϋv�l
	float elapsedtTime;				// �V�[���h��W�J���Ă���̌o�ߎ���
	VECTOR distanceToPlayer;		// �v���C���[�Ƃ̋���

	void MoveFinish();				// ���ۂɈړ�����

	void UpdateDeployment();		// DEPLOYMENT���X�V����
	void UpdateDestruction();		// DESTRUCTION���X�V����

};

