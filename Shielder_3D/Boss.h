#pragma once

#include "Mover.h"

using namespace My3dLib;

class Boss : public Mover
{
public:
	Boss();
	~Boss();

	enum class State
	{
		NONE,		// 存在しない
		ATTACK,		// 攻撃
		DEAD		// 死亡
	};

	enum class AttackState
	{

	};

	void Initialize();		// 初期化処理
	void Fainalize();		// 終了処理
	void Activate();		// 活性化処理
	void Deactivate();		// 非活性化処理
	void Update();			// 更新処理
	void Draw();			// 描画処理

	void MoveFinish();		// 移動予定地に実際に移動する
private:
	static const VECTOR INITIAL_POSITION;		// 初期位置
	static const VECTOR INITIAL_DIRECTION;		// 初期向き
	static const VECTOR INITIAL_SCALE;			// 初期サイズ
	static const float  COLLIDE_RADIUS;			// 当たり判定球半径

	State state;						// 状態
	Sphere collisionSphere;				// 当たり判定球

	float collideRadius;				// 当たり判定半径

	void (Boss::* pUpdate)();			// Update関数ポインタ

	// 各Stateごとの更新処理
	void UpdateAttack();
};

