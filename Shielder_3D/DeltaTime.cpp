#include "Pch.h"
#include "DeltaTime.h"

//---------------------------------------------
// コンストラクタ
//---------------------------------------------
DeltaTime::DeltaTime()
    : nowCount(0.0f)
    , prevCount(0.0f)
    , deltaTime(0.0f)
    , isSlow(false)
{
    // 処理なし
}

//---------------------------------------------
// デストラクタ
//---------------------------------------------
DeltaTime::~DeltaTime()
{
    // 処理なし
}

//---------------------------------------------
// インスタンスの取得
//---------------------------------------------
DeltaTime& DeltaTime::GetInstance()
{
    static DeltaTime deltaTime;
    return deltaTime;
}

//---------------------------------------------
// DeltaTimeの計測
//---------------------------------------------
void DeltaTime::InstrumentationDeltaTime()
{
    deltaTime;
    nowCount = GetNowCount();
    deltaTime = (nowCount - prevCount) / 1000.0f;
    prevCount = nowCount;
}

//---------------------------------------------
// DeltaTimeを設定
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
// ゲーム開始時のタイムを取得
//---------------------------------------------
void DeltaTime::SetCount()
{
    nowCount, prevCount;
    nowCount = prevCount = GetNowCount();
}
