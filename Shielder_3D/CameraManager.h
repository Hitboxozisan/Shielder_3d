#pragma once

class Camera;

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
		LOCK_ON
	};

	void Initialize();		// 初期化処理
	void Finalize();		// 終了処理
	void Update();
	void Draw();

	void SetNextCamera();		// 次のカメラをセット
	void GetCurrentCamera();	// 現在のカメラを返す

private:
	CameraManager(const CameraManager&);	// コピーコンストラクタ
	void operator=(const CameraManager&);	// コピー代入演算子

	Camera* eachCamera[Camera::LOCK_ON];	// 各カメラのインスタンス
	Camera* currentPointer;					// 現在のカメラのポインタ

	void ChangeCamera();					// カメラを変更する
};

