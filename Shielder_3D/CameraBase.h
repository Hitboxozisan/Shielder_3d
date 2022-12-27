#pragma once

class CameraManager;

/// <summary>
/// カメラベースクラス
/// </summary>
class CameraBase
{
public:
	CameraBase(CameraManager* const cameraManager);
	virtual ~CameraBase();

	virtual void Initialize() = 0;		// 初期化処理
	virtual void Fainalize() = 0;		// 終了処理
	virtual void Activate() = 0;		// 活性化処理
	virtual void Deactivate() = 0;		// 非活性化処理
	virtual void Update() = 0;			// 更新処理

	void MoveFinish();					// 移動予定地に実際に移動する

	void SetActorPosition(VECTOR inActorPosition);			// アクターの座標を設定する
	void SetTargetPosition(VECTOR inTargetPosition);		// 注視点を設定する
	const int GetId() const;			// 識別番号を返す
	const VECTOR GetPosition() const;	// 現在位置を返す
	const VECTOR GetDirection() const;	// 現在の向きを返す

	void DebugMoveCamera();				// カメラの位置・向きを動かす

protected:
	CameraManager* parent;	// カメラマネージャーのポインタ

	int	   id;						// カメラの識別番号（今回は使用しないが今後のため）
	float  rangeTarget;				// ターゲットとの距離
	VECTOR position;				// 現在位置
	VECTOR nextPosition;			// 次フレームでのポジション
	VECTOR prevPosition;			// 前フレームでのポジション
	VECTOR direction;				// カメラの向き
	VECTOR nextDirection;			// 次フレームの向き
	VECTOR prevDirection;			// 前フレームでの向き
	VECTOR actorPosition;			// アクターの位置
	VECTOR targetPosition;			// 注視点の位置
	VECTOR rockOnTargetPosition;

private:
	CameraBase();						// デフォルトコンストラクタ
	CameraBase(const CameraBase&);		// コピーコンストラクタ
	void operator=(const CameraBase&);	// 代入演算子

	static const float SPEED;

	float speed;						// 移動速度
};

