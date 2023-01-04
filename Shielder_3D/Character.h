#pragma once

#include "Mover.h"

class Character : public Mover
{
public:
	Character();
	virtual ~Character();

	virtual void Initialize() = 0;		// 初期化処理
	virtual void Finalize() = 0;		// 終了処理
	virtual void Activate() = 0;		// 活性化処理
	virtual void Deactivate() = 0;		// 非活性化処理
	virtual void Update() = 0;			// 更新処理
	virtual void Draw() = 0;			// 描画処理

	void		 MoveFinish();				// 移動予定地に実際に移動
	virtual void GameStart() = 0;			// ゲーム開始時（演出用）
	virtual void Releaseinvincible() = 0;	// 無敵状態解除

	bool IsAlive();							// 生きているかを返す

protected:

	float hitPoint;	
	float speed;					// 移動速度				
	float invincibleTime;			// 無敵時間
	bool  noDrawFrame;				// 描画可能フレームか
	bool  isAlive;					// 生きているか

private:


};

