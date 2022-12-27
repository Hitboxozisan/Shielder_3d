#include "Pch.h"
#include "CameraManager.h"
#include "CameraMain.h"
#include "KeyManager.h"
#include "DeltaTime.h"

using namespace Math3d;

const float CameraMain::INITIALIZE_RANGE_TARGET = 50.0f;
const float CameraMain::RANGE_POSSIBLE_ROCKON = 100.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cameraManager"></param>
CameraMain::CameraMain(CameraManager* const cameraManager)
	:CameraBase(cameraManager)
	,cameraRadius(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
CameraMain::~CameraMain()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void CameraMain::Initialize()
{
	//float fov = CAMERA_FOV * DX_PI / 180.0f;

	position = VGet(500.0f, 100.0f, -500.0f);
	nextPosition = prevPosition = position;
	direction = VGet(0.0f, 0.0f, 1.0f);
	nextDirection = prevDirection = direction;

	targetPosition = actorPosition + VGet(0.0f, 0.0f, 100.0f);
	cameraRadius = 500.0f;
	cameraYaw = 0.0f;
	cameraPitch = 0.0f;

	// positionの位置でtargetPositionを注視する
	SetCameraPositionAndTarget_UpVecY(position, targetPosition);

	// FOVを設定
	//SetupCamera_Perspective(fov);

	// カメラの描画範囲を指定
	//SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
}

/// <summary>
/// 終了処理
/// </summary>
void CameraMain::Fainalize()
{
}

/// <summary>
/// 活性化処理
/// </summary>
void CameraMain::Activate()
{
}

/// <summary>
/// 非活性化処理
/// </summary>
void CameraMain::Deactivate()
{
}

/// <summary>
/// 更新処理
/// </summary>
void CameraMain::Update()
{
	MoveFinish();
	InputAction();
	FollowTarget();
	RotateCamera();
	DebugMoveCamera();
}

/// <summary>
/// ターゲットを追従する
/// </summary>
void CameraMain::FollowTarget()
{
	
}

/// <summary>
/// カメラを回転させる
/// </summary>
void CameraMain::RotateCamera()
{
	targetPosition = actorPosition;

	position.x = targetPosition.x + cameraRadius * cosf(cameraYaw);
	//position.y = 50.0f;
	position.z = targetPosition.z + cameraRadius * sinf(cameraYaw);

	//position.x = position.x * cosf(cameraPitch);
	position.y = cameraRadius * sinf(cameraPitch);
	//position.z = position.z * cosf(cameraPitch);

	SetCameraPositionAndTarget_UpVecY(position, targetPosition);
}

/// <summary>
/// 入力処理
/// </summary>
void CameraMain::InputAction()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	if (cameraYaw > 360.0f || cameraYaw < 0.0f)
	{
		//cameraYaw = 0.0f;
	}

	// カメラを時計回りに回転させる
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_Q))
	{
		cameraYaw += 0.5f * deltaTime;
	}
	// カメラを反時計回りに回転させる
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_E))
	{
		cameraYaw -= 0.5f * deltaTime;
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
