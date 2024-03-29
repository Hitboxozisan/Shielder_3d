#include "Pch.h"
#include "GuardEffect.h"

GuardEffect::GuardEffect()
{
}

GuardEffect::~GuardEffect()
{
}

void GuardEffect::Initialize()
{
	effectHandle = LoadEffekseerEffect("Data/Effect/Blow.efkefc", 20.0f);
	if (effectHandle == -1)
	{
		printfDx("読み込みに失敗_GuardEffect");
	}
	
}

void GuardEffect::Finalize()
{
	//エフェクトを削除する
	DeleteEffekseerEffect(effectHandle);
}

void GuardEffect::Activate(VECTOR inPosition)
{
	exist = true;
	frame = 0;
	position = inPosition;
	//position = VGet(320.0f, 300.0f, 100.0f);
	position.y = 50.0f;
	playingEffectHandle = -1;
}

void GuardEffect::Deactivate()
{
	exist = false;
}

void GuardEffect::Update(VECTOR inPostion, VECTOR inEnemyPosition)
{
	//存在しないなら処理しない
	if (exist == false)
	{
		return;
	}

	frame++;

	if (frame <= 1)
	{
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);					// エフェクトを再生する
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 1.5f, 1.5f, 1.5f);	// エフェクトの拡大率を設定
		SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, 1.5f);
	}

	//エフェクトを再生し終わったら
	if (frame >= 60)
	{
		Deactivate();
	}

	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);
}


void GuardEffect::Draw()
{
	if (exist == false)
	{
		return;
	}

	UpdateEffekseer3D();
	DrawEffekseer3D();
}
	