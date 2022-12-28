#include "Pch.h"
#include "Boss.h"
#include "ModelManager.h"

using namespace My3dLib;

const VECTOR Boss::INITIAL_POSITION  = VGet(500.0f, 0.0f, 500.0f);
const VECTOR Boss::INITIAL_DIRECTION = VGet(0.0f, 0.0f, -1.0f);
const VECTOR Boss::INITIAL_SCALE     = VGet(0.5f, 0.5f, 0.5f);
const float  Boss::COLLIDE_RADIUS    = 200.0f;

/// <summary>
/// コンストラクタ
/// </summary>
Boss::Boss()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Boss::~Boss()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Boss::Initialize()
{
	// モデルの読み込み
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY);
	// モデルの拡大率設定
	MV1SetScale(modelHandle, INITIAL_SCALE);
}

/// <summary>
/// 終了処理
/// </summary>
void Boss::Fainalize()
{
}

/// <summary>
/// 活性化処理
/// </summary>
void Boss::Activate()
{
	position = INITIAL_POSITION;
	nextPosition = position;
	prevPosition = position;
	direction = INITIAL_DIRECTION;
	nextDirection = direction;
	prevDirection = direction;
	// 当たり判定球情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = collideRadius;


	// 初期状態を NORMAL に（後に別途行動切り替え）
	state = State::ATTACK;
	pUpdate = &Boss::UpdateAttack;

	// モデルを初期位置に配置
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 非活性化処理
/// </summary>
void Boss::Deactivate()
{
}

/// <summary>
/// 更新処理
/// </summary>
void Boss::Update()
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();		// 状態ごとの更新処理
	}

	// 当たり判定球移動
	collisionSphere.Move(position);
}

/// <summary>
/// 描画処理
/// </summary>
void Boss::Draw()
{
	// 描画しないフレームなら描画しない
	if (state == State::DEAD)
	{
		return;
	}
	
	MV1DrawModel(modelHandle);

#ifdef DEBUG
	//当たり判定デバック描画
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		8, GetColor(0, 255, 0), 0, FALSE);
#endif // DEBUG
}

/// <summary>
/// 移動予定地に実際に移動する
/// </summary>
void Boss::MoveFinish()
{
}

void Boss::UpdateAttack()
{
	
}
