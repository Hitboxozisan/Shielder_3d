#include "Random.h"
#include <random>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Random::Random()
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Random::~Random()
{
	// �����Ȃ�
}

/// <summary>
/// �C���X�^���X�̎擾
/// </summary>
/// <returns></returns>
Random& Random::GetInstance()
{
	static Random random;
	return random;
}

/// <summary>
/// �����_����int�l��Ԃ�
/// </summary>
/// <param name="min">�ŏ��l</param>
/// <param name="max">�ő�l</param>
/// <returns></returns>
int Random::GetRandomInt(int min, int max)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> next(min, max);

	return next(eng);
}

/// <summary>
/// �����_����float�l��Ԃ�
/// </summary>
/// <param name="min">�ŏ��l</param>
/// <param name="max">�ő�l</param>
/// <returns></returns>
float Random::GetRandomFloat(float min, float max)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<> next(min, max);

	return next(eng);
}
