#include "Pch.h"
#include <algorithm>
#include "Timer.h"

using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="limitTime"></param>
Timer::Timer(float limitTime)
	:time(0)
	,limitTime(limitTime)
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Timer::~Timer()
{
	// 処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void Timer::Update(float deltaTime)
{
	time = min(time + deltaTime, limitTime);
}

/// <summary>
/// リセット
/// </summary>
void Timer::Reset()
{
	time = 0;
}

/// <summary>
/// タイムアウトか
/// </summary>
bool Timer::IsTimeout() const
{
	return time >= limitTime;
}
