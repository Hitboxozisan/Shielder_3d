#include "Pch.h"
#include "Camera.h"
#include "DeltaTime.h"
#include "KeyManager.h"

using namespace Math3d;

const float Camera::TARGET_DISTANCE			 = 500.0f;
const float Camera::HORIZONTAL_DISTANCE		 = 200.0f;
const float Camera::VERTICAL_DISTANCE		 = 500.0f;
const float Camera::CAMERA_DISTANCE			 = 500.0f;
const float Camera::DISPLACE_DISTANCE		 = 100.0f;
const float Camera::ROCKON_POSSIBLE_DISTANCE = 2000.0f;
const float Camera::ROCKON_DISTANCE			 = 400.0f;
const float Camera::ROCKON_VERTICAL_DISTANCE = 400.0f;

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Camera::Initialize()
{
	targetDistance = TARGET_DISTANCE;
	horizontalDistance = HORIZONTAL_DISTANCE;
	verticalDistance = VERTICAL_DISTANCE;
	cameraRadius = CAMERA_DISTANCE;
	cameraYaw = 0.0f;
	cameraPitch = 1.0f;
	rockOnDistance = ROCKON_DISTANCE;

	isRockOn = false;

	// 初期位置に配置
	position = ZERO_VECTOR;
}

/// <summary>
/// 終了処理
/// </summary>
void Camera::Finalize()
{
}

/// <summary>
/// 活性化処理
/// </summary>
/// <param name="inPlayerPos"></param>
/// <param name="inEnemyPos"></param>
void Camera::Activate(VECTOR inPlayerPos, VECTOR inEnemyPos)
{
	position = inPlayerPos;
	actorPosition = inPlayerPos;
}

/// <summary>
/// 非活性化処理
/// </summary>
void Camera::Deactivate()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="inPlayerPos"></param>
/// <param name="inEnemyPos"></param>
void Camera::Update(VECTOR inPlayerPos, VECTOR inEnemyPos)
{
	Effekseer_Sync3DSetting();						// DXライブラリのカメラとEffekseerのカメラを同期する
	UpdatePosition(inPlayerPos, inEnemyPos);		// actor と enemy の現在地を更新
	CalculatingCamerePos();							// カメラの位置を設定
	//CalculatingTagetPos();						// 注視点の位置を設定
	//RotateCamera();								// カメラを回転させる
	TargetRockon();									// ロックオン対象を見る
	InputAction();									// 入力処理

	// カメラの位置と向きを設定
	SetCameraPositionAndTarget_UpVecY(position, targetPosition);
}

/// <summary>
/// カメラを切り替える（追従・ロックオン）
/// </summary>
void Camera::ChangeCamera()
{
	if (isRockOn)
	{
		isRockOn = false;
		return;
	}
	else
	{
		isRockOn = true;
	}
}

/// <summary>
/// 現在位置を返す
/// </summary>
/// <returns></returns>
VECTOR Camera::GetPosition()
{
	return position;
}

/// <summary>
/// 現在の注視点を返す
/// </summary>
/// <returns></returns>
VECTOR Camera::GetTargetPosition()
{
	return targetPosition;
}

/// <summary>
/// ロックオン中か
/// </summary>
/// <returns>ロックオンしている</returns>
bool Camera::IsRockOn()
{
	if (isRockOn)
	{
		return true;
	}
	return false;
}


/// <summary>
/// actor と enemy の現在位置の更新
/// </summary>
void Camera::UpdatePosition(VECTOR inPlayerPos, VECTOR inEnemyPos)
{
	actorPosition = inPlayerPos;
	enemyPosition = inEnemyPos;
}

/// <summary>
/// カメラの位置を計算
/// </summary>
void Camera::CalculatingCamerePos()
{
	VECTOR pos = actorPosition - enemyPosition;
	float distance = VSize(pos);
	// ロックオンしている場合は敵とプレイヤーをカメラに収める
	if (isRockOnPossible())
	{
		// カメラの高さを一定にするため y成分を0にする
		pos.y = 0.0f;
		// ベクトルの正規化
		pos = VNorm(pos);
		pos = VScale(pos, ROCKON_DISTANCE);
		pos.y = ROCKON_VERTICAL_DISTANCE;
		position = actorPosition + pos;

	}
	// ロックオンしていない場合はプレイヤーを追従する
	else
	{
		position.x = targetPosition.x + cameraRadius * cosf(cameraYaw);
		//position.y = 50.0f;
		position.z = targetPosition.z + cameraRadius * sinf(cameraYaw);
		//position.x = position.x * cosf(cameraPitch);
		position.y = cameraRadius * sinf(cameraPitch);
		//position.z = position.z * cosf(cameraPitch);
	}
	

}

/// <summary>
/// 注視点の位置を計算
/// </summary>
void Camera::CalculatingTagetPos()
{
	VECTOR dir = actorPosition - position;
	// 正規化
	dir = VNorm(dir);

	//targetPosition = actorPosition + VScale(dir, targetDistance);
}

/// <summary>
/// カメラを回転させる
/// </summary>
void Camera::RotateCamera()
{
	
}

// ロックオン対象を見る
void Camera::TargetRockon()
{
	if (isRockOnPossible() && isRockOn)
	{
		targetPosition = enemyPosition;
	}
	else
	{
		// ロックオンしていない場合はプレイヤーを注視する
		targetPosition = actorPosition;
	}
}

/// <summary>
/// ロックオン可能か
/// </summary>
/// <returns></returns>
bool Camera::isRockOnPossible()
{
	float range = VSize(enemyPosition - actorPosition);
	// ロックオン可能距離内なら
	if (ROCKON_POSSIBLE_DISTANCE >= range && isRockOn)
	{
		return true;
	}
	// ロックオン中に範囲外に出た時のためフラグを false にする
	else
	{
		isRockOn = false;
		return false;
	}
	
}

/// <summary>
/// 入力処理
/// </summary>
void Camera::InputAction()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	if (cameraYaw > 360.0f || cameraYaw < 0.0f)
	{
		//cameraYaw = 0.0f;
	}

	// カメラを時計回りに回転させる
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_Q))
	{
		cameraYaw += 1.5f * deltaTime;
	}
	// カメラを反時計回りに回転させる
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_E))
	{
		cameraYaw -= 1.5f * deltaTime;
	}
	// カメラ位置を高くする
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_I))
	{
		cameraPitch += 0.5f * deltaTime;
	}
	// カメラ位置を低くする
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_K))
	{
		cameraPitch -= 0.5f * deltaTime;
	}
}
