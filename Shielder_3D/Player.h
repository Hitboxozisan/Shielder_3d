#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player();
	~Player();

	// 状態
	enum State
	{
		NONE,		// 存在しない
		NORMAL,		// 通常
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
	static const VECTOR NORMAL_SPEED;			// 
	static const float  MAX_HITPOINT;			// 最大HitPoint

	State state;								// 状態
	VECTOR inputDirection;						// 入力方向

	void (Player::* pUpdate)();					// Update関数ポインタ

	// 各Stateごとの更新処理
	void UpdateNomal();							// NORMAL時更新処理
	void UpdateDead();							// DEAD時更新処理

	void InputAction();							// 入力処理
};