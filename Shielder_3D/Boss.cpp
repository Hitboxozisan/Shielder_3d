//----------------------------------------------------------------
// <不具合・バグ>
// ・
// <note>
// ・振動時ロックオンだとわかりにくいある程度の誤差は追わないようにするべきか？
// ・ロックオン可能なのかをBossのStateを参照する影響でBossクラスのポインタを使用
// 　Activate, Updateの引数が無駄になっているため修正する必要あり
//----------------------------------------------------------------

#include "Pch.h"
#include "Boss.h"
#include "Player.h"
#include "Bullet.h"
#include "BulletCreater.h"
#include "EffectManager.h"
#include "KeyManager.h"
#include "ModelManager.h"
#include "Random.h"
#include "Timer.h"
#include "DeltaTime.h"

using namespace My3dLib;
using namespace Math3d;

const VECTOR Boss::INITIAL_POSITION      = VGet(500.0f, 0.0f, 500.0f);
const VECTOR Boss::INITIAL_DIRECTION     = VGet(0.0f, 0.0f, -1.0f);
const VECTOR Boss::INITIAL_SCALE         = VGet(0.5f, 0.5f, 0.5f);
const VECTOR Boss::JUMP_FORCE		     = VGet(0.0f, 800.0f, 0.0f);
const float  Boss::FRICTIONAL_FORCE      = -400.0f;
const float  Boss::GRAVITY			     = -10.0f;
const float  Boss::DECREMENT_HIT_POINT   = 1.0f;
const float  Boss::ASSAULT_MAGNIFICATION = 2.0f;
const float  Boss::BULLET_MAGNIFICATION  = 1.0f;
const float  Boss::IS_JUST_MAGNIFICATION = 2.0f;
const float  Boss::FORCE_AT_HIT_SHIELD	 = 300.0f;
const float  Boss::COLLIDE_RADIUS		 = 100.0f;
const float  Boss::VIBRATE_TIME			 = 1.0f;
const float  Boss::ASSAULT_SPEED		 = 1300.0f;
const float  Boss::ASSAULT_DISTANCE		 = 1500.0f;
const float  Boss::TELEPORT_DISTANCE	 = 800.0f;
const float  Boss::TELEPORT_TIME		 = 3.0f;
const float  Boss::SHOT_INTERVAL		 = 2.0f;
const int    Boss::ASSAULT_TIME			 = 3;
const int	 Boss::SHOT_TIME			 = 3;

const float Boss::NEAR_DISTANCE			 = 250.0f;
const float Boss::FAR_DISTANCE			 = 3000.0f;

/// <summary>
/// コンストラクタ
/// </summary>
Boss::Boss(Player* inPlayer,
		   BulletCreater* const inBulletCreater)
	:player(inPlayer)
	,bulletCreater(inBulletCreater)
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Boss::~Boss()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Boss::Initialize(EffectManager* const inEffectManager)
{
	effectManager = inEffectManager;
	// モデルの読み込み
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY);
	// モデルの拡大率設定
	MV1SetScale(modelHandle, INITIAL_SCALE);
}

/// <summary>
/// 終了処理
/// </summary>
void Boss::Fainalize()
{
}

/// <summary>
/// 活性化処理
/// </summary>
void Boss::Activate()
{
	position = INITIAL_POSITION;
	nextPosition = position;
	prevPosition = position;
	direction = INITIAL_DIRECTION;
	nextDirection = direction;
	prevDirection = direction;

	// 当たり判定球情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = COLLIDE_RADIUS;

	assaultTime = 0;
	shotTime = 0;
	hitPoint = 0.0f;
	vibrateTime = 0.0f;
	trunkMagnification = ASSAULT_MAGNIFICATION;
	startAssaultPosition = ZERO_VECTOR;
	force = ZERO_VECTOR;
	jumpForce = ZERO_VECTOR;

	// 初期状態を NORMAL に（後に別途行動切り替え）
	state = State::ATTACK;
	pUpdate = &Boss::UpdateAttack;

#ifdef DEBUG

#endif // DEBUG

	ChangeAttackState(AttackState::THINKING);
	// 攻撃パターンを ASSAULT に
	//attackState = AttackState::THINKING;
	//pUpdateAttack = &Boss::UpdateThinking;

	// モデルを初期位置に配置
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 非活性化処理
/// </summary>
void Boss::Deactivate()
{
}

/// <summary>
/// 更新処理
/// </summary>
void Boss::Update()
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();		// 状態ごとの更新処理
	}

	// 移動予定地に実際に移動する
	MoveFinish();
	// 当たり判定球移動
	collisionSphere.Move(position);
}

