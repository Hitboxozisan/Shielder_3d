#include "Pch.h"
#include "Camera.h"
#include "Boss.h"
#include "DeltaTime.h"
#include "KeyManager.h"

using namespace Math3d;

const VECTOR Camera::INITIAL_POSITION = VGet(-800.0f, 3000.0f, 0.0f);
const float Camera::TARGET_DISTANCE			  = 500.0f;
const float Camera::HORIZONTAL_DISTANCE		  = 200.0f;
const float Camera::VERTICAL_DISTANCE		  = 500.0f;

const float Camera::INITIAL_CAMERA_YAW		  = 1.5f;
const float Camera::INITIAL_CAMERA_PITCH	  = 0.1f;
const float Camera::START_CAMERA_YAW		  = 0.25f;
const float Camera::START_CAMERA_DISTANCE	  = 300.0f;
const float Camera::START_ADD_DISTANCE		  = 500.0f;

const float Camera::CAMERA_DISTANCE			  = 1500.0f;
const float Camera::DISPLACE_DISTANCE		  = 100.0f;
const float Camera::ROCKON_POSSIBLE_DISTANCE  = 1200.0f;
const float Camera::ERROR_ADMISSIBLE_DISTANCE = 5.0f;
const float Camera::ROCKON_DISTANCE			  = 400.0f;
const float Camera::ROCKON_VERTICAL_DISTANCE  = 400.0f;

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
void Camera::Initialize(Boss* inBoss)
{
	boss = inBoss;

	targetDistance = TARGET_DISTANCE;
	horizontalDistance = HORIZONTAL_DISTANCE;
	verticalDistance = VERTICAL_DISTANCE;
	cameraRadius = CAMERA_DISTANCE;
	cameraYaw = INITIAL_CAMERA_YAW;
	cameraPitch = INITIAL_CAMERA_PITCH;
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
	cameraRadius = START_CAMERA_DISTANCE;
	position = INITIAL_POSITION;
	actorPosition = inPlayerPos;

	cameraYaw = INITIAL_CAMERA_YAW;
	cameraPitch = INITIAL_CAMERA_PITCH;

#ifdef DEBUG
	cameraRadius = CAMERA_DISTANCE;
	cameraYaw = 1.5f;
	cameraPitch = -1.5f;
#endif // DEBUG


	isMoveInitialPosition = false;
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
	// 演出が終わるまで更新処理に入らない
	/*if (!UpdateGameStart(inPlayerPos))
	{
		return;
	}*/

	UpdatePosition(inPlayerPos, inEnemyPos);		// actor と enemy の現在地を更新
	CalculatingCamerePos();							// カメラの位置を設定
	//CalculatingTagetPos();						// 注視点の位置を設定
	//RotateCamera();								// カメラを回転させる
	TargetRockon();									// ロックオン対象を見る
	InputAction();									// 入力処理

	// カメラの位置と向きを設定
	SetCameraPositionAndTarget_UpVecY(position, actorPosition);
	//SetCameraPositionAndTargetAndUpVec(position, actorPosition, VGet(0.0f, 1.0f, 0.0f));

	Effekseer_Sync3DSetting();						// DXライブラリのカメラとEffekseerのカメラを同期する
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
/// 初期位置にカメラが移動したか
/// </summary>
/// <returns></returns>
const bool Camera::IsMovedCameraToInitialPosition()
{
	return isMoveInitialPosition;
}

/// <summary>
/// ゲーム開始時の演出用更新処理
/// </summary>
/// <param name="inPlayerPos">プレイヤーの位置</param>
bool Camera::UpdateGameStart(VECTOR inPlayerPos)
{
	// プレイヤーの周囲を一回転する
	if (RotateCamera())
	{
		// カメラの位置をゲーム中の位置に変更する
		if(MoveCameraToInitialPosition())
		{
			isMoveInitialPosition = true;
			return true;
		}
	}
	// actor と enemyの現在位置の更新（これはいらないと思う）
	UpdatePosition(inPlayerPos, ZERO_VECTOR);
	// カメラの位置を更新
	CalculatingCamerePos();

	TargetRockon();
	
	// カメラの位置と向きを設定
	SetCameraPositionAndTarget_UpVecY(position, actorPosition);
	// DXライブラリのカメラとEffekseerのカメラを同期する
	Effekseer_Sync3DSetting();						
	return false;
}

/// <summary>
/// カメラを初期位置に移動する
/// </summary>
bool Camera::MoveCameraToInitialPosition()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	
	// 初期位置に移動したら終了する
	if (cameraRadius >= CAMERA_DISTANCE &&
		cameraPitch >= 0.3f)
	{
		
		return true;
	}
	else
	{
		cameraRadius += START_ADD_DISTANCE * deltaTime;
		// 初期角度になったらやめる
		if (cameraPitch <= 0.3f)
		{
			cameraPitch += 0.1f * deltaTime;
		}
	}

	return false;
}

/// <summary>
/// actor と enemy の現在位置の更新
/// </summary>
void Camera::UpdatePosition(VECTOR inPlayerPos, VECTOR inEnemyPos)
{
	// 前フレームの位置と違った場合更新する
	if (actorPosition != inPlayerPos)
	{
		actorPosition = inPlayerPos;
	}
	// ある程度の誤差は追わないようにする
	if (VSize(inEnemyPos - enemyPosition) >= ERROR_ADMISSIBLE_DISTANCE)
	{
		enemyPosition = inEnemyPos;
	}
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
		position.x = targetPosition.x + cameraRadius * cosf(cameraYaw * DX_PI);
		position.z = targetPosition.z + cameraRadius * sinf(cameraYaw * DX_PI);
		position.y = cameraRadius * sinf(cameraPitch * DX_PI);
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
bool Camera::RotateCamera()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	// カメラがプレイヤーの周囲を一回転したら
	if (cameraYaw >= 3.5f)
	{
		return true;
	}

	cameraYaw += START_CAMERA_YAW * deltaTime * DX_PI;
	
	return false;
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
	if (ROCKON_POSSIBLE_DISTANCE >= range && 
		isRockOn &&
		boss->GetCurrentState() != Boss::State::NONE)
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
		cameraYaw += 1.5f * deltaTime * DX_PI;
	}
	// カメラを反時計回りに回転させる
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_E))
	{
		cameraYaw -= 1.5f * deltaTime * DX_PI;
	}
	// カメラ位置を高くする
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_I))
	{
		cameraPitch += 0.5f * deltaTime * DX_PI;
	}
	// カメラ位置を低くする
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_K))
	{
		cameraPitch -= 0.5f * deltaTime * DX_PI;
	}
}
