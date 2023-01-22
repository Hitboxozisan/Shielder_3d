#pragma once

class Boss;

#include <vector>

class EnemyManager
{
public:
	EnemyManager(Boss* const);
	~EnemyManager();

	void Initialize();						// ����������
	void Update();							// �X�V����

	void PopEnemy();


private:
	static const int ENEMY_AMOUNT;			// �G�l�~�[�̑���

	//std::vector<Boss*> boss;

	Boss* boss;
};

