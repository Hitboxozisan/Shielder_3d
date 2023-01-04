#include "Pch.h"
#include <algorithm>
#include "Timer.h"

using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="limitTime"></param>
Timer::Timer(float limitTime)
	:time(0)
	,limitTime(limitTime)
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Timer::~Timer()
{
	// �����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Timer::Update(float deltaTime)
{
	time = min(time + deltaTime, limitTime);
}

/// <summary>
/// ���Z�b�g
/// </summary>
void Timer::Reset()
{
	time = 0;
}

/// <summary>
/// �^�C���A�E�g��
/// </summary>
bool Timer::IsTimeout() const
{
	return time >= limitTime;
}
