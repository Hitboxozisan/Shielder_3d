//----------------------------------------------------------------
// <不具合・バグ>
// ・
// <note>
// ・Update関数はStateごとに配列で管理したほうが楽か？（そもそもできるのか）
//----------------------------------------------------------------
#pragma once

#include "Mover.h"

using namespace My3dLib;

class Timer;
class Player;
class Bullet;
class BulletCreater;
class EffectManager;

class Boss : public Mover
{
public:
	Boss(Player* inPlayer,
		 BulletCreater* const inBulletCreater);
	~Boss();

	// ボス自身のステータス
	enum class State
	{
		NONE,		// 存在しない
		MOVE,		// 移動
		ATTACK,		// 攻撃
		SLIDE,		// 跳ね返る
		DEAD		// 死亡
	};

	// 攻撃状態
	enum class AttackState
	{
		ASSAULT = 0,	// 突進攻撃
		BULLET,			// 通常弾発射
		//SLOW_BULLET,	// 遅延弾発射
		JUMP,			// ジャンプ
		TELEPORT,		// 瞬間移動
		//KICK,			// キック
		//JUDGE,			// どこにいるか判断
		//BACK,			// 画面端に戻る
		THINKING,		// 行動思考・決定

		ATTACK_AMOUST	// 行動パターン数
	};

	void Initialize(EffectManager* const inEffectManager);		// 初期化処理
	void Fainalize();		// 終了処理
	void Activate();		// 活性化処理
	void Deactivate();		// 非活性化処理
	void Update();			// 更新処理
	void Draw();			// 描画処理

	void MoveFinish();		// 移動予定地に実際に移動する

	void HitOtherCharacter(const VECTOR& forceDirection);	// 他のキャラクターに接触した
	void HitShield(const VECTOR& forceDirection,
				   const bool isJust);						// シールドに接触した

	const float GetHitPoint();			// 現在のHitPointを返す
	const float GetCollideRadius();		// 当たり判定球半径を返す
private:
	static const VECTOR INITIAL_POSITION;			// 初期位置
	static const VECTOR INITIAL_DIRECTION;			// 初期向き
	static const VECTOR INITIAL_SCALE;				// 初期サイズ
	static const VECTOR JUMP_FORCE;					// ジャンプ力
	static const float  FRICTIONAL_FORCE;			// 摩擦力
	static const float  GRAVITY;					// 重力
	static const float  DECREMENT_HIT_POINT;		// 接触時のHitPoint減少量
	static const float  ASSAULT_MAGNIFICATION;		// ASSAULT時の減少倍率
	static const float  BULLET_MAGNIFICATION;		// BULLET時の減少倍率
	static const float  IS_JUST_MAGNIFICATION;		// "ジャストガード"時の減少倍率
	static const float  FORCE_AT_HIT_SHIELD;		// 盾と接触時の力
	static const float  COLLIDE_RADIUS;				// 当たり判定球半径
	static const float  VIBRATE_TIME;				// 振動する時間
	static const float  ASSAULT_SPEED;				// 突進速度
	static const float  ASSAULT_DISTANCE;			// 突進する距離
	static const float  TELEPORT_DISTANCE;			// 瞬間移動する距離（プレイヤーを中心とする半径）
	static const float  TELEPORT_TIME;				// 瞬間移動時消滅する時間（秒）
	static const float  SHOT_INTERVAL;				// 発射間隔（秒）
	static const int    ASSAULT_TIME;				// 突進回数
	static const int	SHOT_TIME;					// 発射回数

	int	   assaultTime;					// 突進回数
	int	   shotTime;					// 発射回数
	float  hitPoint;					// 体力
	float  vibrateTime;					// 振動時間
	float  trunkMagnification;			// 防がれたときの体幹ゲージの減る倍率
	VECTOR startAssaultPosition;		// 突進開始位置
	VECTOR force;						// 加わる力（跳ね返るときに主に使用）
	VECTOR jumpForce;					// ジャンプ力

	Player* player;						// Playerクラスのポインタ
	EffectManager* effectManager;		// EffectManagerクラスのポインタ
	Timer* timer;						// Timerクラスのポインタ
	Bullet* bullet;						// Bulletクラスのポインタ
	BulletCreater* bulletCreater;		// BulletCreaterクラスのポインタ

	State state;						// 状態
	AttackState attackState;			// 攻撃パターン
	AttackState prevAttackState;		// 前回の攻撃パターン
	Sphere collisionSphere;				// 当たり判定球


	void (Boss::* pUpdate)();			// Update関数ポインタ
	void (Boss::* pUpdateAttack)();		// UpdateAttack関数ポインタ

	// AttackStateに合わせて更新処理を変更する
	// これは一時的なもの
	void SetNextAttackUpdate();

	// 次のStateを決定する（デバッグ用）
	void SetNextAttackState();

	// 各Stateごとの更新処理
	void UpdateMove();
	void UpdateAttack();
	void UpdateSlide();

	// 各AttackStateごとの更新処理
	void UpdateAssault();
	void UpdateBullet();
	void UpdateJump();
	void UpdateTeleport();
	void UpdateThinking();


	void DecrementHitPoint(bool isJust);			// HitPointを減少させる
	void ChangeStateInitialize();					// 状態変化時の初期化
	void ChangeAttackState(AttackState nextState);	// 攻撃パターン変更
	void ResetPositionYaw();						// Y座標を0.0fの位置に戻す
	void FaceToPlayer();							// プレイヤーのほうを向く
	void AssaultToPlayer();							// プレイヤーに向かって突進する
	void ReloadBullet();							// 弾を補充する
	void ShootBullet();								// 弾を発射する
	bool Jump();									// ジャンプする
	bool Vibrate();									// 振動する
	bool Teleport();								// 瞬間移動する
	bool Slide();									// 防御されたときの反動

	// 判断（この辺り↓は別途クラスで処理するべき）
	// 判断用定数
	static const float NEAR_DISTANCE;				// プレイヤーに近いと判断する距離
	static const float FAR_DISTANCE;				// 初期位置から離れているかと判断する距離

	// 判断関係関数
	const bool PlayerWithRangeNear();				// プレイヤーとの距離が近いか
	const bool InitPosWithRangeFar();				// 初期位置から離れているか

};

