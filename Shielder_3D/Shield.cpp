#include "Pch.h"
#include "Shield.h"

#include "ModelManager.h"

const float Shield::SCALE_BY_DIRECTION_FOR_CORRECTION = 80.0f;

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
void Shield::Activate(const VECTOR& inPosition, const VECTOR& inDirection, const VECTOR& inPrevDirection)
{
	position = inPosition;
	direction = inDirection;

	MV1SetPosition(modelHandle, position);					// ���f���̈ʒu��ݒ�
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);	// ���̌�����ݒ�
}

/// <summary>
/// �񊈐�������
/// </summary>
void Shield::Deactivate()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
/// <param name="inPrevDirection"></param>
void Shield::Update(const VECTOR& inPosition, const VECTOR& inDirection, const VECTOR& inPrevDirection)
{

}

/// <summary>
/// �`�揈��
/// </summary>
void Shield::Draw()
{
	// ���݂��Ȃ��Ȃ珈�����Ȃ�
	if (state == NONE)
	{
		return;
	}

	// ���f���̕`��
	MV1DrawModel(modelHandle);
}
