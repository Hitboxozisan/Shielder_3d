#include "Pch.h"

#include "EffectFieldBackground.h"

/// <summary>
/// コンストラクタ
/// </summary>
EffectFieldBackground::EffectFieldBackground()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
EffectFieldBackground::~EffectFieldBackground()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void EffectFieldBackground::Initialize()
{
	// エフェクト読み込み
	effectHandle = LoadEffekseerEffect("Data/Effect/FieldBackground.efkefc", 35.0f);
	// エラー処理
	if (effectHandle == -1)
	{
		printfDx("読み込みに失敗_FieldBackground\n");
	}
}

/// <summary>
/// 終了処理
/// </summary>
void EffectFieldBackground::Finalize()
{
	// エフェクトを削除する
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// 活性化処理
/// </summary>
/// <param name="inPosition">発生位置</param>
void EffectFieldBackground::Activate(VECTOR inPosition)
{
	exist = true;
	frame = 0;
	position = inPosition;
	//position = VGet(320.0f, 300.0f, 100.0f);
	playingEffectHandle = -1;
}

/// <summary>
/// 非活性化処理
/// </summary>
void EffectFieldBackground::Deactivate()
{
	exist = false;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="inPostion">プレイヤーの位置</param>
/// <param name="inEnemyPosition">エネミーの位置</param>
void EffectFieldBackground::Update(VECTOR inPostion, VECTOR inEnemyPosition)
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
	if (frame >= 240)
	{
		frame = 0;
	}

	//再生位置を設定
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, 0.0f, 0.0f, 0.0f);
}

/// <summary>
/// 描画処理
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
