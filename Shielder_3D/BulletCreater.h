#pragma once

class Bullet;

#include<list>

class BulletCreater
{
public:
	BulletCreater(std::list<Bullet*>* const activeList,
				  std::list<Bullet*>* const deactiveList );
	~BulletCreater();

	Bullet* Create(const VECTOR& inPosition, const VECTOR& inDirection);	// �e�̐���
	bool IsCreatableCheck();												// �e�������\��

private:
	//BulletCreater();
	BulletCreater(const BulletCreater&);
	void operator=(const BulletCreater&);

	// �x�N�^�[�ւ̃|�C���^
	std::list<Bullet*>* const activeBullet;
	std::list<Bullet*>* const deActiveBullet;
};

