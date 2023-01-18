#pragma once

class Boss;

/// <summary>
/// カメラクラス
/// </summary>
class Camera
{
public:
	Camera();
	~Camera();

	void Initialize(Boss* inBoss);			// 初期化処理
	void Finalize();						// 終了処理
	void Activate(VECTOR inPlayerPos,
				  VECTOR inEnemyPos);		// 活性化処理
	void Deactivate();						// 非活性化処理
	void Update(VECTOR inPlayerPos,
				VECTOR inEnemyPos);			// 更新処理
	void ChangeCamera();					// カメラを切り替える（追従・ロックオン）

	VECTOR GetPosition();					// 現在位置を返す
	VECTOR GetTargetPosition();				// 現在の注視点を返す
	bool IsRockOn();						// ロックオン中か

private:
	
	// 定数
	static const float TARGET_DISTANCE;
	static const float HORIZONTAL_DISTANCE;
	static const float VERTICAL_DISTANCE;

	static const float CAMERA_DISTANCE;				// カメラとプレイヤーの距離
	static const float DISPLACE_DISTANCE;			// 中心からのずれの距離
	static const float ROCKON_POSSIBLE_DISTANCE;	// ロックオン可能距離
	static const float ERROR_ADMISSIBLE_DISTANCE;	// ロックオン中対象を追わない誤差距離
	static const float ROCKON_DISTANCE;				// ロックオン中のカメラ距離
	static const float ROCKON_VERTICAL_DISTANCE;	// ロックオン中のカメラ高

	Boss* boss;						// Bossクラスのポインタ

	// 変数
	float targetDistance;			// ターゲット距離
	float horizontalDistance;		// 水平距離
	float verticalDistance;			// 垂直距離
	
	float cameraRadius;				// カメラ回転半径
	float cameraYaw;				// 水平方向回転角（ヨー）
	float cameraPitch;				// 高さ方向回転角（ピッチ）
	float rockOnDistance;			// ロックオン可能距離
	VECTOR position;				// カメラの位置
	VECTOR actorPosition;			// プレイヤーの位置
	VECTOR enemyPosition;			// 敵の位置（主にロックオンに使用）
	VECTOR targetPosition;			// 注視点の位置

	bool isRockOn;					// ロックオンしているか

	void UpdatePosition(VECTOR inPlayerPos, VECTOR inEnemyPos);	// actor と enemy の現在位置の更新
	void CalculatingCamerePos();	// カメラの位置を計算 
	void CalculatingTagetPos();		// 注視点の位置を計算
	void RotateCamera();			// カメラを回転させる
	void TargetRockon();			// ロックオン対象を見る
	void ChangeTargetPosition();	// 注視点を対象まで移動させる
	
	bool isRockOnPossible();		// ロックオン可能か

	void InputAction();				// 入力処理
};

