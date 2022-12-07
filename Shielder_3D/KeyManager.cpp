#include "KeyManager.h"
#include "Pch.h"

#include <chrono>

//---------------------------------------------
// コンストラクタ
//---------------------------------------------
KeyManager::KeyManager()
    : currentState()
    , prevState()
    , allKeyReleaseCount()
{
    // 処理なし
}
//---------------------------------------------
// コピーデストラクタ
//---------------------------------------------
KeyManager::KeyManager(const KeyManager&)
{
    // 使用しない
}

//---------------------------------------------
// 代入演算子
//---------------------------------------------
void KeyManager::operator=(const KeyManager&)
{
    // 使用しない
}

//---------------------------------------------
// デストラクタ
//---------------------------------------------
KeyManager::~KeyManager()
{
    // 処理なし
}

//---------------------------------------------
// インスタンスを取得
//---------------------------------------------
KeyManager& KeyManager::GetInstance()
{
    static KeyManager keyManager;
    return keyManager;
}

//---------------------------------------------
// 更新処理
//---------------------------------------------
void KeyManager::Update()
{
    for (int i = 0; i < 256; ++i)
    {
        prevState[i] = currentState[i]; // prevを更新
    }

    GetHitKeyStateAll(currentState);  // currentを更新

    // 何かキーが押されていたらカウントリセット
    for (int i = 0; i < 256; ++i)
    {
        if (currentState[i])
        {
            allKeyReleaseCount = 0;
            return;
        }
    }

    ++allKeyReleaseCount;
}

//---------------------------------------------
// 何かしらキーが押されたら
//---------------------------------------------
bool KeyManager::CheckPressed(int keyCode) const
{
    if (currentState[keyCode] == 0)
    {
        return false;   // 現フレームで押されていない
    }
    return true;    // 現フレームで押されている
}

//---------------------------------------------
// 何かしらのキーを押した瞬間か
//---------------------------------------------
bool KeyManager::CheckJustPressed(int keyCode) const
{
    if (prevState[keyCode] == 1)
    {
        return false;   // 前フレームで押されている
    }
    if (currentState[keyCode] == 0)
    {
        return false;   // 現フレームで押されていない
    }

    return true;    // 現フレームで初めて押された
}

//---------------------------------------------
// 何かしらのキーを離したか
//---------------------------------------------
bool KeyManager::CheckRelease(int keyCode) const
{
    if (prevState[keyCode] == 0)
    {
        return false;   // 前フレームで押されていない
    }
    if (currentState[keyCode] == 1)
    {
        return false;   // 現フレームで押されている
    }

    return true;    // 現フレームでキーは離された
}

//---------------------------------------------
// キーを離している時間を取得
//---------------------------------------------
int KeyManager::GetKeyReleaseCount() const
{
    return allKeyReleaseCount;
}
