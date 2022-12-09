#include "Random.h"
#include <random>

/// <summary>
/// コンストラクタ
/// </summary>
Random::Random()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Random::~Random()
{
	// 処理なし
}

/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns></returns>
Random& Random::GetInstance()
{
	static Random random;
	return random;
}

/// <summary>
/// ランダムなint値を返す
/// </summary>
/// <param name="min">最小値</param>
/// <param name="max">最大値</param>
/// <returns></returns>
int Random::GetRandomInt(int min, int max)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> next(min, max);

	return next(eng);
}

/// <summary>
/// ランダムなfloat値を返す
/// </summary>
/// <param name="min">最小値</param>
/// <param name="max">最大値</param>
/// <returns></returns>
float Random::GetRandomFloat(float min, float max)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<> next(min, max);

	return next(eng);
}
