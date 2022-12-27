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
		MAIN = 0,		// 主に使用するカメラ
		//START,		// ゲーム開始時の演出用カメラ

		CAMERA_AMOUNT	// カメラの種類数
	};

	void Initialize();		// 初期化処理
	void Finalize();		// 終了処理
	void Update();			// 更新処理

	//void SetRockOnPosition();
	void SetActorPosition(VECTOR inActorPosition);	// アクターの位置を設定する
	void SetTargetPosition(VECTOR inPosition);		// 注視点を設定する
	void SetNextCamera(Camera next);				// 次のカメラをセット
	//Camera GetCurrentCamera();					// 現在のカメラを返す

	VECTOR GetPosition();							// カメラの現在地を返す
	VECTOR GetDirection();							// カメラの向きを返す

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

