#pragma once

#include "Character.h"


class Shield;
class CameraManager;

class Player : public Character
{
public:
	Player(CameraManager* const);
	~Player();

	// 状態
	enum State
	{
		NONE,		// 存在しない
		NORMAL,		// 通常
		DEFENSE,	// 防御
		DEAD		// 死亡
	};

	void Initialize();		// 初期化処理
	void Finalize();		// 終了処理
	void Activate();		// 活性化処理
	void Deactivate();		// 非活性化処理
	void Update();			// 更新処理
	void Draw();			// 描画処理

	void GameStart();			// ゲーム開始時（演出用）
	void Releaseinvincible();	// 無敵状態解除

private:
	static const VECTOR INITIAL_POSITION;		// 初期位置
	static const VECTOR INITIAL_DIRECTION;		// 初期向き
	static const VECTOR INITIAL_SCALE;			// 初期サイズ
	static const float  SPEED_INCREASE;			// 1フレームの速度増加量
	static const float  SPEED_DECREASE;			// 1フレームの速度減少量
	static const float  MAX_NORMAL_SPEED;		// 通常時最大速度
	static const float  MAX_DEFENSE_SPEED;		// 防御時最大速度
	static const float  MAX_HITPOINT;			// 最大HitPoint

	Shield* shield;								// Shieldクラスのポインタ
	CameraManager* cameraManager;				// CameraManagerクラスのポインタ

	State state;								// 状態
	VECTOR inputDirection;						// 入力方向

	float maxSpeed;								// 最大速度

	void (Player::* pUpdate)();					// Update関数ポインタ

	// 各Stateごとの更新処理
	void UpdateNomal();							// NORMAL時更新処理
	void UpdateDefense();						// DEFENSE時更新処理
	void UpdateDead();							// DEAD時更新処理

	void Move();								// 移動処理
	///void MoveFinish();						// 移動予定地に実際に移動する
	void InputAction();							// 入力処理
	void ChangeSpeed(float afterSpeed);			// 移動速度を変更する
	void ActivateShield();						// 盾を展開する
	void DeactivateShield();					// 盾を消滅させる
};