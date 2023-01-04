//----------------------------------------------------------------
// <不具合・バグ>
// ・
// <note>
// ・ロックオン時モデルの透過率0%だと敵が隠れるためカメラの調節か、
// 　盾の透過率を上げる必要がある
//----------------------------------------------------------------

#include "Pch.h"
#include "Shield.h"

#include "ModelManager.h"

const VECTOR Shield::INITIAL_SCALE					  = VGet(0.5f, 0.5f, 0.5f);
const float Shield::MAX_HITPOINT					  = 100.0f;
const float Shield::SCALE_BY_DIRECTION_FOR_CORRECTION = 150.0f;
const float Shield::COLLIDE_RADIUS					  = 50.0f;
const float Shield::COLLIDE_HEIGHT					  = 125.0f;

/// <summary>
/// コンストラクタ
/// </summary>
Shield::Shield()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Shield::~Shield()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Shield::Initialize()
{
	hitPoint = MAX_HITPOINT;
	// モデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::SHIELD));
	MV1SetScale(modelHandle, INITIAL_SCALE);
}

/// <summary>
/// 終了処理
/// </summary>
void Shield::Finalize()
{

}

/// <summary>
/// 活性化処理
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
/// <param name="inPrevDirection"></param>
void Shield::Activate(const VECTOR& inPosition,
					  const VECTOR& inDirection, 
					  const VECTOR& inPrevDirection)
{
	state = State::DEPLOYMENT;

	position = inPosition;
	direction = inDirection;
	distanceToPlayer = VScale(inPrevDirection, SCALE_BY_DIRECTION_FOR_CORRECTION);

	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = COLLIDE_RADIUS;

	MV1SetPosition(modelHandle, position);					// モデルの位置を設定
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);	// 盾の向きを設定

	pUpdate = &Shield::UpdateDeployment;
}

/// <summary>
/// 非活性化処理
/// </summary>
void Shield::Deactivate()
{
	state = State::NONE;
	pUpdate = nullptr;
}

/// <summary>
/// 更新処理
/// </summary>
void Shield::Update()
{
	// 存在しないなら処理しない
	if (state == State::NONE)
	{
		return;
	}

	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();		// 状態ごとの更新処理
	}

	collisionSphere.Move(position);
}

/// <summary>
/// 描画処理
/// </summary>
void Shield::Draw()
{
	// 存在しないなら処理しない
	if (state == State::NONE)
	{
		return;
	}

	// モデルの描画
	MV1DrawModel(modelHandle);

#ifdef DEBUG
	//当たり判定デバック描画
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		32, GetColor(0, 255, 0), 0, FALSE);

#endif // DEBUG

}

/// <summary>
/// 他のキャラクターと接触した
/// </summary>
/// <param name="forceDirection"></param>
void Shield::HitOtherCharacter()
{


}

/// <summary>
/// 当たり判定球半径を返す
/// </summary>
/// <returns></returns>
const float Shield::GetCollideRadius()
{
	return collisionSphere.radius;
}

/// <summary>
/// 位置をセット
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
/// <param name="inPrevDirection"></param>
void Shield::SetShieldPosition(const VECTOR& inPosition, const VECTOR& inDirection, const VECTOR& inPrevDirection)
{
	position = inPosition;
	direction = inDirection;
	distanceToPlayer = VScale(direction, SCALE_BY_DIRECTION_FOR_CORRECTION);
	position = VAdd(position, distanceToPlayer);
	// 当たり判定球の高さを調節する
	collisionSphere.worldCenter.y = COLLIDE_HEIGHT;
}

/// <summary>
/// 実際に移動する
/// </summary>
void Shield::MoveFinish()
{
	// モデルの位置を設定
	MV1SetPosition(modelHandle, position);
	// モデルの向きを設定
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
}

/// <summary>
/// DEPLOYMENT時更新処理
/// </summary>
void Shield::UpdateDeployment()
{
	MoveFinish();
}

/// <summary>
/// DESTRUCTION時更新処理
/// </summary>
void Shield::UpdateDestruction()
{

}
