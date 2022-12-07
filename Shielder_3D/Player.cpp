#include "Pch.h"
#include "Player.h"
#include "KeyManager.h"
#include "ModelManager.h"

const VECTOR Player::INITIAL_POSITION  = VGet(500.0f, 0.0f, 100.0f);
const VECTOR Player::INITIAL_DIRECTION = VGet(0.0f, 0.0f, 1.0f);

using namespace Math3d;		// VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
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
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

	

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

	// 状態を NORMAL に
	state = NORMAL;
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

}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{
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
	MoveFinish();
}

/// <summary>
/// DEAD時更新処理
/// </summary>
void Player::UpdateDead()
{

}

/// <summary>
/// 入力処理
/// </summary>
void Player::InputAction()
{
#ifdef DEBUG
	// Pキーで死亡
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_P))
	{
		hitPoint = 0;
	}

#endif // DEBUG

	// 左右移動
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_A) && nextPosition.x >= SCREEN_LEFTMOST)
	{
		inputDirection += LEFT * speed * deltaTime;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_D) && nextPosition.x <= SCREEN_RIGHTMOST)
	{
		inputDirection += RIGHT * speed * deltaTime;
	}

	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		// ジャンプ

	}

	// 防御
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_LSHIFT) ||
		KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		speed = DEFENSE_SPEED;	// 移動速度変更
		CreateShield();			// 盾生成

		pUpdate = &Player::UpdateDefence;
	}
	else
	{
		speed = NORMAL_SPEED;	// 

		shield->Deactivate();	//盾を消滅させる
		pUpdate = &Player::UpdateNormal;
	}

	// 回復
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_R))
	{
		Recovery();
	}
}