/// <summary>
/// 描画処理
/// </summary>
void Boss::Draw()
{
	// 描画しないフレームなら描画しない
	if (state == State::NONE || state == State::DEAD)
	{
		return;
	}
	
	// モデルの描画
	MV1DrawModel(modelHandle);

#ifdef DEBUG

	//当たり判定デバック描画
	//DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		//8, GetColor(0, 255, 0), 0, FALSE);

#endif // DEBUG
}

/// <summary>
/// 移動予定地に実際に移動する
/// </summary>
void Boss::MoveFinish()
{
	prevPosition = position;
	position = nextPosition;
	direction = nextDirection;

	// 位置を設定
	MV1SetPosition(modelHandle, position);

	// モデルの向きを決定
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
}

/// <summary>
/// 他のキャラクターと接触した
/// </summary>
/// <param name="forceDirection"></param>
void Boss::HitOtherCharacter(const VECTOR& forceDirection)
{
	// 跳ね返る力を設定
	//force = forceDirection;
	//force = VScale(force, FORCE_AT_DEFENSE);

	// ガードエフェクトを生成する


	// 状態を DAMAGE に
	//state = State::;
	//pUpdate = &Player::UpdatePrevent;

	// 次の行動を決定する
	ChangeAttackState(AttackState::THINKING);
	//attackState = AttackState::THINKING;
	//pUpdateAttack = &Boss::UpdateThinking;
}

/// <summary>
/// シールドに接触した
/// </summary>
/// <param name="forceDirection"></param>
void Boss::HitShield(const VECTOR& forceDirection, const bool isJust)
{
	// 跳ね返る力を設定
	force = forceDirection;
	force = VScale(force, FORCE_AT_HIT_SHIELD);

	// HitPointを減少させる
	// "ジャストガード"かどうかで減少倍率を攻撃パターンとは別に変更
	DecrementHitPoint(isJust);

	// チャージエフェクトを生成
	//effectManager->CreateEnergyEffect(position);

	// タイマーを nullptr にする
	timer = nullptr;
	// 状態を SLIDE に
	state = State::SLIDE;
	pUpdate = &Boss::UpdateSlide;
}

/// <summary>
/// 現在のステータスを返す
/// </summary>
/// <returns></returns>
const Boss::State Boss::GetCurrentState()
{
	return state;
}

/// <summary>
/// 現在のHitPointを返す
/// </summary>
/// <returns></returns>
const float Boss::GetHitPoint()
{
	return hitPoint;
}

/// <summary>
/// 当たり判定球半径を返す
/// </summary>
/// <returns></returns>
const float Boss::GetCollideRadius()
{
	return collisionSphere.radius;
}

/// <summary>
/// AttackStateに合わせて更新処理を変更する
/// </summary>
void Boss::SetNextAttackUpdate()
{
	// 各AttackStateごとに更新処理を変更する
	// さらに減少量の設定も
	switch (attackState)
	{
	case AttackState::ASSAULT:
		pUpdateAttack = &Boss::UpdateAssault;
		trunkMagnification = ASSAULT_MAGNIFICATION;
		break;
	case AttackState::BULLET:
		pUpdateAttack = &Boss::UpdateBullet;
		trunkMagnification = BULLET_MAGNIFICATION;
		break;
	case AttackState::JUMP:
		pUpdateAttack = &Boss::UpdateJump;
		break;
	case AttackState::TELEPORT:
		pUpdateAttack = &Boss::UpdateTeleport;
		break;
	case AttackState::THINKING:
		pUpdateAttack = &Boss::UpdateThinking;
		break;
	default:
		break;
	}
}

