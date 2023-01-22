#include "Pch.h"
#include "Field.h"

#include "ModelManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Field::Field()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Field::~Field()
{
}

/// <summary>
/// ����������
/// </summary>
void Field::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::FIELD));
	MV1SetScale(modelHandle, VGet(1.5f, 1.0f, 1.5f));														//���f���̃T�C�Y�ύX

	position = VGet(0.0f, -80.0f, 0.0f);
	MV1SetPosition(modelHandle, position);
	//MV1SetRotationXYZ(modelHandle, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
}

/// <summary>
/// �`�揈��
/// </summary>
void Field::Draw()
{
	MV1DrawModel(modelHandle);
}
