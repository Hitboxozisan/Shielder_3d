#include "Pch.h"

#include "Sword.h"
#include "ModelManager.h"
#include "DeltaTime.h"

const VECTOR Sword::INITIAL_POSITION				 = VGet(0.0f, 0.0f, 0.0f);
const VECTOR Sword::INITIAL_DIRECTION				 = VGet(1.0f, 0.0f, 0.0f);
const VECTOR Sword::INITIAL_SCALE					 = VGet(1.0f, 1.0f, 1.0f);
const float Sword::SCALE_BY_DIRECTION_FOR_CORRECTION = 50.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <returns></returns>
Sword::Sword()
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Sword::~Sword()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Sword::Initialize()
{
	// ���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::SWORD));
	// ���f���̊g�嗦�ݒ�
	MV1SetScale(modelHandle, INITIAL_SCALE);
}

/// <summary>
/// �I������
/// </summary>
void Sword::Finalize()
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
void Sword::Activate(const VECTOR& inPosition, const VECTOR& inDirection)
{
	position = INITIAL_POSITION;
	nextPosition = position;
	prevPosition = position;
	direction = INITIAL_DIRECTION;
	nextDirection = direction;
	prevDirection = direction;
	prevDirection = direction;

	// ��Ԃ� NONE ��
	state = State::NONE;

	// ���f���������ʒu�ɔz�u
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// �񊈐�������
/// </summary>
void Sword::Deactivate()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <returns></returns>
void Sword::Update()
{
	// ���݂��Ȃ��Ȃ珈�����Ȃ�
	if (state == State::NONE)
	{
		return;
	}

	rollSword();
	MoveFinish();
}

/// <summary>
/// �`�揈��
/// </summary>
void Sword::Draw()
{
	// ���݂��Ȃ��Ȃ�`�悵�Ȃ�
	if (state == State::NONE)
	{
		return;
	}

	// ���f���̕`��
	MV1DrawModel(modelHandle);
}

/// <summary>
/// ���𑶍݂�����
/// </summary>
void Sword::activateSword(const VECTOR& inPosition, const VECTOR& inDirection)
{
	// �I�u�W�F�N�g�̑O�ɔz�u����
	SetToFrontOfObject(inPosition, inDirection);
	state = State::ACTIVE;
}

/// <summary>
/// ����U��
/// </summary>
void Sword::rollSword()
{

}

/// <summary>
/// �I�u�W�F�N�g�̑O�ɔz�u����
/// </summary>
/// <param name="inPosition">�I�u�W�F�N�g�̈ʒu</param>
/// <param name="inDirection">�I�u�W�F�N�g�̌���</param>
void Sword::SetToFrontOfObject(const VECTOR& inPosition, const VECTOR& inDirection)
{
	position = inPosition;
	direction = inDirection;

	//�G�l�~�[�̑O���Ɉʒu����
	VECTOR distanceToPlayer = VScale(direction, SCALE_BY_DIRECTION_FOR_CORRECTION);

	nextPosition = VAdd(nextPosition, distanceToPlayer);
}

void Sword::MoveFinish()
{
	prevPosition = position;
	position = nextPosition;
	direction = nextDirection;

	// ���f���̈ʒu��ݒ�
	MV1SetPosition(modelHandle, position);

	// ���f���̌�����ݒ�
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
}
