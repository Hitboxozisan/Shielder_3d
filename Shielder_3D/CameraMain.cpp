#include "Pch.h"
#include "CameraManager.h"
#include "CameraMain.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cameraManager"></param>
CameraMain::CameraMain(CameraManager* const cameraManager)
	:CameraBase(cameraManager)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CameraMain::~CameraMain()
{
}

/// <summary>
/// ����������
/// </summary>
void CameraMain::Initialize()
{
	position = VGet(500.0f, 100.0f, 0.0f);
	nextPosition = prevPosition = position;
	direction = VGet(0.0f, 0.0f, 1.0f);
	nextDirection = prevDirection = direction;
}

/// <summary>
/// �I������
/// </summary>
void CameraMain::Fainalize()
{
}

/// <summary>
/// ����������
/// </summary>
void CameraMain::Activate()
{
}

/// <summary>
/// �񊈐�������
/// </summary>
void CameraMain::Deactivate()
{
}

/// <summary>
/// �X�V����
/// </summary>
void CameraMain::Update()
{
	MoveFinish();
	DebugMoveCamera();
}
