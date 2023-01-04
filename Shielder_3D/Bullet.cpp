#include "Pch.h"

#include "Bullet.h"

#include "ModelManager.h"

const float Bullet::NORMAL_SPEED   = 16.0f;
const float Bullet::SLOW_SPEED     = 8.0f;
const float Bullet::SCALE_BY_DIRECTION_FOR_CORRECTION = 1.0f;
const float Bullet::COLLIDE_RADIUS = 50.0f;

/// <summary>
/// コンストラクタ
/// </summary>
Bullet::Bullet()
	:state(NONE)
	,velocity()
	,speed(0.0f)
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Bullet::~Bullet()
{
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void Bullet::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BULLET));
}

/// <summary>
/// 終了処理
/// </summary>
void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// 活性化処理
/// </summary>
/// <param name="inPosition">発射位置</param>
/// <param name="inDirection">発射向き</param>
void Bullet::Activate(const VECTOR& inPosition, const VECTOR& inDirection)
{
	// 位置・向きを設定
	position = inPosition;
	nextPosition = position;
	prevPosition = position;
	direction = inDirection;
	nextDirection = direction;
	prevDirection = direction;

	velocity = ZERO_VECTOR;
	
	state = NORMAL;

	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.radius = COLLIDE_RADIUS;
	collisionSphere.worldCenter = position;

	SetToFrontOfEnemy(inPosition, inDirection);					// エネミーの前方に位置調整

	MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.2f));			// モデル拡大縮小
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, 1.5f, 0.0f));		// モデルの向きを設定
}

/// <summary>
/// 非活性化処理
/// </summary>
void Bullet::Deactivate()
{
	state = NONE;
}

/// <summary>
/// 更新処理
/// </summary>
/// <returns></returns>
bool Bullet::Update()
{
	//存在しないなら処理しない
	if (state == NONE)
	{
		return false;
	}

	//エネミー攻撃が通常球なら
	if (state == NORMAL)
	{
		speed = NORMAL_SPEED;
	}
	else
	{
		speed = SLOW_SPEED;
	}

	//テスト用direction
	//direction = VGet(0.5f, 0.0f, 0.0f);

	//飛んでいるときの処理
	if (state == NORMAL ||
		state == SLOW)
	{
		Move();
		return true;
	}

	return true;
}

/// <summary>
/// 描画処理
/// </summary>
void Bullet::Draw()
{
	// 存在しないなら描画しない
	if (state == NONE)
	{
		return;
	}

	MV1SetPosition(modelHandle, position);		// 3Dモデルのポジション設定
	

	MV1DrawModel(modelHandle);					// 3Dモデルの描画

#ifdef DEBUG

	// 当たり判定デバック描画
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		8, GetColor(0, 255, 0), 0, FALSE);

#endif // DEBUG	
}

/// <summary>
/// 
/// </summary>
/// <param name="attackType"></param>
void Bullet::Shoot(int attackType)
{
	//エネミー攻撃が通常弾なら
	if (attackType == 1)		
	{
		state = NORMAL;
	}
	else if(attackType == 2)
	{
		state = SLOW;
	}
	
}

/// <summary>
/// エネミーの前方に設置
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
void Bullet::SetToFrontOfEnemy(const VECTOR& inPosition, const VECTOR& inDirection)
{
	position = inPosition;
	direction = inDirection;

	//エネミーの前方に位置調整
	VECTOR distanceToPlayer = VScale(direction, SCALE_BY_DIRECTION_FOR_CORRECTION);

	position = VAdd(position, distanceToPlayer);
}

/// <summary>
/// 現在の状態を返す
/// </summary>
/// <returns></returns>
Bullet::State Bullet::GetState() const
{
	return state;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Bullet::IsCollidableState() const
{
	if (state == NORMAL ||
		state == SLOW)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 当たり判定球半径を返す
/// </summary>
/// <returns></returns>
const float Bullet::GetCollisionRadius() const
{
	return collisionSphere.radius;
}

/// <summary>
/// フィールド外に出た
/// </summary>
void Bullet::OnOutField()
{
	Deactivate();
}

/// <summary>
/// 何かに当たって壊れた
/// </summary>
void Bullet::OnHitBreak()
{
	state = NONE;
}

/// <summary>
/// 移動処理
/// </summary>
void Bullet::Move()
{
	//フィールド外に出たら消滅させる


	position = VAdd(position, VScale(direction, speed));	//向いている方向に移動
	collisionSphere.Move(position);				//当たり判定球移動
}
