//----------------------------------------------------------------
// <不具合・バグ>
// ・
// <note>
// ・振動時ロックオンだとわかりにくいある程度の誤差は追わないようにするべきか？
//----------------------------------------------------------------

#include "Pch.h"
#include "Boss.h"
#include "Player.h"
#include "ModelManager.h"
#include "Random.h"
#include "Timer.h"
#include "DeltaTime.h"

using namespace My3dLib;
using namespace Math3d;

const VECTOR Boss::INITIAL_POSITION    = VGet(500.0f, 0.0f, 500.0f);
const VECTOR Boss::INITIAL_DIRECTION   = VGet(0.0f, 0.0f, -1.0f);
const VECTOR Boss::INITIAL_SCALE       = VGet(0.5f, 0.5f, 0.5f);
const float  Boss::FRICTIONAL_FORCE    = -0.1f;
const float  Boss::FORCE_AT_HIT_SHIELD = 3.0f;
const float  Boss::COLLIDE_RADIUS      = 100.0f;
const float  Boss::VIBRATE_TIME		   = 2.0f;
const float  Boss::ASSAULT_SPEED	   = 10.0f;
const float  Boss::ASSAULT_DISTANCE    = 1000.0f;
const int    Boss::ASSAULT_TIME		   = 8;

/// <summary>
/// コンストラクタ
/// </summary>
Boss::Boss(Player* inPlayer)
	:player(inPlayer)
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
void Boss::Initialize()
{
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
	vibrateTime = 0.0f;
	movedDistance = 0.0f;
	startAssaultPosition = ZERO_VECTOR;

	// 初期状態を NORMAL に（後に別途行動切り替え）
	state = State::ATTACK;
	pUpdate = &Boss::UpdateAttack;

	// 攻撃パターンを ASSAULT に
	attackState = AttackState::ASSAULT;
	pUpdateAttack = &Boss::UpdateAssault;

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
	if (state == State::DEAD)
	{
		return;
	}
	
	// モデルの描画
	MV1DrawModel(modelHandle);

#ifdef DEBUG

	//当たり判定デバック描画
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		8, GetColor(0, 255, 0), 0, FALSE);

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
}

/// <summary>
/// シールドに接触した
/// </summary>
/// <param name="forceDirection"></param>
void Boss::HitShield(const VECTOR& forceDirection)
{
	// 跳ね返る力を設定
	force = forceDirection;
	force = VScale(force, FORCE_AT_HIT_SHIELD);


	// 状態を DAMAGE に
	state = State::SLIDE;
	pUpdate = &Boss::UpdateSlide;
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
void Boss::SetNextAttackState()
{
	switch (attackState)
	{
	case AttackState::ASSAULT:
		pUpdate = &Boss::UpdateAssault;
		break;
	case AttackState::JUMP:
		pUpdate = &Boss::UpdateJump;
		break;

	default:
		break;
	}
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
		state = State::ATTACK;
		pUpdateAttack = &Boss::UpdateThinking;
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
}

/// <summary>
/// JUMP時の更新処理
/// </summary>
void Boss::UpdateJump()
{

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
	assaultTime = 0;

	// 前回と違う行動にする
	do
	{
		// 次の行動を決定
		nextState = static_cast<AttackState>(nextAttack);

	} while (prevAttackState != nextState);

	// 次の状態に移行する
	attackState = nextState;
	SetNextAttackState();

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
	VECTOR speed = direction * ASSAULT_SPEED;
	VECTOR sub = position - startAssaultPosition;
	float inDistance = VSize(sub);

	if (inDistance >= ASSAULT_DISTANCE)
	{
		// 終了する
		++assaultTime;
		// 振動時のタイマーをリセットする
		timer->Reset();
		return;
	}

	nextPosition = VAdd(nextPosition, speed);
	
}

/// <summary>
/// ジャンプさせる
/// </summary>
void Boss::Jump()
{

}

/// <summary>
/// 振動させる
/// </summary>
/// <returns></returns>
bool Boss::Vibrate()
{
	if (timer == nullptr)
	{
		timer = new Timer(VIBRATE_TIME);
	}

	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	
	float randomX = Random::GetInstance().GetRandomFloat(-2, 2);
	float randomZ = Random::GetInstance().GetRandomFloat(-2, 2);

	// ランダムな方向に移動し続ける
	VECTOR randomForce = VGet(randomX, 0.0f, randomZ);
	nextPosition = prevPosition;
	position = prevPosition;
	
	timer->Update(deltaTime);

	// 指定秒数振動させる
	if (!timer->IsTimeout())
	{
		nextPosition = VAdd(nextPosition, randomForce);
		// 突進開始位置を更新する
		startAssaultPosition = position;
		return false;
	}
	
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

	nextPosition = VAdd(nextPosition, force);
	force = VAdd(force, frictionalForce);

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
