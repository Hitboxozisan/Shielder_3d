#include "Pch.h"

#include "EffectTeleport.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectTeleport::EffectTeleport()
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectTeleport::~EffectTeleport()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void EffectTeleport::Initialize()
{
	// �G�t�F�N�g�ǂݍ���
	effectHandle = LoadEffekseerEffect("Data/Effect/teleport.efkefc", 20.0f);
	// �G���[����
	if (effectHandle == -1)
	{
		printfDx("�ǂݍ��݂Ɏ��s_teleportEffect\n");
	}
}

/// <summary>
/// �I������
/// </summary>
void EffectTeleport::Finalize()
{
	//�G�t�F�N�g���폜����
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// ����������
/// </summary>
/// <param name="inPosition"></param>
void EffectTeleport::Activate(VECTOR inPosition)
{
	exist = true;
	frame = 0;
	position = inPosition;
	//position = VGet(320.0f, 300.0f, 100.0f);
	position.y = 50.0f;
	playingEffectHandle = -1;
}

/// <summary>
/// �񊈐�������
/// </summary>
void EffectTeleport::Deactivate()
{
	exist = false;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="inPostion">�����ʒu</param>
/// <param name="inEnemyPosition">�G�̈ʒu</param>
void EffectTeleport::Update(VECTOR inPostion, VECTOR inEnemyPosition)
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
	if (frame >= 60)
	{
		Deactivate();
	}

	//�Đ��ʒu��ݒ�
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);
}

/// <summary>
/// �`�揈��
/// </summary>
void EffectTeleport::Draw()
{
	if (exist == false)
	{
		return;
	}

	UpdateEffekseer3D();
	DrawEffekseer3D();
}
