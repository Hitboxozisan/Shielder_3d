#include "Pch.h"
#include "DeltaTime.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
DeltaTime::DeltaTime()
    : nowCount(0.0f)
    , prevCount(0.0f)
    , deltaTime(0.0f)
    , isSlow(false)
{
    // �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DeltaTime::~DeltaTime()
{
    // �����Ȃ�
}

/// <summary>
/// �C���X�^���X�̎擾
/// </summary>
/// <returns></returns>
DeltaTime& DeltaTime::GetInstance()
{
    static DeltaTime deltaTime;
    return deltaTime;
}

/// <summary>
/// deltaTime�̎擾
/// </summary>
void DeltaTime::InstrumentationDeltaTime()
{
    nowCount = GetNowCount();
    deltaTime = (nowCount - prevCount) / 1000.0f;
    prevCount = nowCount;
}

//---------------------------------------------
// DeltaTime��ݒ�
//---------------------------------------------
//void DeltaTime::SetDeltaTime(float delta)
//{
//    if (isSlow)
//    {
//        deltaTime = delta * 0.5f;
//    }
//    else
//    {
//        deltaTime = delta;
//    }
//}

/// <summary>
/// �Q�[���J�n���̃^�C�����擾
/// </summary>
void DeltaTime::SetCount()
{
    nowCount = prevCount = GetNowCount();
}
