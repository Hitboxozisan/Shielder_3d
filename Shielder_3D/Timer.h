#pragma once

/// <summary>
/// タイマークラス
/// </summary>
class Timer
{
public:
	Timer(float limitTime);
	~Timer();

	void Update(float deltaTime);		// 更新処理
	void Reset();						// タイマーのリセット
	bool IsTimeout() const;				// タイムアウトか

private:
	float time;			// 現在の時間
	float limitTime;	// 制限時間
};

