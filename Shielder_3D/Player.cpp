//----------------------------------------------------------------
// <不具合・バグ>
// ・ロックオン中、速度を減衰するのは向きに影響するため移動中入力を止めると、
// 　前に進む不具合が発生中。直前の入力向きを取得することで解決か？
// 
//----------------------------------------------------------------

#include "Pch.h"
#include "Player.h"
#include "Shield.h"
#include "Camera.h"
#include "EffectManager.h"
#include "DeltaTime.h"
#include "KeyManager.h"
#include "ModelManager.h"
#include "Timer.h"

const VECTOR Player::INITIAL_POSITION    = VGet(500.0f, 0.0f, 100.0f);
const VECTOR Player::INITIAL_DIRECTION   = VGet(0.0f, 0.0f, 1.0f);
const VECTOR Player::INITIAL_SCALE       = VGet(0.5f, 0.5f, 0.5f);
const float  Player::SPEED_INCREASE      = 5.0f;
const float  Player::SPEED_DECREASE      = 10.0f;
const float  Player::MAX_HIT_POINT	     = 100.0f;
const float  Player::MAX_NORMAL_SPEED    = 500.0f;
const float  Player::MAX_DEFENSE_SPEED   = 200.0f;
const float  Player::COLLIDE_RADIUS	     = 100.0f;
const float  Player::DECREMENT_HIT_POINT = 10.0f;
const float  Player::FORCE_AT_DAMAGE	 = 500.0f;
const float  Player::FORCE_AT_DEFENSE    = 300.0f;
const float  Player::FRICTIONAL_FORCE	 = -400.0f;

using namespace Math3d;		// VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player(Camera* const inCamera)
	:inputDirection(ZERO_VECTOR)
	,camera(inCamera)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize(EffectManager* const inEffectManager)
{
	shield = new Shield();
	shield->Initialize(inEffectManager);

	effectManager = inEffectManager;
	// モデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	// モデルの拡大率設定
	MV1SetScale(modelHandle, INITIAL_SCALE);
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{
	
}

/// <summary>
/// 活性化処理
/// </summary>
void Player::Activate()
{
	// 初期位置・向きを設定
	position = INITIAL_POSITION;
	nextPosition = position;
	prevPosition = position;
	direction = INITIAL_DIRECTION;
	nextDirection = direction;
	prevDirection = direction;
	hitPoint = MAX_HIT_POINT;
	speed = 0.0f;
	maxSpeed = MAX_NORMAL_SPEED;
	frame = 0;
	noDrawFrame = false;
	// 当たり判定球情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = COLLIDE_RADIUS;


	// 状態を NORMAL に
	state = State::NORMAL;
	pUpdate = &Player::UpdateNomal;

	// モデルを初期位置に配置
	MV1SetPosition(modelHandle, position);

}

/// <summary>
/// 非活性化処理
/// </summary>
void Player::Deactivate()
{
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();		// 状態ごとの更新処理
	}

	// 当たり判定球移動処理
	collisionSphere.Move(position);
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{
	// 描画しないフレームなら描画しない
	if (noDrawFrame || state == State::DEAD)
	{
		return;
	}

	MV1DrawModel(modelHandle);
	shield->Draw();

#ifdef DEBUG
	//当たり判定デバック描画
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		32, GetColor(0, 255, 0), 0, FALSE);

#endif // DEBUG
}

/// <summary>
/// ゲーム開始時の処理（演出用）
/// </summary>
void Player::GameStart()
{
}

/// <summary>
/// 無敵状態解除
/// </summary>
void Player::Releaseinvincible()
{

}

/// <summary>
/// 他のキャラクターと接触した
/// </summary>
void Player::HitOtherCharacter(const VECTOR& forceDirection)
{
	// 跳ね返る力を設定
	force = forceDirection;
	force = VScale(force, FORCE_AT_DAMAGE);

	// ダメージエフェクトを生成する
	effectManager->CreateDamageEffect(position);

	// HitPointを減少させる
	DecrementHitPoint();

	// 状態を DAMAGE に
	state = State::DAMAGE;
	pUpdate = &Player::UpdateDamage;
}

