#pragma once
class DebugMenu
{
public:
	DebugMenu();
	~DebugMenu();

	void Initialize();
	void Update();
	void Draw();
	
	void DrawCameraPosition(VECTOR position);		// カメラの現在位置を描画
	void DrawCameraDirection(VECTOR direction);		// カメラの向きを描画

private:

	int displayCount;					// デバッグ表示件数

	static const int FIRST_POSITION_X;		// 先頭位置_X
	static const int FIRST_POSITION_Y;		// 先頭位置_Y

};