/// <summary>
/// 次のstateを決定する
/// </summary>
void Boss::SetNextAttackState()
{
	int attackStateAmount = static_cast<int>(AttackState::ATTACK_AMOUST);
	AttackState nextAttack;

	// 各数字キー入力処理
	for (int i = 0; i < attackStateAmount; ++i)
	{
		// 各AttackState に変更（キーの番号は）
		if (KeyManager::GetInstance().CheckJustPressed(i + 2))
		{
			nextAttack = static_cast<AttackState>(i);
			// 行動を決定
			ChangeAttackState(nextAttack);
			//attackState = nextAttack;
			//SetNextAttackUpdate();
		}
	}

}

/// <summary>
/// MOVE時の更新処理
/// </summary>
void Boss::UpdateMove()
{
	
}

/// <summary>
/// ATTACK時の更新処理
/// </summary>
void Boss::UpdateAttack()
{
	if (pUpdateAttack != nullptr)
	{
		(this->*pUpdateAttack)();
	}

	// 移動予定地に実際に移動する
	MoveFinish();			
}

/// <summary>
/// SLLIDE時の更新処理
/// </summary>
void Boss::UpdateSlide()
{
	// 反動処理終了後、次の行動を思考する
	if (Slide())
	{
		// 空中で防御された場合は瞬間移動して位置を修正する
		if (position.y >= 0.0f)
		{
			// 瞬間移動する
			ChangeAttackState(AttackState::TELEPORT);
			return;
		}
		// 行動思考・決定
		ChangeAttackState(AttackState::TELEPORT);
		
	}
}

/// <summary>
/// ASSAULT時の更新処理
/// </summary>
void Boss::UpdateAssault()
{
	// 規定回数まで突進を続ける
	if (assaultTime < ASSAULT_TIME)
	{
		// 一定時間振動後プレイヤーに向かって突進
		if (Vibrate())
		{
			AssaultToPlayer();
		}
		else
		{
			// プレイヤーのほうを向く
			FaceToPlayer();		
		}
	}
	// 規定回数まで突進が終わるか、地面にめり込んだら次の行動を決定する
	if(assaultTime == ASSAULT_TIME || position.y < 0.0f)
	{
		position.y = 0.0f;
		ChangeAttackState(AttackState::THINKING);
		//attackState = AttackState::THINKING;
		//pUpdateAttack = &Boss::UpdateThinking;
	}
}

/// <summary>
/// BULLET時の更新処理
/// </summary>
void Boss::UpdateBullet()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	if (timer == nullptr)
	{
		timer = new Timer(SHOT_INTERVAL);
	}
	// タイマーを更新
	timer->Update(deltaTime);

	// プレイヤーのほうを向く
	FaceToPlayer();

	// 規定回数まで発射する
	if (shotTime <= SHOT_TIME && timer->IsTimeout())
	{
		ReloadBullet();			// 弾の生成
		ShootBullet();			// 弾を発射する
		shotTime++;				// 発射回数カウント
		timer->Reset();			// タイマーをリセット
	}
	// 規定回数発射すると次の行動に移る
	else if(shotTime > SHOT_TIME)
	{
		ChangeAttackState(AttackState::THINKING);
	}

}

/// <summary>
/// JUMP時の更新処理
/// </summary>
void Boss::UpdateJump()
{
	// ジャンプし終わったら次の行動に移る
	if (Jump())
	{
		ChangeAttackState(AttackState::ASSAULT);
		//attackState = AttackState::ASSAULT;
		//pUpdateAttack = &Boss::UpdateAssault;
	}
}