/// <summary>
/// シールドが他のキャラクターが接触した
/// </summary>
/// <param name="forceDirection"></param>
void Player::HitShieldOtherCharacter(const VECTOR& forceDirection)
{
	// 跳ね返る力を設定
	force = forceDirection;
	force = VScale(force, FORCE_AT_DEFENSE);

	// ガードエフェクトを生成する
	effectManager->CreateSparkEffect(position);

	// 状態を DAMAGE に
	state = State::PREVENT;
	pUpdate = &Player::UpdatePrevent;
}

/// <summary>
/// 当たり判定球半径を返す
/// </summary>
/// <returns></returns>
const float Player::GetCollideRadius()
{
	return collisionSphere.radius;
}

const float Player::GetHitPoint()
{
	return hitPoint;
}

/// <summary>
/// プレイヤーの状態を返す
/// </summary>
/// <returns></returns>
const Player::State Player::GetCurrentState()
{
	return state;
}

/// <summary>
/// 盾のポインタを返す
/// </summary>
/// <returns></returns>
Shield *Player::GetShieldPointer()
{
	return shield;
}

///// <summary>
///// 盾の現在位置を返す
///// </summary>
///// <returns></returns>
//VECTOR Player::GetShieldPosition()
//{
//	shield->GetPosition();
//}
//
//State Player::GetShieldState()
//{
//	return shield->GetState();
//}

/// <summary>
/// NORMAL時更新処理
/// </summary>
void Player::UpdateNomal()
{
	Move();
	MoveFinish();
	InputAction();
}
/// <summary>
/// DEFENSE時更新処理
/// </summary>
void Player::UpdateDefense()
{
	Move();
	MoveFinish();
	InputAction();
	shield->SetShieldPosition(position, direction, prevDirection);
	shield->Update();
}

/// <summary>
/// PREVENT時更新処理
/// </summary>
void Player::UpdatePrevent()
{
	MoveFinish();
	DefenseBouncePlayer();
	shield->SetShieldPosition(position, direction, prevDirection);
	shield->Update();
}

/// <summary>
/// DAMAGE時の更新処理
/// </summary>
void Player::UpdateDamage()
{
	// 跳ね返り終了後行動可能に
	if (DamageBouncePlayer())
	{
		/*InputAction();
		InvincibleUpdate();
		Move();*/
	}

	// 移動予定地に実際に移動する
	MoveFinish();
}

/// <summary>
/// DEAD時更新処理
/// </summary>
void Player::UpdateDead()
{

}

/// <summary>
/// 移動処理
/// </summary>
void Player::Move()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	// 入力があると移動する
	if (VSize(inputDirection) != 0.0f)
	{
		// 正規化
		inputDirection = VNorm(inputDirection);
		// 最大速度まで移動速度を徐々に増加させる
		if (speed <= maxSpeed)
		{
			speed += SPEED_INCREASE;
		}

		nextDirection = inputDirection;
	}
	else
	{
		// 移動速度を徐々に減少させる
		if (speed > 0.0f)
		{
			speed -= SPEED_DECREASE;
		}
		else
		{
			speed = 0.0f;
		}
	}

	nextPosition = VAdd(position, VScale(nextDirection, speed) * deltaTime);

	// ロックオン中の場合は向きを固定する
	if (camera->IsRockOn())
	{
		VECTOR front = position - camera->GetPosition();
		front.y = 0.0f;
		front = VNorm(front);
		nextDirection = front;
	}

	
}

/// <summary>
/// 
/// </summary>
//void Player::MoveFinish()
//{
//	printfDx("child");
//}

/// <summary>
/// 入力処理
/// </summary>
void Player::InputAction()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	VECTOR yAxis = { 0, 1, 0 };
	VECTOR front = position - camera->GetPosition();
	front.y = 0.0f;				// 高さベクトルを考慮しない
	front = VNorm(front);
	VECTOR left = VCross(front, yAxis);

	inputDirection = ZERO_VECTOR;

#ifdef DEBUG
	// Pキーで死亡
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_P))
	{
		hitPoint = 0;
	}

#endif // DEBUG

	// 前後左右移動
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_W))
	{
		inputDirection += front;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_S))
	{
		inputDirection += VScale(front, -1.0f);
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_A))
	{
		inputDirection += left;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_D))
	{
		inputDirection += VScale(left, -1.0f);
	}

	// ロックオン切り替え
	if (KeyManager::GetInstance().CheckJustPressed(KEY_INPUT_R))
	{
		camera->ChangeCamera();
	}

	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		// ジャンプ

	}

	// 防御
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_LSHIFT) ||
		KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		ChangeSpeed(MAX_DEFENSE_SPEED);			// 速度を変更する
		ActivateShield();						// 盾を生成する
	}
	else
	{
		ChangeSpeed(MAX_NORMAL_SPEED);			// 速度を変更する
		shield->Deactivate();					// 盾を消滅させる
	}

	// 回復
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_R))
	{
		//Recovery();
	}
}

