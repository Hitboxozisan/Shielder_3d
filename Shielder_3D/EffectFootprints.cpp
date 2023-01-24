#include "Pch.h"

#include "DeltaTime.h"
#include "EffectFootprints.h"

const int	EffectFootprints::DEFAULT_EXIST_FRAME = 60;
const float EffectFootprints::INCREASE_SIZE = 0.8f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectFootprints::EffectFootprints()
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectFootprints::~EffectFootprints()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inSize"></param>
void EffectFootprints::Activate(const VECTOR& inPosition, float inSize)
{
	position = inPosition;		// �����ʒu��ݒ�
	position.y = 0.0f;			// �n�ʂ���G�t�F�N�g���o��

	size = inSize;

	exist = true;
	existFrame = DEFAULT_EXIST_FRAME;

	opacity = 255.0f;
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="inPosition"></param>
void EffectFootprints::Draw(const VECTOR& inPosition)
{
	//���݂��Ȃ��Ȃ珈�����Ȃ�
	if (exist == false)
	{
		return;
	}

	// alpha�l���������Ui���������邭�Ȃ邽�ߕs�g�p

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, opacity);
	DrawBillboard3D(position, 0.5f, 0.5f, size, 0.0f, *graphicPointer, TRUE);		//�摜�̕`��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// �X�V����
/// </summary>
void EffectFootprints::UpdateEach()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	// ���X�ɓ����ɂ���
	opacity -= deltaTime;
}
