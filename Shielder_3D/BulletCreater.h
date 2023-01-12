#pragma once

class Bullet;

#include<list>

class BulletCreater
{
public:
	BulletCreater(std::list<Bullet*>* const activeList,
				  std::list<Bullet*>* const deactiveList );
	~BulletCreater();

	Bullet* Create(const VECTOR& inPosition, const VECTOR& inDirection);	// 弾の生成
	bool IsCreatableCheck();												// 弾が生成可能か

private:
	//BulletCreater();
	BulletCreater(const BulletCreater&);
	void operator=(const BulletCreater&);

	// ベクターへのポインタ
	std::list<Bullet*>* const activeBullet;
	std::list<Bullet*>* const deActiveBullet;
};

