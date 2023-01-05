#pragma once

class Bullet;

#include<vector>

class BulletCreater
{
public:
	BulletCreater(std::vector<Bullet*>* const activeList,
				  std::vector<Bullet*>* const deactiveList );
	~BulletCreater();

	Bullet* Create(const VECTOR& inPosition, const VECTOR& inDirection);
	bool IsCreatableCheck();

private:
	//BulletCreater();
	BulletCreater(const BulletCreater&);
	void operator=(const BulletCreater&);

	// ベクターへのポインタ
	std::vector<Bullet*>* const activeBullet;
	std::vector<Bullet*>* const deActiveBullet;
};

