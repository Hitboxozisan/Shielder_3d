#include "Pch.h"
#include "CameraBase.h"

#include "DeltaTime.h"
#include "KeyManager.h"

using namespace Math3d;

const float CameraBase::SPEED = 100.0f;

/// <summary>
/// コンストラクタ
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
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
CameraBase::~CameraBase()
{
	// 処理なし
}

/// <summary>
/// 移動予定地に実際に移動する
/// </summary>
void CameraBase::MoveFinish()
{
	// 移動しているなら前フレームの向きを更新する
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
/// 識別番号を返す
/// </summary>
/// <returns>識別番号</returns>
const int CameraBase::GetId() const
{
	return id;
}

/// <summary>
/// 現在位置を返す
/// </summary>
/// <returns></returns>
const VECTOR CameraBase::GetPosition() const
{
	return position;
}

/// <summary>
/// 現在の向きを返す
/// </summary>
/// <returns></returns>
const VECTOR CameraBase::GetDirection() const
{
	return direction;
}

/// <summary>
/// カメラの位置・向きを動かす
/// </summary>
void CameraBase::DebugMoveCamera()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	// 前後左右移動
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
	// 上下移動
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

	// カメラの向き変更
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
