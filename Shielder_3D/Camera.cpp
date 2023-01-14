#include "Pch.h"
#include "Camera.h"
#include "DeltaTime.h"
#include "KeyManager.h"

using namespace Math3d;

const float Camera::TARGET_DISTANCE			 = 500.0f;
const float Camera::HORIZONTAL_DISTANCE		 = 200.0f;
const float Camera::VERTICAL_DISTANCE		 = 500.0f;
const float Camera::CAMERA_DISTANCE			 = 500.0f;
const float Camera::DISPLACE_DISTANCE		 = 100.0f;
const float Camera::ROCKON_POSSIBLE_DISTANCE = 2000.0f;
const float Camera::ROCKON_DISTANCE			 = 400.0f;
const float Camera::ROCKON_VERTICAL_DISTANCE = 400.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Camera::Initialize()
{
	targetDistance = TARGET_DISTANCE;
	horizontalDistance = HORIZONTAL_DISTANCE;
	verticalDistance = VERTICAL_DISTANCE;
	cameraRadius = CAMERA_DISTANCE;
	cameraYaw = 0.0f;
	cameraPitch = 1.0f;
	rockOnDistance = ROCKON_DISTANCE;

	isRockOn = false;

	// �����ʒu�ɔz�u
	position = ZERO_VECTOR;
}

/// <summary>
/// �I������
/// </summary>
void Camera::Finalize()
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="inPlayerPos"></param>
/// <param name="inEnemyPos"></param>
void Camera::Activate(VECTOR inPlayerPos, VECTOR inEnemyPos)
{
	position = inPlayerPos;
	actorPosition = inPlayerPos;
}

/// <summary>
/// �񊈐�������
/// </summary>
void Camera::Deactivate()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="inPlayerPos"></param>
/// <param name="inEnemyPos"></param>
void Camera::Update(VECTOR inPlayerPos, VECTOR inEnemyPos)
{
	Effekseer_Sync3DSetting();						// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����
	UpdatePosition(inPlayerPos, inEnemyPos);		// actor �� enemy �̌��ݒn���X�V
	CalculatingCamerePos();							// �J�����̈ʒu��ݒ�
	//CalculatingTagetPos();						// �����_�̈ʒu��ݒ�
	//RotateCamera();								// �J��������]������
	TargetRockon();									// ���b�N�I���Ώۂ�����
	InputAction();									// ���͏���

	// �J�����̈ʒu�ƌ�����ݒ�
	SetCameraPositionAndTarget_UpVecY(position, targetPosition);
}

/// <summary>
/// �J������؂�ւ���i�Ǐ]�E���b�N�I���j
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
/// ���݈ʒu��Ԃ�
/// </summary>
/// <returns></returns>
VECTOR Camera::GetPosition()
{
	return position;
}

/// <summary>
/// ���݂̒����_��Ԃ�
/// </summary>
/// <returns></returns>
VECTOR Camera::GetTargetPosition()
{
	return targetPosition;
}

/// <summary>
/// ���b�N�I������
/// </summary>
/// <returns>���b�N�I�����Ă���</returns>
bool Camera::IsRockOn()
{
	if (isRockOn)
	{
		return true;
	}
	return false;
}


/// <summary>
/// actor �� enemy �̌��݈ʒu�̍X�V
/// </summary>
void Camera::UpdatePosition(VECTOR inPlayerPos, VECTOR inEnemyPos)
{
	actorPosition = inPlayerPos;
	enemyPosition = inEnemyPos;
}

/// <summary>
/// �J�����̈ʒu���v�Z
/// </summary>
void Camera::CalculatingCamerePos()
{
	VECTOR pos = actorPosition - enemyPosition;
	float distance = VSize(pos);
	// ���b�N�I�����Ă���ꍇ�͓G�ƃv���C���[���J�����Ɏ��߂�
	if (isRockOnPossible())
	{
		// �J�����̍��������ɂ��邽�� y������0�ɂ���
		pos.y = 0.0f;
		// �x�N�g���̐��K��
		pos = VNorm(pos);
		pos = VScale(pos, ROCKON_DISTANCE);
		pos.y = ROCKON_VERTICAL_DISTANCE;
		position = actorPosition + pos;

	}
	// ���b�N�I�����Ă��Ȃ��ꍇ�̓v���C���[��Ǐ]����
	else
	{
		position.x = targetPosition.x + cameraRadius * cosf(cameraYaw);
		//position.y = 50.0f;
		position.z = targetPosition.z + cameraRadius * sinf(cameraYaw);
		//position.x = position.x * cosf(cameraPitch);
		position.y = cameraRadius * sinf(cameraPitch);
		//position.z = position.z * cosf(cameraPitch);
	}
	

}

/// <summary>
/// �����_�̈ʒu���v�Z
/// </summary>
void Camera::CalculatingTagetPos()
{
	VECTOR dir = actorPosition - position;
	// ���K��
	dir = VNorm(dir);

	//targetPosition = actorPosition + VScale(dir, targetDistance);
}

/// <summary>
/// �J��������]������
/// </summary>
void Camera::RotateCamera()
{
	
}

// ���b�N�I���Ώۂ�����
void Camera::TargetRockon()
{
	if (isRockOnPossible() && isRockOn)
	{
		targetPosition = enemyPosition;
	}
	else
	{
		// ���b�N�I�����Ă��Ȃ��ꍇ�̓v���C���[�𒍎�����
		targetPosition = actorPosition;
	}
}

/// <summary>
/// ���b�N�I���\��
/// </summary>
/// <returns></returns>
bool Camera::isRockOnPossible()
{
	float range = VSize(enemyPosition - actorPosition);
	// ���b�N�I���\�������Ȃ�
	if (ROCKON_POSSIBLE_DISTANCE >= range && isRockOn)
	{
		return true;
	}
	// ���b�N�I�����ɔ͈͊O�ɏo�����̂��߃t���O�� false �ɂ���
	else
	{
		isRockOn = false;
		return false;
	}
	
}

/// <summary>
/// ���͏���
/// </summary>
void Camera::InputAction()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	if (cameraYaw > 360.0f || cameraYaw < 0.0f)
	{
		//cameraYaw = 0.0f;
	}

	// �J���������v���ɉ�]������
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_Q))
	{
		cameraYaw += 1.5f * deltaTime;
	}
	// �J�����𔽎��v���ɉ�]������
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_E))
	{
		cameraYaw -= 1.5f * deltaTime;
	}
	// �J�����ʒu����������
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_I))
	{
		cameraPitch += 0.5f * deltaTime;
	}
	// �J�����ʒu��Ⴍ����
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_K))
	{
		cameraPitch -= 0.5f * deltaTime;
	}
}
