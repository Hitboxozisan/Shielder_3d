#pragma once

#include "Mover.h"

class Bullet final : public Mover
{
public:
	enum State
	{
		NONE,			// 存在しない
		NORMAL,			// 滞空
		SHOOT			// 発射
	};

	Bullet();
	~Bullet();

	void Initialize();							// 初期化処理
	void Finalize();							// 終了処理
	void Activate(const VECTOR& inPosition, 
				  const VECTOR& inDirection);	// 活性化処理
	void Deactivate();							// 非活性化処理
	bool Update();								// 更新処理
	void Draw();								// 描画処理

	void Shoot(int attackType);					// 発射処理

	// エネミーの前に設置する
	void SetToFrontOfEnemy(const VECTOR& inPosition, const VECTOR& inDirection);

	State GetState() const;						// 現在の状態を返す
	bool IsCollidableState() const;				// 当たり判定がある状態か

	const float GetCollisionRadius() const;

	void OnOutField();							// フィールド外に出た
	void OnHitBreak();							// 何かに当たって壊れる
	
private:
	//定数
	static const float NORMAL_SPEED;						// 通常球移動速度
	static const float SLOW_SPEED;							// 遅延弾移動速度
	static const float SCALE_BY_DIRECTION_FOR_CORRECTION;	// 位置補正用に向きベクトルに掛ける倍率
	static const float COLLIDE_RADIUS;			   			// 当たり判定球半径

	State state;		// 現在の状態
	float speed;		// 現在の速度
	VECTOR velocity;	// 現在の速度、加速度、向きを持つ、マイナスにもなる

	My3dLib::Sphere collisionSphere;		// 当たり判定用球

	void Move();		// 移動処理
};

