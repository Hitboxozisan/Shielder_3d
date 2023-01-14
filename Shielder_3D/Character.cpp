#include "Pch.h"
#include "Character.h"
#include "EffectManager.h"

using namespace Math3d;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Character::Character()
	:isAlive(true)
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Character::~Character()
{
	// �����Ȃ�
}

/// <summary>
/// �ړ��\��n�Ɏ��ۂɈړ�����
/// </summary>
void Character::MoveFinish()
{
	// �ړ����Ă���Ȃ�O�t���[���̌������X�V����
	if (direction != ZERO_VECTOR)
	{
		prevDirection = direction;
	}

	prevPosition = position;
	position  = nextPosition;
	direction = nextDirection;

	// ���f���̈ʒu��ݒ�
	MV1SetPosition(modelHandle, position);
	// ���f���̌�����ݒ�
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
}

/// <summary>
/// �����Ă��邩��Ԃ�
/// </summary>
/// <returns>�������</returns>
bool Character::IsAlive()
{
	return isAlive;
}
