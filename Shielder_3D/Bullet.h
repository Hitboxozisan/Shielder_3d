#pragma once

#include "Mover.h"

class Bullet final : public Mover
{
public:
	// �e�̏��
	enum class State
	{
		NONE,			// ���݂��Ȃ�
		NORMAL,			// �؋�
		SHOOT			// ����
	};

	Bullet();
	~Bullet();

	void Initialize();							// ����������
	void Finalize();							// �I������
	void Activate(const VECTOR& inPosition, 
				  const VECTOR& inDirection);	// ����������
	void Deactivate();							// �񊈐�������
	bool Update();								// �X�V����
	void Draw();								// �`�揈��

	void Shoot();								// ���ˏ���

	// �G�l�~�[�̑O�ɐݒu����
	void SetToFrontOfEnemy(const VECTOR& inPosition, const VECTOR& inDirection);
	void RotationAboutObject(Mover* bullet, VECTOR objPos,int totalBullet);	// �I�u�W�F�N�g�𒆐S�ɉ�]

	State GetState() const;						// ���݂̏�Ԃ�Ԃ�
	bool IsCollidableState() const;				// �����蔻�肪�����Ԃ�

	const float GetCollisionRadius() const;

	void OnOutField();							// �t�B�[���h�O�ɏo��
	void OnHitBreak();							// �����ɓ������ĉ���
	
private:
	//�萔
	static const VECTOR INITIAL_SCALE;						// �����T�C�Y
	static const float  NORMAL_SPEED;						// �ʏ틅�ړ����x
	static const float  SLOW_SPEED;							// �x���e�ړ����x
	static const float  SCALE_BY_DIRECTION_FOR_CORRECTION;	// �ʒu�␳�p�Ɍ����x�N�g���Ɋ|����{��
	static const float  NORMAL_FORWARD_DISTANCE;			// �؋󎞂̃I�u�W�F�N�g�Ƃ̋���
	static const float  COLLIDE_RADIUS;			   			// �����蔻�苅���a

	State state;		// ���݂̏��
	float speed;		// ���݂̑��x
	VECTOR velocity;	// ���݂̑��x�A�����x�A���������A�}�C�i�X�ɂ��Ȃ�

	My3dLib::Sphere collisionSphere;		// �����蔻��p��

	void SetShootDirection();	// ���f���̌����� SHOOT �p�ɐݒ�
	void ResetDirection();		// ���f���̌����� NORMAL ���ɖ߂�
	void Move();				// �ړ�����
	void MoveFinish();			// �ړ��\��n�Ɏ��ۂɈړ�����
	
};

