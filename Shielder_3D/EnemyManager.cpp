#include "EnemyManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name=""></param>
EnemyManager::EnemyManager(Boss* const inBoss)
	:boss(inBoss)
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyManager::~EnemyManager()
{
	// 処理なし
}
