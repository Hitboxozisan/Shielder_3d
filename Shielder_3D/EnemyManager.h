#pragma once

class Boss;

#include <vector>

class EnemyManager
{
public:
	EnemyManager(Boss* const);
	~EnemyManager();

	void Initialize();						// 初期化処理
	void Update();							// 更新処理

	void PopEnemy();


private:
	static const int ENEMY_AMOUNT;			// エネミーの総数

	//std::vector<Boss*> boss;

	Boss* boss;
};

