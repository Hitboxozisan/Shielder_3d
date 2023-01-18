#pragma once

#include "Mover.h"

class Sword : public Mover
{
public:
	// オブジェクトの状態
	enum class State
	{
		NONE,		// 存在しない
		ACTIVE		// 存在している
	};

	Sword();
	~Sword();

	void Initialize();							// 初期化処理
	void Finalize();							// 終了処理
	void Activate(const VECTOR& inPosition,
				  const VECTOR& inDirection);	// 活性化処理
	void Deactivate();							// 非活性化処理
	void Update();								// 更新処理
	void Draw();								// 描画処理

	void activateSword(const VECTOR& inPosition,
					   const VECTOR& inDirection);	// 剣を存在させる
	void rollSword();								// 剣を振る
private:
	static const VECTOR INITIAL_POSITION;						// 初期位置
	static const VECTOR INITIAL_DIRECTION;						// 初期向き
	static const VECTOR INITIAL_SCALE;							// 初期サイズ
	static const float SCALE_BY_DIRECTION_FOR_CORRECTION;		// 前方距離

	State state;

	void SetToFrontOfObject(const VECTOR& inPosition,
							const VECTOR& inDirection);			// オブジェクトの前に配置する
	void MoveFinish();											// 移動予定地に実際に移動する
};

