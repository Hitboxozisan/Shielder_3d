#include "Pch.h"
#include "Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cameraManager"></param>
Camera::Camera(CameraManager* const cameraManager)
	:parent(cameraManager)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{

}

/// <summary>
/// ���ʔԍ���Ԃ�
/// </summary>
/// <returns>���ʔԍ�</returns>
int Camera::GetId()
{
	return id;
}
