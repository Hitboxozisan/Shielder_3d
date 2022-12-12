#include "Pch.h"
#include "Shield.h"

#include "ModelManager.h"

const float Shield::SCALE_BY_DIRECTION_FOR_CORRECTION = 80.0f;

/// <summary>
/// コンストラクタ
/// </summary>
Shield::Shield()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Shield::~Shield()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Shield::Initialize()
{
	// モデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::SHIELD));
}

/// <summary>
/// 終了処理
/// </summary>
void Shield::Finalize()
{
}

/// <summary>
/// 活性化処理
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
/// <param name="inPrevDirection"></param>
void Shield::Activate(const VECTOR& inPosition, const VECTOR& inDirection, const VECTOR& inPrevDirection)
{
	position = inPosition;
	direction = inDirection;

	MV1SetPosition(modelHandle, position);					// モデルの位置を設定
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);	// 盾の向きを設定
}

/// <summary>
/// 非活性化処理
/// </summary>
void Shield::Deactivate()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
/// <param name="inPrevDirection"></param>
void Shield::Update(const VECTOR& inPosition, const VECTOR& inDirection, const VECTOR& inPrevDirection)
{

}

/// <summary>
/// 描画処理
/// </summary>
void Shield::Draw()
{
	// 存在しないなら処理しない
	if (state == NONE)
	{
		return;
	}

	// モデルの描画
	MV1DrawModel(modelHandle);
}
