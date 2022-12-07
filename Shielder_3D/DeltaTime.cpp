#include "Pch.h"
#include "DeltaTime.h"

//---------------------------------------------
// �R���X�g���N�^
//---------------------------------------------
DeltaTime::DeltaTime()
    : nowCount(0.0f)
    , prevCount(0.0f)
    , deltaTime(0.0f)
    , isSlow(false)
{
    // �����Ȃ�
}

//---------------------------------------------
// �f�X�g���N�^
//---------------------------------------------
DeltaTime::~DeltaTime()
{
    // �����Ȃ�
}

//---------------------------------------------
// �C���X�^���X�̎擾
//---------------------------------------------
DeltaTime& DeltaTime::GetInstance()
{
    static DeltaTime deltaTime;
    return deltaTime;
}

//---------------------------------------------
// DeltaTime�̌v��
//---------------------------------------------
void DeltaTime::InstrumentationDeltaTime()
{
    deltaTime;
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

//---------------------------------------------
// �Q�[���J�n���̃^�C�����擾
//---------------------------------------------
void DeltaTime::SetCount()
{
    nowCount, prevCount;
    nowCount = prevCount = GetNowCount();
}
