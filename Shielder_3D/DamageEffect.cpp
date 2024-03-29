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
		printfDx("読み込みに失敗_DamageEffect");
	}
}

void DamageEffect::Finalize()
{
	//エフェクトを削除する
	DeleteEffekseerEffect(effectHandle);
}

void DamageEffect::Activate(VECTOR inPosition)
{
	exist = true;
	frame = 0;
	position = inPosition;
	position.y = 50.0f;
	playingEffectHandle = -1;
}

void DamageEffect::Deactivate()
{
	exist = false;
}

void DamageEffect::Update(VECTOR inPostion, VECTOR inEnemyPosition)
{
	//存在しないなら処理しない
	if (exist == false)
	{
		return;
	}

	frame++;

	if (frame <= 1)
	{
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);			//エフェクトを再生する
	}

	//エフェクトを再生し終わったら
	if (frame >= 60)
	{
		Deactivate();
	}

	//再生位置を設定
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
