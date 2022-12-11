#include "Pch.h"
#include "Player.h"
#include "DeltaTime.h"
#include "KeyManager.h"
#include "ModelManager.h"

const VECTOR Player::INITIAL_POSITION  = VGet(500.0f, 0.0f, 100.0f);
const VECTOR Player::INITIAL_DIRECTION = VGet(0.0f, 0.0f, 1.0f);
const VECTOR Player::INITIAL_SCALE     = VGet(0.5f, 0.5f, 0.5f);
const float  Player::SPEED_INCREASE    = 5.0f;
const float  Player::SPEED_DECREASE    = 10.0f;
const float  Player::MAX_NORMAL_SPEED  = 200.0f;

using namespace Math3d;		// VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	:inputDirection(ZERO_VECTOR)
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
void Player::Initialize()
{
	// モデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
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
	speed = 0.0f;
	noDrawFrame = false;

	// 状態を NORMAL に
	state = NORMAL;
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

}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{
	// 描画しないフレームなら描画しない
	if (noDrawFrame || state == DEAD)
	{
		return;
	}

	MV1DrawModel(modelHandle);
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
/// NORMAL時更新処理
/// </summary>
void Player::UpdateNomal()
{
	Move();
	MoveFinish();
	InputAction();
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
		// 最大速度まで移動速度を徐々に増加させる
		if (speed <= MAX_NORMAL_SPEED)
		{
			speed += SPEED_INCREASE;
		}

		nextDirection = VNorm(inputDirection);
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
		inputDirection += PROGRESS;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_S))
	{
		inputDirection += RECESSION;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_A))
	{
		inputDirection += LEFT;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_D))
	{
		inputDirection += RIGHT;
	}

	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		// ジャンプ

	}

	// 防御
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_LSHIFT) ||
		KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		//speed = DEFENSE_SPEED;	// 移動速度変更
		//CreateShield();			// 盾生成

		//pUpdate = &Player::UpdateDefence;
	}
	else
	{
		//speed = NORMAL_SPEED;	// 

		//shield->Deactivate();	//盾を消滅させる
		//pUpdate = &Player::UpdateNormal;
	}

	// 回復
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_R))
	{
		//Recovery();
	}
}