/// <summary>
/// TELEPORT時の更新処理
/// </summary>
void Boss::UpdateTeleport()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	// タイマーをリセット
	if (timer == nullptr)
	{
		timer = new Timer(TELEPORT_TIME);
	}

	// タイマーを更新
	timer->Update(deltaTime);

	// State を NONE にし存在を消滅後一定時間経過後 State を ATTACK に戻す
	if (timer->IsTimeout())
	{
		// プレイヤーから一定距離の位置に瞬間移動する
		Teleport();

		// テレポートエフェクトを生成する
		effectManager->CreateTeleportEffect(position);

		state = State::ATTACK;
		ChangeAttackState(AttackState::THINKING);
		//attackState = AttackState::THINKING;
	}
	else
	{
		// ボスの状態を変更する
		if (state != State::NONE)
		{
			// テレポートエフェクトを生成する
			effectManager->CreateTeleportEffect(position);

			state = State::NONE;
		}
	}

	
}

/// <summary>
/// THINKING時の更新処理
/// </summary>
void Boss::UpdateThinking()
{
	int attackAmoust = static_cast<int>(AttackState::ATTACK_AMOUST);
	int nextAttack = Random::GetInstance().GetRandomInt(0, attackAmoust);
	AttackState nextState;

	// 各種値をリセット
	if (timer != nullptr)
	{
		timer->Reset();
	}

	assaultTime = 0;
	

#ifdef DEBUG

	// 次の行動を決定
	SetNextAttackState();
	ChangeStateInitialize();

#else

	// 前回と違う行動にする
	do
	{
		// 次の行動を決定
		nextState = static_cast<AttackState>(nextAttack);

	} while (prevAttackState != nextState);

	// 次の状態に移行する
	attackState = nextState;
	SetNextAttackUpdate();

#endif // DEBUG

	

}

/// <summary>
/// HitPointを減少させる
/// </summary>
void Boss::DecrementHitPoint(bool isJust)
{
	// 数値的には増加させているが、Playerと合わせるためにあえて減少と表現
	// HitPointを減少させる
	// "ジャストガード"時は2倍で減少させる
	if (isJust)
	{
		hitPoint += DECREMENT_HIT_POINT * trunkMagnification * IS_JUST_MAGNIFICATION;
	}
	else
	{
		hitPoint += DECREMENT_HIT_POINT * trunkMagnification;
	}

	// HitPointが底をついたらこれ以上減少しないようにする
	if (hitPoint >= 100)
	{
		hitPoint = 100.0f;
	}
}

/// <summary>
/// 状態変化時の初期化
/// </summary>
void Boss::ChangeStateInitialize()
{
	// JUMP 時の初期化処理
	if (attackState == AttackState::JUMP)
	{
		// ジャンプ力を設定
		jumpForce = JUMP_FORCE;
	}
}

// 攻撃パターン変更
void Boss::ChangeAttackState(AttackState nextState)
{
	// 攻撃パターン変更
	attackState = nextState;
	SetNextAttackUpdate();
}

/// <summary>
/// Y座標を0.0fの位置に戻す
/// </summary>
void Boss::ResetPositionYaw()
{
	
}

/// <summary>
/// プレイヤーのほうを向く
/// </summary>
void Boss::FaceToPlayer()
{
	VECTOR sub = player->GetPosition() - position;
	VECTOR inDirection = VNorm(sub);

	nextDirection = inDirection;
}

/// <summary>
/// プレイヤーに向かって突進する
/// </summary>
void Boss::AssaultToPlayer()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	VECTOR speed = direction * ASSAULT_SPEED;
	VECTOR sub = position - startAssaultPosition;
	float inDistance = VSize(sub);

	// 指定距離突進したら
	if (inDistance >= ASSAULT_DISTANCE)
	{
		// 終了する
		++assaultTime;
		// 振動時のタイマーをリセットする
		timer->Reset();
		return;
	}

	nextPosition = VAdd(nextPosition, speed * deltaTime);
	
}

