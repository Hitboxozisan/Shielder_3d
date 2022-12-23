#include "Pch.h"
#include "CameraManager.h"
#include "CameraMain.h"
#include "KeyManager.h"
#include "DeltaTime.h"

using namespace Math3d;

const float CameraMain::INITIALIZE_RANGE_TARGET = 50.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cameraManager"></param>
CameraMain::CameraMain(CameraManager* const cameraManager)
	:CameraBase(cameraManager)
	,cameraRadius(0.0f)
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
	//float fov = CAMERA_FOV * DX_PI / 180.0f;

	position = VGet(500.0f, 100.0f, -500.0f);
	nextPosition = prevPosition = position;
	direction = VGet(0.0f, 0.0f, 1.0f);
	nextDirection = prevDirection = direction;

	targetPosition = actorPosition + VGet(0.0f, 0.0f, 100.0f);
	cameraRadius = 200.0f;
	cameraYaw = 0.0f;

	// position�̈ʒu��targetPosition�𒍎�����
	SetCameraPositionAndTarget_UpVecY(position, targetPosition);

	// FOV��ݒ�
	//SetupCamera_Perspective(fov);

	// �J�����̕`��͈͂��w��
	//SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
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
	InputAction();
	FollowTarget();
	RotateCamera();
	DebugMoveCamera();
}

/// <summary>
/// �^�[�Q�b�g��Ǐ]����
/// </summary>
void CameraMain::FollowTarget()
{
	targetPosition = actorPosition;
	position.x = targetPosition.x + cameraRadius * cosf(cameraYaw);
	position.y = 100.0f;
	position.z = targetPosition.z + cameraRadius * sinf(cameraYaw);
	SetCameraPositionAndTarget_UpVecY(position, targetPosition);
}

/// <summary>
/// �J��������]������
/// </summary>
void CameraMain::RotateCamera()
{
	
}

/// <summary>
/// ���͏���
/// </summary>
void CameraMain::InputAction()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	if (cameraYaw > 360.0f || cameraYaw < 0.0f)
	{
		cameraYaw = 0.0f;
	}

	// �J���������v���ɉ�]������
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_Q))
	{
		cameraYaw += 0.5f * deltaTime;
	}
	// �J�����𔽎��v���ɉ�]������
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_E))
	{
		cameraYaw -= 0.5f * deltaTime;
	}
}
