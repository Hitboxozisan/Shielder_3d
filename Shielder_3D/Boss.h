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

class Boss : public Mover
{
public:
	Boss(Player* inPlayer);
	~Boss();

	enum class State
	{
		NONE,		// 存在しない
		ATTACK,		// 攻撃
		SLIDE,		// 跳ね返る
		DEAD		// 死亡
	};

	enum class AttackState
	{
		ASSAULT = 0,	// 突進攻撃
		BULLET,			// 通常弾発射
		SLOW_BULLET,	// 遅延弾発射
		JUMP,			// ジャンプ
		KICK,			// キック
		JUDGE,			// どこにいるか判断
		BACK,			// 画面端に戻る
		THINKING,		// 行動思考・決定

		ATTACK_AMOUST	// 行動パターン数
	};

	void Initialize();		// 初期化処理
	void Fainalize();		// 終了処理
	void Activate();		// 活性化処理
	void Deactivate();		// 非活性化処理
	void Update();			// 更新処理
	void Draw();			// 描画処理

	void MoveFinish();		// 移動予定地に実際に移動する

	void HitOtherCharacter(const VECTOR& forceDirection);	// 他のキャラクターに接触した
	void HitShield(const VECTOR& forceDirection);			// シールドに接触した

	const float GetCollideRadius();		// 当たり判定球半径を返す
private:
	static const VECTOR INITIAL_POSITION;		// 初期位置
	static const VECTOR INITIAL_DIRECTION;		// 初期向き
	static const VECTOR INITIAL_SCALE;			// 初期サイズ
	static const float  FRICTIONAL_FORCE;		// 摩擦力
	static const float  FORCE_AT_HIT_SHIELD;	// 盾と接触時の力
	static const float  COLLIDE_RADIUS;			// 当たり判定球半径
	static const float  VIBRATE_TIME;			// 振動する時間
	static const float  ASSAULT_SPEED;			// 突進速度
	static const float  ASSAULT_DISTANCE;		// 突進する距離
	static const int    ASSAULT_TIME;			// 突進回数

	int	   assaultTime;					// 突進回数
	float  vibrateTime;					// 振動時間
	float  movedDistance;				// 突進距離
	VECTOR startAssaultPosition;		// 突進開始位置
	VECTOR force;						// 加わる力（跳ね返るときに主に使用）

	Player* player;						// Playerクラスのポインタ
	Timer* timer;						// Timerクラスのポインタ

	State state;						// 状態
	AttackState attackState;			// 攻撃パターン
	AttackState prevAttackState;		// 前回の攻撃パターン
	Sphere collisionSphere;				// 当たり判定球


	void (Boss::* pUpdate)();			// Update関数ポインタ
	void (Boss::* pUpdateAttack)();		// UpdateAttack関数ポインタ

	// AttackStateに合わせて更新処理を変更する
	// これは一時的なもの
	void SetNextAttackState();

	// 各Stateごとの更新処理
	void UpdateAttack();
	void UpdateSlide();

	// 各AttackStateごとの更新処理
	void UpdateAssault();
	void UpdateJump();
	void UpdateThinking();

	void FaceToPlayer();				// プレイヤーのほうを向く
	void AssaultToPlayer();				// プレイヤーに向かって突進する
	void Jump();						// ジャンプする
	bool Vibrate();						// 振動する
	bool Slide();						// 防御されたときの反動
};

