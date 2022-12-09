#include "Pch.h"
#include "CameraBase.h"

#include "DeltaTime.h"
#include "KeyManager.h"

using namespace Math3d;

const float CameraBase::SPEED = 100.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cameraManager"></param>
CameraBase::CameraBase(CameraManager* const cameraManager)
	:parent(cameraManager)
	,id(0)
	,position(ZERO_VECTOR)
	,nextPosition(ZERO_VECTOR)
	,prevPosition(ZERO_VECTOR)
	,direction(ZERO_VECTOR)
	,nextDirection(ZERO_VECTOR)
	,prevDirection(ZERO_VECTOR)
	,speed(SPEED)
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CameraBase::~CameraBase()
{
	// �����Ȃ�
}

/// <summary>
/// �ړ��\��n�Ɏ��ۂɈړ�����
/// </summary>
void CameraBase::MoveFinish()
{
	// �ړ����Ă���Ȃ�O�t���[���̌������X�V����
	if (direction != ZERO_VECTOR)
	{
		prevDirection = direction;
	}

	prevPosition = position;
	position = nextPosition;
	direction = nextDirection;

	// 
	SetCameraPositionAndAngle(position, 0, 0, 0);
}

/// <summary>
/// ���ʔԍ���Ԃ�
/// </summary>
/// <returns>���ʔԍ�</returns>
const int CameraBase::GetId() const
{
	return id;
}

/// <summary>
/// ���݈ʒu��Ԃ�
/// </summary>
/// <returns></returns>
const VECTOR CameraBase::GetPosition() const
{
	return position;
}

/// <summary>
/// ���݂̌�����Ԃ�
/// </summary>
/// <returns></returns>
const VECTOR CameraBase::GetDirection() const
{
	return direction;
}

/// <summary>
/// �J�����̈ʒu�E�����𓮂���
/// </summary>
void CameraBase::DebugMoveCamera()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	// �O�㍶�E�ړ�
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_I))
	{
		nextPosition += PROGRESS * speed * deltaTime;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_K))
	{
		nextPosition += RECESSION * speed * deltaTime;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_J))
	{
		nextPosition += LEFT * speed * deltaTime;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_L))
	{
		nextPosition += RIGHT * speed * deltaTime;
	}
	// �㉺�ړ�
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_I) &&
		KeyManager::GetInstance().CheckPressed(KEY_INPUT_LSHIFT))
	{
		nextPosition += UP * speed * deltaTime;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_I) &&
		KeyManager::GetInstance().CheckPressed(KEY_INPUT_LSHIFT))
	{
		nextPosition += DOWN * speed * deltaTime;
	}

	// �J�����̌����ύX
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_UP))
	{
		nextDirection += PROGRESS * speed * deltaTime;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_DOWN))
	{
		nextDirection += RECESSION * speed * deltaTime;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_LEFT))
	{
		nextDirection += LEFT * speed * deltaTime;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_RIGHT))
	{
		nextDirection += RIGHT * speed * deltaTime;
	}
}