/// <summary>
/// 最大移動速度を変更する
/// </summary>
/// <param name="speed">変更後の最大速度</param>
void Player::ChangeSpeed(float afterSpeed)
{
	maxSpeed = afterSpeed;
	// 変更時、移動速度が変更後の最大速度より速かったら速度を落とす
	if (speed > maxSpeed)
	{
		speed = maxSpeed;
	}
}

/// <summary>
/// 盾を展開する
/// </summary>
void Player::ActivateShield()
{
	// 盾が既に存在してるもしくは破壊されているなら処理しない
	if (shield->GetState() == Shield::State::DEPLOYMENT ||
		shield->GetState() == Shield::State::DESTRUCTION)
	{
		return;
	}
	shield->Activate(position, direction, prevDirection);
	pUpdate = &Player::UpdateDefense;
}

/// <summary>
/// 盾を消滅させる
/// </summary>
void Player::DeactivateShield()
{
	shield->Deactivate();
	pUpdate = &Player::UpdateNomal;
}

/// <summary>
/// 体力を減少させる
/// </summary>
void Player::DecrementHitPoint()
{
	// HitPointを減少させる
	hitPoint -= DECREMENT_HIT_POINT;
	// HitPointが底をついたらこれ以上減少しないようにする
	if (hitPoint <= 0)
	{
		hitPoint = 0.0f;
	}
}

/// <summary>
/// 無敵状態処理
/// </summary>
void Player::InvincibleUpdate()
{
	// インスタンスの生成
	if (timer == nullptr)
	{
		timer = new Timer(2.0f);
	}

	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	// 一定時間無敵状態にする
	timer->Update(deltaTime);

	// 一定時間経過後無敵状態解除
	if (timer->IsTimeout())
	{
		noDrawFrame = false;

		// 状態を NORMAL に
		state = State::NORMAL;
		pUpdate = &Player::UpdateNomal;
	}
	else
	{
		// 2フレームに1回描画する
		noDrawFrame != noDrawFrame;
	}

}

/// <summary>
/// プレイヤーを跳ね返す（ダメージ）
/// </summary>
bool Player::DamageBouncePlayer()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	++frame;

	// 摩擦力を設定
	VECTOR frictionalForce = VNorm(force);
	frictionalForce = VScale(frictionalForce, FRICTIONAL_FORCE);

	nextPosition = VAdd(nextPosition, force * deltaTime);
	force = VAdd(force, frictionalForce * deltaTime);

	// 一定時間おきにエフェクト生成
	if (frame % 10 == 0)
	{
		// スモークエフェクト生成
		effectManager->CreateSmokeEffect(nextPosition);
	}
	
	// 跳ね返す力が0に近くなったら終了する
	if (VSize(force) <= 1.0f)
	{
		// 経過フレームをリセット
		frame = 0;
		// 状態を NORMAL に
		state = State::NORMAL;
		pUpdate = &Player::UpdateNomal;
		return true;
	}
	return false;
}

/// <summary>
/// プレイヤーを跳ね返す（ディフェンス）
/// </summary>
/// <returns></returns>
bool Player::DefenseBouncePlayer()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	++frame;

	// 摩擦力を設定
	VECTOR frictionalForce = VNorm(force);
	frictionalForce = VScale(frictionalForce, FRICTIONAL_FORCE);

	// 移動
	nextPosition = VAdd(nextPosition, force * deltaTime);
	force = VAdd(force, frictionalForce * deltaTime);

	// 一定時間おきにエフェクト生成
	if (frame % 10 == 0)
	{
		// スモークエフェクト生成
		effectManager->CreateSmokeEffect(nextPosition);
	}

	// 跳ね返す力が0に近くなったら終了する
	if (VSize(force) <= 1.0f)
	{
		// シールドを非活性化
		shield->Deactivate();
		// 経過フレームをリセット
		frame = 0;
		// 力を0に戻す


		// 状態を NORMAL に
		state = State::NORMAL;
		pUpdate = &Player::UpdateNomal;
		return true;
	}
	return false;
}

