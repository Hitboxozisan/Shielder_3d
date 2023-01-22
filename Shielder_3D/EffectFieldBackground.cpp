#include "Pch.h"

#include "EffectFieldBackground.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectFieldBackground::EffectFieldBackground()
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectFieldBackground::~EffectFieldBackground()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void EffectFieldBackground::Initialize()
{
	// �G�t�F�N�g�ǂݍ���
	effectHandle = LoadEffekseerEffect("Data/Effect/FieldBackground.efkefc", 35.0f);
	// �G���[����
	if (effectHandle == -1)
	{
		printfDx("�ǂݍ��݂Ɏ��s_FieldBackground\n");
	}
}

/// <summary>
/// �I������
/// </summary>
void EffectFieldBackground::Finalize()
{
	// �G�t�F�N�g���폜����
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// ����������
/// </summary>
/// <param name="inPosition">�����ʒu</param>
void EffectFieldBackground::Activate(VECTOR inPosition)
{
	exist = true;
	frame = 0;
	position = inPosition;
	//position = VGet(320.0f, 300.0f, 100.0f);
	playingEffectHandle = -1;
}

/// <summary>
/// �񊈐�������
/// </summary>
void EffectFieldBackground::Deactivate()
{
	exist = false;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="inPostion">�v���C���[�̈ʒu</param>
/// <param name="inEnemyPosition">�G�l�~�[�̈ʒu</param>
void EffectFieldBackground::Update(VECTOR inPostion, VECTOR inEnemyPosition)
{
	//���݂��Ȃ��Ȃ珈�����Ȃ�
	if (exist == false)
	{
		return;
	}

	frame++;

	if (frame <= 1)
	{
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);			//�G�t�F�N�g���Đ�����
	}

	//�G�t�F�N�g���Đ����I�������
	if (frame >= 240)
	{
		frame = 0;
	}

	//�Đ��ʒu��ݒ�
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, 0.0f, 0.0f, 0.0f);
}

/// <summary>
/// �`�揈��
/// </summary>
void EffectFieldBackground::Draw()
{
	if (exist == false)
	{
		return;
	}

	UpdateEffekseer3D();
	DrawEffekseer3D();
}
