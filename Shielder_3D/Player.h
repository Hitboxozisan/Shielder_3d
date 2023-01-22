#pragma once

#include "Character.h"

using namespace My3dLib;

class Shield;
class Camera;
class Timer;

class Player : public Character
{
public:
	Player(Camera* const);
	~Player();

	// 状態
	enum class State
	{
		NONE,		// 存在しない
		NORMAL,		// 通常
		DEFENSE,	// 防御
		PREVENT,	// 防いだ
		DAMAGE,		// 被弾
		DEAD		// 死亡
	};

	void Initialize(EffectManager* const inEffectManager);		// 初期化処理
	void Finalize();		// 終了処理
	void Activate();		// 活性化処理
	void Deactivate();		// 非活性化処理
	void Update();			// 更新処理
	void Draw();			// 描画処理

	void GameStart();											// ゲーム開始時（演出用）
	void Releaseinvincible();									// 無敵状態解除
	void HitOtherCharacter(const VECTOR& forceDirection);		// 他のキャラクターと接触した
	void HitShieldOtherCharacter(const VECTOR& forceDirection);	// シールドが他のキャラクターと接触した

	const float GetCollideRadius();			// 当たり判定球半径を返す
	const float GetHitPoint();				// 現在のHitPointを返す
	const State GetCurrentState();			// 現在の状態を返す
		  Shield *GetShieldPointer();		// シールドのポインタを返す

	//VECTOR GetShieldPosition();			// シールドの現在位置を返す
	//State GetShieldState();				// シールドの状態を返す

private:
	static const VECTOR INITIAL_POSITION;		// 初期位置
	static const VECTOR INITIAL_DIRECTION;		// 初期向き
	static const VECTOR INITIAL_SCALE;			// 初期サイズ
	static const float  SPEED_INCREASE;			// 1フレームの速度増加量
	static const float  SPEED_DECREASE;			// 1フレームの速度減少量
	static const float  MAX_HIT_POINT;			// 最大HitPoint
	static const float  MAX_NORMAL_SPEED;		// 通常時最大速度
	static const float  MAX_DEFENSE_SPEED;		// 防御時最大速度
	static const float  COLLIDE_RADIUS;			// 当たり判定球半径
	static const float  DECREMENT_HIT_POINT;	// 接触時のHitPoint減少量 
	static const float  FORCE_AT_DAMAGE;		// 接触時に働く力
	static const float  FORCE_AT_DEFENSE;		// 防御時に働く力
	static const float  FRICTIONAL_FORCE;		// 摩擦力
	
	Shield* shield;								// Shieldクラスのポインタ
	Camera* camera;								// Cameraクラスのポインタ
	EffectManager* effectManager;				// EffectManagerクラスのポインタ
	Timer* timer;								// Timerクラスのポインタ（なんとかできないものか）

	State  state;								// 状態
	Sphere collisionSphere;						// 当たり判定球


	int    frame;								// 経過フレーム（1秒以下の描画に使用）
	float  maxSpeed;							// 最大速度
	int mousePosX;
	int mousePosY;
	VECTOR mousePosition;						// マウスポインタの位置
	VECTOR screenPosition;						// プレイヤーの画面座標
	VECTOR inputDirection;						// 入力方向
	VECTOR moveForce;							// 進もうとする力
	VECTOR force;								// 

	void (Player::* pUpdate)();					// Update関数ポインタ

	// 各Stateごとの更新処理
	void UpdateNomal();							// NORMAL時更新処理
	void UpdateDefense();						// DEFENSE時更新処理
	void UpdatePrevent();						// PREVENT時更新処理
	void UpdateDamage();						// DAMAGE時更新処理
	void UpdateDead();							// DEAD時更新処理

	// 常時作動する処理
	//void UpdateAlways();

	void Move();								// 移動処理
	///void MoveFinish();						// 移動予定地に実際に移動する
	void InputAction();							// 入力処理
	void ChangeSpeed(float afterSpeed);			// 移動速度を変更する
	void ActivateShield();						// シールドを展開する
	void DeactivateShield();					// シールドを消滅させる
	void DecrementHitPoint();					// HitPointを減少させる（遅れて減少するのはUIのほうで処理）
	void InvincibleUpdate();					// 無敵状態処理
	bool DamageBouncePlayer();					// プレイヤーを跳ね返す（ダメージ）
	bool DefenseBouncePlayer();					// プレイヤーを跳ね返す（ディフェンス）
};