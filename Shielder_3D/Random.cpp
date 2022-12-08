#include "Random.h"
#include <random>

float Random::GetRandomFloat(float min, float max)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<> next(min, max);

	return next(eng);
}
