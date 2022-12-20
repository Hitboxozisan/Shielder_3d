#include "Pch.h"
#include "CameraManager.h"

#include "CameraMain.h"
#include "CameraLockOn.h"
#include "Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
CameraManager::CameraManager()
	:eachCameras()
	,currentPointer(nullptr)
	,currentCamera()
	,nextCamera()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
CameraManager::~CameraManager()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void CameraManager::Initialize()
{
	eachCameras[MAIN] = new CameraMain(this);
	eachCameras[LOCK_ON] = new CameraLockOn(this);

	// 各カメラの初期化処理
	for (int i = 0; i < Camera::CAMERA_AMOUNT; ++i)
	{
		eachCameras[i]->Initialize();
	}

	currentCamera = nextCamera = MAIN;
	currentPointer = eachCameras[currentCamera];
	currentPointer->Activate();
}

/// <summary>
/// 終了処理
/// </summary>
void CameraManager::Finalize()
{
	for (int i = 0; i < CameraManager::CAMERA_AMOUNT; ++i)
	{
		eachCameras[i]->Fainalize();
		delete eachCameras[i];
		eachCameras[i] = nullptr;
	}
}

/// <summary>
/// 更新処理
/// </summary>
void CameraManager::Update()
{
	if (currentCamera != nextCamera)
	{
		ChangeCamera();		// 変更先カメラに変更する
	}

	if (currentPointer != nullptr)
	{
		currentPointer->Update();		// 現在のカメラの更新処理
	}
}

void CameraManager::SetTargetPosition(VECTOR inPosition)
{
	currentPointer->SetTargetPosition(inPosition);
}

/// <summary>
/// 次のカメラをセットする
/// </summary>
void CameraManager::SetNextCamera(Camera next)
{
	nextCamera = next;
}

/// <summary>
/// カメラの向きを返す
/// </summary>
VECTOR CameraManager::GetDirection()
{
	VECTOR dir = currentPointer->GetDirection();
	return dir;
}


/// <summary>
/// 現在のカメラを返す
/// </summary>
//Camera CameraManager::GetCurrentCamera()
//{
//	return currentCamera;
//}


/// <summary>
/// カメラを切り替える
/// </summary>
void CameraManager::ChangeCamera()
{
	currentPointer->Deactivate();
	currentPointer = eachCameras[nextCamera];
	currentCamera = nextCamera;
	currentPointer->Activate();
}
