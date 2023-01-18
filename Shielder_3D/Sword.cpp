#include "Pch.h"

#include "Sword.h"
#include "ModelManager.h"
#include "DeltaTime.h"

const VECTOR Sword::INITIAL_POSITION				 = VGet(0.0f, 0.0f, 0.0f);
const VECTOR Sword::INITIAL_DIRECTION				 = VGet(1.0f, 0.0f, 0.0f);
const VECTOR Sword::INITIAL_SCALE					 = VGet(1.0f, 1.0f, 1.0f);
const float Sword::SCALE_BY_DIRECTION_FOR_CORRECTION = 50.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <returns></returns>
Sword::Sword()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Sword::~Sword()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Sword::Initialize()
{
	// モデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::SWORD));
	// モデルの拡大率設定
	MV1SetScale(modelHandle, INITIAL_SCALE);
}

/// <summary>
/// 終了処理
/// </summary>
void Sword::Finalize()
{
}

/// <summary>
/// 活性化処理
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
void Sword::Activate(const VECTOR& inPosition, const VECTOR& inDirection)
{
	position = INITIAL_POSITION;
	nextPosition = position;
	prevPosition = position;
	direction = INITIAL_DIRECTION;
	nextDirection = direction;
	prevDirection = direction;
	prevDirection = direction;

	// 状態を NONE に
	state = State::NONE;

	// モデルを初期位置に配置
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 非活性化処理
/// </summary>
void Sword::Deactivate()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <returns></returns>
void Sword::Update()
{
	// 存在しないなら処理しない
	if (state == State::NONE)
	{
		return;
	}

	rollSword();
	MoveFinish();
}

/// <summary>
/// 描画処理
/// </summary>
void Sword::Draw()
{
	// 存在しないなら描画しない
	if (state == State::NONE)
	{
		return;
	}

	// モデルの描画
	MV1DrawModel(modelHandle);
}

/// <summary>
/// 剣を存在させる
/// </summary>
void Sword::activateSword(const VECTOR& inPosition, const VECTOR& inDirection)
{
	// オブジェクトの前に配置する
	SetToFrontOfObject(inPosition, inDirection);
	state = State::ACTIVE;
}

/// <summary>
/// 剣を振る
/// </summary>
void Sword::rollSword()
{

}

/// <summary>
/// オブジェクトの前に配置する
/// </summary>
/// <param name="inPosition">オブジェクトの位置</param>
/// <param name="inDirection">オブジェクトの向き</param>
void Sword::SetToFrontOfObject(const VECTOR& inPosition, const VECTOR& inDirection)
{
	position = inPosition;
	direction = inDirection;

	//エネミーの前方に位置調整
	VECTOR distanceToPlayer = VScale(direction, SCALE_BY_DIRECTION_FOR_CORRECTION);

	nextPosition = VAdd(nextPosition, distanceToPlayer);
}

void Sword::MoveFinish()
{
	prevPosition = position;
	position = nextPosition;
	direction = nextDirection;

	// モデルの位置を設定
	MV1SetPosition(modelHandle, position);

	// モデルの向きを設定
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
}
