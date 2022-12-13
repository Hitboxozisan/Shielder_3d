#pragma once

#include "ObjectBase.h"

class Shield final : public ObjectBase
{
public:
	Shield();
	~Shield();

	// 状態
	enum class State
	{
		NONE,			// 存在しない
		DEPLOYMENT,		// 展開中
		DESTRUCTION		// 破壊
	};

	void Initialize();									// 初期化処理
	void Finalize();									// 終了処理
	void Activate(const VECTOR& inPosition,
				  const VECTOR& inDirection,
				  const VECTOR& inPrevDirection);		// 活性化処理
	void Deactivate();									// 非活性化処理
	void Update();										// 更新処理
	void Draw();										// 描画処理

	void DecrementHitPoint();							// 耐久値を減少させる

	State GetState() const { return state; }			// 現在の状態を返す
	void SetShieldPosition(const VECTOR& inPosition,
							 const VECTOR& inDirection,
							 const VECTOR& inPrevDirection);	// シールドの位置を設定

private:
	Shield(const Shield&);			// コピーコンストラクタ
	void operator=(const Shield&);	// 代入演算子

	static const float MAX_HITPOINT;							// 最大耐久値
	static const float SCALE_BY_DIRECTION_FOR_CORRECTION;		// プレイヤーとの距離

	State state;

	void (Shield::* pUpdate)();		// Update関数ポインタ

	float hitPoint;					// シールドの耐久値
	float elapsedtTime;				// シールドを展開してからの経過時間
	VECTOR distanceToPlayer;		// プレイヤーとの距離

	void UpdateDeployment();		// DEPLOYMENT時更新処理
	void UpdateDestruction();		// DESTRUCTION時更新処理

};

