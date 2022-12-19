#include "Pch.h"
#include "Shield.h"

#include "ModelManager.h"

const float Shield::MAX_HITPOINT = 100.0f;
const float Shield::SCALE_BY_DIRECTION_FOR_CORRECTION = 150.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Shield::Shield()
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Shield::~Shield()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Shield::Initialize()
{
	hitPoint = MAX_HITPOINT;
	// ���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::SHIELD));
}

/// <summary>
/// �I������
/// </summary>
void Shield::Finalize()
{

}

/// <summary>
/// ����������
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
/// <param name="inPrevDirection"></param>
void Shield::Activate(const VECTOR& inPosition,
					  const VECTOR& inDirection, 
					  const VECTOR& inPrevDirection)
{
	state = State::DEPLOYMENT;

	position = inPosition;
	direction = inDirection;
	distanceToPlayer = VScale(inPrevDirection, SCALE_BY_DIRECTION_FOR_CORRECTION);

	MV1SetPosition(modelHandle, position);					// ���f���̈ʒu��ݒ�
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);	// ���̌�����ݒ�

	pUpdate = &Shield::UpdateDeployment;
}

/// <summary>
/// �񊈐�������
/// </summary>
void Shield::Deactivate()
{
	state = State::NONE;
	pUpdate = nullptr;
}

/// <summary>
/// �X�V����
/// </summary>
void Shield::Update()
{
	// ���݂��Ȃ��Ȃ珈�����Ȃ�
	if (state == State::NONE)
	{
		return;
	}

	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();		// ��Ԃ��Ƃ̍X�V����
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Shield::Draw()
{
	// ���݂��Ȃ��Ȃ珈�����Ȃ�
	if (state == State::NONE)
	{
		return;
	}

	// ���f���̕`��
	MV1DrawModel(modelHandle);
}

/// <summary>
/// �ʒu���Z�b�g
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
/// <param name="inPrevDirection"></param>
void Shield::SetShieldPosition(const VECTOR& inPosition, const VECTOR& inDirection, const VECTOR& inPrevDirection)
{
	position = inPosition;
	direction = inDirection;
	distanceToPlayer = VScale(direction, SCALE_BY_DIRECTION_FOR_CORRECTION);
	position = VAdd(position, distanceToPlayer);
}

/// <summary>
/// ���ۂɈړ�����
/// </summary>
void Shield::MoveFinish()
{
	// ���f���̈ʒu��ݒ�
	MV1SetPosition(modelHandle, position);
	// ���f���̌�����ݒ�
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
}

/// <summary>
/// DEPLOYMENT���X�V����
/// </summary>
void Shield::UpdateDeployment()
{
	MoveFinish();
}

/// <summary>
/// DESTRUCTION���X�V����
/// </summary>
void Shield::UpdateDestruction()
{

}
