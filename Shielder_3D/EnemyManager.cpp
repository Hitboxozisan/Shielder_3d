#include "Pch.h"

#include "Boss.h"
#include "EnemyManager.h"

const int EnemyManager::ENEMY_AMOUNT = 2;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name=""></param>
EnemyManager::EnemyManager(Boss* const inBoss)
	:boss(inBoss)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyManager::~EnemyManager()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void EnemyManager::Initialize()
{
	for (int i = 0; i < ENEMY_AMOUNT; ++i)
	{
		//boss = new Boss();
	}
}
