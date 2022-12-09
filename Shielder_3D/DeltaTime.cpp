#include "Pch.h"
#include "DeltaTime.h"

/// <summary>
/// コンストラクタ
/// </summary>
DeltaTime::DeltaTime()
    : nowCount(0.0f)
    , prevCount(0.0f)
    , deltaTime(0.0f)
    , isSlow(false)
{
    // 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
DeltaTime::~DeltaTime()
{
    // 処理なし
}

/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns></returns>
DeltaTime& DeltaTime::GetInstance()
{
    static DeltaTime deltaTime;
    return deltaTime;
}

/// <summary>
/// deltaTimeの取得
/// </summary>
void DeltaTime::InstrumentationDeltaTime()
{
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

/// <summary>
/// ゲーム開始時のタイムを取得
/// </summary>
void DeltaTime::SetCount()
{
    nowCount = prevCount = GetNowCount();
}
