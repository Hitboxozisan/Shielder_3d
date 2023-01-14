#include "Pch.h"

#include "Bullet.h"
#include "DeltaTime.h"
#include "ModelManager.h"

const VECTOR Bullet::INITIAL_SCALE			 = VGet(0.5f, 0.5f, 0.5f);
const float  Bullet::NORMAL_SPEED		     = 1000.0f;
const float  Bullet::SLOW_SPEED				 = 200.0f;
const float  Bullet::SCALE_BY_DIRECTION_FOR_CORRECTION = 1.0f;
const float  Bullet::NORMAL_FORWARD_DISTANCE = 100.0f;
const float  Bullet::COLLIDE_RADIUS			 = 50.0f;

/// <summary>
/// コンストラクタ
/// </summary>
Bullet::Bullet()
	:state(State::NORMAL)
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
	
	speed = NORMAL_SPEED;
	state = State::SHOOT;

	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.radius = COLLIDE_RADIUS;
	collisionSphere.worldCenter = position;

	SetToFrontOfEnemy(inPosition, inDirection);					// エネミーの前方に位置調整

	MV1SetScale(modelHandle, INITIAL_SCALE);					// モデル拡大縮小
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, 1.5f, 0.0f));		// モデルの向きを設定
}

/// <summary>
/// 非活性化処理
/// </summary>
void Bullet::Deactivate()
{
	state = State::NORMAL;
}

/// <summary>
/// 更新処理
/// </summary>
/// <returns></returns>
bool Bullet::Update()
{
	//存在しないなら処理しない
	if (state == State::NONE)
	{
		return false;
	}

	//飛んでいるときの処理
	if (state == State::NORMAL ||
		state == State::SHOOT)
	{
		if (state == State::NORMAL)
		{
			
		}
		else
		{
			Move();
		}
		MoveFinish();

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
	if (state == State::NONE)
	{
		return;
	}

	MV1DrawModel(modelHandle);					// 3Dモデルの描画

#ifdef DEBUG

	// 当たり判定デバック描画
	//DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		//8, GetColor(0, 255, 0), 0, FALSE);

#endif // DEBUG	
}

/// <summary>
/// 
/// </summary>
/// <param name="attackType"></param>
void Bullet::Shoot()
{
	// 発射状態にする
	state = State::SHOOT;
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

	nextPosition = VAdd(nextPosition, distanceToPlayer);
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
	if (state == State::NORMAL ||
		state == State::SHOOT)
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
	state = State::NONE;
}

/// <summary>
/// 移動処理
/// </summary>
void Bullet::Move()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	//フィールド外に出たら消滅させる


	nextPosition = VAdd(nextPosition, VScale(direction, speed * deltaTime));	//向いている方向に移動
	collisionSphere.Move(position);												//当たり判定球移動
}

/// <summary>
/// 移動予定地に実際に移動する
/// </summary>
void Bullet::MoveFinish()
{
	prevPosition = position;
	position = nextPosition;
	direction = nextDirection;

	// モデルの位置を設定
	MV1SetPosition(modelHandle, position);

	// モデルの向きを設定
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
}

/// <summary>
/// オブジェクトを中心に回転
/// </summary>
void Bullet::RotationAboutObject(Mover* bullet, VECTOR objPos, int totalBullet)
{
	VECTOR objPosition = objPos;
	
	position.x = objPosition.x + NORMAL_FORWARD_DISTANCE * cosf(0.0f);
	position.z = objPosition.z + NORMAL_FORWARD_DISTANCE * sinf(1.0f);

}

/// <summary>
/// モデルの向きを発射用に設定
/// </summary>
void Bullet::SetShootDirection()
{
	// 発射用角度を設定
	VECTOR newDirection;

	// モデルの向きを設定

}

/// <summary>
/// モデルの向きを NORMAL 時に戻す
/// </summary>
void Bullet::ResetDirection()
{
	// 元の角度に戻す

}
