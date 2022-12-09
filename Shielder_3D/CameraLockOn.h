#pragma once

#include "CameraBase.h"

class CameraLockOn : public CameraBase
{
public:
	CameraLockOn(CameraManager* const cameraManager);
	~CameraLockOn();

	void Initialize();		// 初期化処理
	void Fainalize();		// 終了処理
	void Activate();		// 活性化処理
	void Deactivate();		// 非活性化処理
	void Update();			// 更新処理

private:
	CameraLockOn();							// デフォルトコンストラクタ
	CameraLockOn(const CameraLockOn&);		// コピーコンストラクタ
	void operator=(const CameraLockOn&);	// 代入演算子
};

