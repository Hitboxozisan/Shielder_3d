#pragma once

#include "Mover.h"

using namespace My3dLib;

class Boss : public Mover
{
public:
	Boss();
	~Boss();

	enum class State
	{
		NONE,		// ���݂��Ȃ�
		ATTACK,		// �U��
		DEAD		// ���S
	};

	enum class AttackState
	{

	};

	void Initialize();		// ����������
	void Fainalize();		// �I������
	void Activate();		// ����������
	void Deactivate();		// �񊈐�������
	void Update();			// �X�V����
	void Draw();			// �`�揈��

	void MoveFinish();		// �ړ��\��n�Ɏ��ۂɈړ�����
private:
	static const VECTOR INITIAL_POSITION;		// �����ʒu
	static const VECTOR INITIAL_DIRECTION;		// ��������
	static const VECTOR INITIAL_SCALE;			// �����T�C�Y
	static const float  COLLIDE_RADIUS;			// �����蔻�苅���a

	State state;						// ���
	Sphere collisionSphere;				// �����蔻�苅

	float collideRadius;				// �����蔻�蔼�a

	void (Boss::* pUpdate)();			// Update�֐��|�C���^

	// �eState���Ƃ̍X�V����
	void UpdateAttack();
};

