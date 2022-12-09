#include "Pch.h"
#include "CameraManager.h"
#include "CameraMain.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cameraManager"></param>
CameraMain::CameraMain(CameraManager* const cameraManager)
	:CameraBase(cameraManager)
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
	position = VGet(500.0f, 100.0f, 0.0f);
	nextPosition = prevPosition = position;
	direction = VGet(0.0f, 0.0f, 1.0f);
	nextDirection = prevDirection = direction;
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
	DebugMoveCamera();
}
