#pragma once

class CameraBase;
class Player;

/// <summary>
/// カメラマネージャー
/// </summary>
class CameraManager final
{
public:
	CameraManager();
	~CameraManager();

	// カメラの種類
	enum Camera
	{
		MAIN = 0,
		LOCK_ON,

		CAMERA_AMOUNT	// カメラの種類数
	};

	void Initialize();		// 初期化処理
	void Finalize();		// 終了処理
	void Update();

	void SetNextCamera(Camera next);			// 次のカメラをセット
	//Camera GetCurrentCamera();				// 現在のカメラを返す

private:
	CameraManager(const CameraManager&);	// コピーコンストラクタ
	void operator=(const CameraManager&);	// コピー代入演算子

	CameraBase* eachCameras[Camera::CAMERA_AMOUNT];	// 各カメラのインスタンス
	CameraBase* currentPointer;						// 現在のカメラのポインタ
	Camera		currentCamera;						// 現在のカメラ
	Camera		nextCamera;							// 次のカメラ

	//Player* const player;							// プレイヤークラスのポインタ

	void ChangeCamera();							// カメラを変更する
};

