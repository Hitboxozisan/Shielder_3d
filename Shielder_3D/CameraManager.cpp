#include "Pch.h"
#include "CameraManager.h"

#include "CameraMain.h"
#include "CameraLockOn.h"
#include "Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CameraManager::CameraManager()
	:eachCameras()
	,currentPointer(nullptr)
	,currentCamera()
	,nextCamera()
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CameraManager::~CameraManager()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void CameraManager::Initialize()
{
	eachCameras[MAIN] = new CameraMain(this);
	eachCameras[LOCK_ON] = new CameraLockOn(this);

	// �e�J�����̏���������
	for (int i = 0; i < Camera::CAMERA_AMOUNT; ++i)
	{
		eachCameras[i]->Initialize();
	}

	currentCamera = nextCamera = MAIN;
	currentPointer = eachCameras[currentCamera];
	currentPointer->Activate();
}

/// <summary>
/// �I������
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
/// �X�V����
/// </summary>
void CameraManager::Update()
{
	if (currentCamera != nextCamera)
	{
		ChangeCamera();		// �ύX��J�����ɕύX����
	}

	if (currentPointer != nullptr)
	{
		currentPointer->Update();		// ���݂̃J�����̍X�V����
	}
}

void CameraManager::SetTargetPosition(VECTOR inPosition)
{
	currentPointer->SetTargetPosition(inPosition);
}

/// <summary>
/// ���̃J�������Z�b�g����
/// </summary>
void CameraManager::SetNextCamera(Camera next)
{
	nextCamera = next;
}

/// <summary>
/// �J�����̌�����Ԃ�
/// </summary>
VECTOR CameraManager::GetDirection()
{
	VECTOR dir = currentPointer->GetDirection();
	return dir;
}


/// <summary>
/// ���݂̃J������Ԃ�
/// </summary>
//Camera CameraManager::GetCurrentCamera()
//{
//	return currentCamera;
//}


/// <summary>
/// �J������؂�ւ���
/// </summary>
void CameraManager::ChangeCamera()
{
	currentPointer->Deactivate();
	currentPointer = eachCameras[nextCamera];
	currentCamera = nextCamera;
	currentPointer->Activate();
}
