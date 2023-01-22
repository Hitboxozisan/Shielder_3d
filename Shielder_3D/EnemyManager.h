#pragma once

class Boss;

class EnemyManager
{
public:
	EnemyManager(Boss* const);
	~EnemyManager();

	
private:

	Boss* boss;
};

