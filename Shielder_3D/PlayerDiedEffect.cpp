#include "Pch.h"
#include "PlayerDiedEffect.h"

PlayerDiedEffect::PlayerDiedEffect()
{
}

PlayerDiedEffect::~PlayerDiedEffect()
{
}

void PlayerDiedEffect::Initialize()
{
	//エフェクトの読み込み
	effectHandle = LoadEffekseerEffect("Data/Effect/playerDied.efkefc", 10.0f);
	if (effectHandle == -1)
	{
		printfDx("読み込みに失敗_playerDiedEffect");
	}
}

void PlayerDiedEffect::Finalize()
{
	//エフェクトを削除する
	DeleteEffekseerEffect(effectHandle);
}

void PlayerDiedEffect::Activate(VECTOR inPosition)
{
	exist = true;
	frame = 0;
	position = inPosition;
	//position = VGet(320.0f, 300.0f, 100.0f);
	position.y = inPosition.y + 25.0f;
	playingEffectHandle = -1;
	
}

void PlayerDiedEffect::Deactivate()
{
	exist = false;
}

void PlayerDiedEffect::Update(VECTOR inPostion, VECTOR inEnemyPosition)
{
	//存在しないなら処理しない
	if (exist == false)
	{
		return;
	}

	frame++;

	if (frame <= 1)
	{
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);				// エフェクトを再生する
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 2.0f, 2.0f, 2.0f);// エフェクトサイズを再生する
	}

	//エフェクトを再生し終わったら
	if (frame >= 60)
	{
		Deactivate();
	}

	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);
}

void PlayerDiedEffect::Draw()
{
	if (exist == false)
	{
		return;
	}

	UpdateEffekseer3D();
	DrawEffekseer3D();
}
