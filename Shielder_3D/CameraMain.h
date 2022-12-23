#pragma once

#include "CameraBase.h"

/// <summary>
/// メインカメラクラス
/// </summary>
class CameraMain final : public CameraBase
{
public:
	CameraMain(CameraManager* const cameraManager);
	~CameraMain();

	void Initialize();		// 初期化処理
	void Fainalize();		// 終了処理
	void Activate();		// 活性化処理
	void Deactivate();		// 非活性化処理
	void Update();			// 更新処理

private:
	CameraMain();						// デフォルトコンストラクタ
	CameraMain(const CameraMain&);		// コピーコンストラクタ
	void operator=(const CameraMain&);	// 代入演算子

	void FollowTarget();				// ターゲットを追従する
	void RotateCamera();				// カメラを回転させる
	void InputAction();					// 入力処理

	static const float INITIALIZE_RANGE_TARGET;		// ターゲットとの距離（初期値）

	float cameraRadius;				// カメラ回転半径
	float cameraYaw;				// 水平方向回転角（ヨー）
};

