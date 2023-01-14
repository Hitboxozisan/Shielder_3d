#include "Pch.h"

#include "EffectTeleport.h"

/// <summary>
/// コンストラクタ
/// </summary>
EffectTeleport::EffectTeleport()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
EffectTeleport::~EffectTeleport()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void EffectTeleport::Initialize()
{
	// エフェクト読み込み
	effectHandle = LoadEffekseerEffect("Data/Effect/teleport.efkefc", 20.0f);
	// エラー処理
	if (effectHandle == -1)
	{
		printfDx("読み込みに失敗_teleportEffect\n");
	}
}

/// <summary>
/// 終了処理
/// </summary>
void EffectTeleport::Finalize()
{
	//エフェクトを削除する
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// 活性化処理
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
/// 非活性化処理
/// </summary>
void EffectTeleport::Deactivate()
{
	exist = false;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="inPostion">発生位置</param>
/// <param name="inEnemyPosition">敵の位置</param>
void EffectTeleport::Update(VECTOR inPostion, VECTOR inEnemyPosition)
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

/// <summary>
/// 描画処理
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
