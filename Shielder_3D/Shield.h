#pragma once

#include "ObjectBase.h"
#include "EffectManager.h"

class Timer;

using namespace My3dLib;

class Shield final : public ObjectBase
{
public:
	Shield();
	~Shield();

	// 状態
	enum class State
	{
		NONE,			// 存在しない
		COOL_TIME,		// 消滅中
		DEPLOYMENT,		// 展開中
		DESTRUCTION		// 破壊
	};

	void Initialize(EffectManager* inEffectManager);									// 初期化処理
	void Finalize();									// 終了処理
	void Activate(const VECTOR& inPosition,
				  const VECTOR& inDirection,
				  const VECTOR& inPrevDirection);		// 活性化処理
	void Deactivate();									// 非活性化処理
	void Update();										// 更新処理
	void Draw();										// 描画処理

	// 当たり判定関係
	// 処理が被っているところは綺麗にしたい
	void HitOtherCharacter(float magnification);		// 他のキャラクターと接触した
	void HitBullet(float magnification);				// 敵が発射した弾と接触した

	// セッター・ゲッター
	void SetShieldPosition(const VECTOR& inPosition,
						   const VECTOR& inDirection,
						   const VECTOR& inPrevDirection);	// シールドの位置を設定
	const float GetCollideRadius();							// 当たり判定球半径を返す
	const bool isJust();									// "ジャストガード"かどうか
	State GetState() const { return state; }				// 現在の状態を返す
	

private:
	Shield(const Shield&);			// コピーコンストラクタ
	void operator=(const Shield&);	// 代入演算子
	
	static const VECTOR INITIAL_SCALE;							// 初期サイズ
	static const float  MAX_TRUNK_POINT;						// 最大耐久値
	static const float  SCALE_BY_DIRECTION_FOR_CORRECTION;		// プレイヤーとの距離
	static const float  JUST_DEFENSE_TIME;						// "ジャストガード"と判断する時間
	static const float  COLLIDE_RADIUS;							// 当たり判定球半径
	static const float  COLLIDE_HEIGHT;							// 当たり判定球高さ
	static const float  INCREMENT_TRUNK_POINT;					// 接触時に増加する耐久値量
	static const float  DECREMENT_TRUNK_POINT;					// 耐久値の減少量

	EffectManager* effectManager;	// EffectManagerクラスのポインタ
	Timer* timer;					// Timerクラスのポインタ

	State state;
	Sphere collisionSphere;			// 本来なら球体を使うべきではないが
									// 端に攻撃が当たることは少ないため楽をする

	void (Shield::* pUpdate)();		// Update関数ポインタ

	float trunkPoint;				// シールドの耐久値
	float elapsedtTime;				// シールドを展開してからの経過時間
	VECTOR distanceToPlayer;		// プレイヤーとの距離

	void MoveFinish();				// 実際に移動する

	void UpdateCoolTime();			// COOLTIME時更新処理
	void UpdateDeployment();		// DEPLOYMENT時更新処理
	void UpdateDestruction();		// DESTRUCTION時更新処理

	bool IncrementTrunkPoint(float magnification);		// シールドの耐久値を増加させる
	bool DecrementTrunkPoint();							// シールドの耐久値を減少させる

};

