#include "Pch.h"

#include "Boss.h"
#include "EnemyManager.h"

const int EnemyManager::ENEMY_AMOUNT = 2;

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

/// <summary>
/// 初期化処理
/// </summary>
void EnemyManager::Initialize()
{
	for (int i = 0; i < ENEMY_AMOUNT; ++i)
	{
		//boss = new Boss();
	}
}
