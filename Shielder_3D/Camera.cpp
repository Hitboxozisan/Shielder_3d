#include "Pch.h"
#include "Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cameraManager"></param>
Camera::Camera(CameraManager* const cameraManager)
	:parent(cameraManager)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{

}

/// <summary>
/// 識別番号を返す
/// </summary>
/// <returns>識別番号</returns>
int Camera::GetId()
{
	return id;
}
