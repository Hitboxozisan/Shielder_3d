#pragma once

#include "Camera.h"

/// <summary>
/// メインカメラクラス
/// </summary>
class CameraMain : public Camera
{
public:
	CameraMain(CameraManager* const cameraManager);
	~CameraMain();

	void Initialize();		// 初期化処理
	void Fainalize();		// 終了処理
	void Activate();		// 活性化処理
	void Deactivate();		// 非活性化処理
	void Update();			// 更新処理
	void Draw();			// 描画処理

private:
	//CameraMain();

};

