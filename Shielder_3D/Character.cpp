#include "Pch.h"
#include "Character.h"
#include "EffectManager.h"

using namespace Math3d;

/// <summary>
/// コンストラクタ
/// </summary>
Character::Character()
	:isAlive(true)
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Character::~Character()
{
	// 処理なし
}

/// <summary>
/// 移動予定地に実際に移動する
/// </summary>
void Character::MoveFinish()
{
	// 移動しているなら前フレームの向きを更新する
	if (direction != ZERO_VECTOR)
	{
		prevDirection = direction;
	}

	prevPosition = position;
	position  = nextPosition;
	direction = nextDirection;

	// モデルの位置を設定
	MV1SetPosition(modelHandle, position);
	// モデルの向きを設定
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
}

/// <summary>
/// 生きているかを返す
/// </summary>
/// <returns>生死状態</returns>
bool Character::IsAlive()
{
	return isAlive;
}
