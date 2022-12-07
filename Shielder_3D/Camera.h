#pragma once

class CameraManager;

//-----------------------------------------------------------------------------
// カメラベースクラス
//-----------------------------------------------------------------------------
class Camera
{
public:
	Camera(CameraManager* const cameraManager);
	virtual ~Camera();

	virtual void Initialize() = 0;		// 初期化処理
	virtual void Fainalize() = 0;		// 終了処理
	virtual void Activate() = 0;		// 活性化処理
	virtual void Deactivate() = 0;		// 非活性化処理
	virtual void Update() = 0;			// 更新処理
	virtual void Draw() = 0;			// 描画処理

	int GetId();			// 識別番号を返す

protected:
	CameraManager* parent;	// カメラマネージャーのポインタ

	int id;					// カメラの識別番号（今回は使用しないが今後のため）
	VECTOR position;		// 現在位置
	VECTOR nextPosition;	// 次フレームでのポジション
	VECTOR prevPosition;	// 前フレームでのポジション
	VECTOR direction;		// カメラの向き
	VECTOR nextDirection;	// 次フレームの向き
	VECTOR prevDirection;	// 前フレームでの向き

private:
	Camera();						// デフォルトコンストラクタ
	Camera(const Camera&);			// コピーコンストラクタ
	void operator=(const Camera&);	// 代入演算子

};

