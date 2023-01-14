#include "Pch.h"

#include "DamageEffect.h"

DamageEffect::DamageEffect()
{
}

DamageEffect::~DamageEffect()
{
}

void DamageEffect::Initialize()
{
	effectHandle = LoadEffekseerEffect("Data/Effect/damage.efkefc", 15.0f);
	if (effectHandle == -1)
	{
		printfDx("�ǂݍ��݂Ɏ��s_DamageEffect");
	}
}

void DamageEffect::Finalize()
{
	//�G�t�F�N�g���폜����
	DeleteEffekseerEffect(effectHandle);
}

void DamageEffect::Activate(VECTOR inPosition)
{
	exist = true;
	frame = 0;
	position = inPosition;
	//position = VGet(320.0f, 300.0f, 100.0f);
	position.y = 50.0f;
	position.z = 0.0f;
	playingEffectHandle = -1;
}

void DamageEffect::Deactivate()
{
	exist = false;
}

void DamageEffect::Update(VECTOR inPostion, VECTOR inEnemyPosition)
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

void DamageEffect::Draw()
{
	if (exist == false)
	{
		return;
	}

	UpdateEffekseer3D();
	DrawEffekseer3D();
}