/// <summary>
/// 弾を補充する
/// </summary>
void Boss::ReloadBullet()
{
	// 弾を生成可能なら生成する
	if (bulletCreater->IsCreatableCheck())
	{
		bullet = bulletCreater->Create(position, direction);
	}
}

/// <summary>
/// 弾を発射する
/// </summary>
void Boss::ShootBullet()
{
	// 弾を保持していないなら処理しない
	if (bullet == nullptr)
	{
		return;
	}

	bullet->Shoot();
}

/// <summary>
/// ジャンプさせる
/// </summary>
bool Boss::Jump()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	jumpForce.y += GRAVITY;

	// 一定高さまでジャンプしたら
	if (jumpForce.y <= 0.0f)
	{
		jumpForce = ZERO_VECTOR;

		return true;
	}

	// 移動
	nextPosition = VAdd(nextPosition, jumpForce * deltaTime);

	return false;

}

/// <summary>
/// 振動させる
/// </summary>
/// <returns></returns>
bool Boss::Vibrate()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	if (timer == nullptr)
	{
		timer = new Timer(VIBRATE_TIME);
	}
	
	float randomX = Random::GetInstance().GetRandomFloat(-200, 200);
	float randomZ = Random::GetInstance().GetRandomFloat(-200, 200);

	// ランダムな方向に移動し続ける
	VECTOR randomForce = VGet(randomX, 0.0f, randomZ);
	
	timer->Update(deltaTime);

	// 指定秒数振動させる
	if (!timer->IsTimeout())
	{

		nextPosition = prevPosition;
		position = prevPosition;

		nextPosition = VAdd(nextPosition, randomForce * deltaTime);

		// 突進開始位置を更新する
		startAssaultPosition = position;
		return false;
	}
	
	return true;
}

/// <summary>
/// プレイヤーから一定距離の位置に瞬間移動する
/// </summary>
/// <returns></returns>
bool Boss::Teleport()
{
	// プレイヤーから半径（一定距離）の場所に瞬間移動する
	VECTOR origin = player->GetPosition();
	VECTOR newPosition = origin;
	float angle = Random::GetInstance().GetRandomFloat(0.0f, 2.0f);

	// 出現位置を算出
	newPosition.x = origin.x + TELEPORT_DISTANCE * cosf(angle * DX_PI);
	newPosition.z = origin.z + TELEPORT_DISTANCE * sinf(angle * DX_PI);
	// 念のためY座標をリセットする
	newPosition.y = 0.0f;

	// 位置を設定
	nextPosition = newPosition;
	// エフェクト発生位置関係上一旦直接代入する
	position = newPosition;

	return true;
}

/// <summary>
/// 防御されたときの反動
/// </summary>
/// <returns>移動が終了した</returns>
bool Boss::Slide()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	// 摩擦力を設定
	VECTOR frictionalForce = VNorm(force);
	frictionalForce = VScale(frictionalForce, FRICTIONAL_FORCE);

	// 移動
	nextPosition = VAdd(nextPosition, force * deltaTime);
	force = VAdd(force, frictionalForce * deltaTime);

	// 跳ね返す力が0になったら終了する
	if (VSize(force) <= 0.0f)
	{
		// 状態を NORMAL に
		state = State::ATTACK;
		pUpdate = &Boss::UpdateAttack;
		return true;
	}
	return false;
}

/// <summary>
/// プレイヤーとの距離が近いか
/// </summary>
/// <returns></returns>
const bool Boss::PlayerWithRangeNear()
{
	float distance = VSize(player->GetPosition() - position);

	// プレイヤーとの距離が指定距離より近い場合は true を返す
	if (distance <= NEAR_DISTANCE)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 初期位置から離れているか
/// </summary>
/// <returns></returns>
const bool Boss::InitPosWithRangeFar()
{
	float distance = VSize(player->GetPosition() - position);

	// 初期位置から離れている場合は true を返す
	if (distance <= FAR_DISTANCE)
	{
		return true;
	}
	return false;
}
