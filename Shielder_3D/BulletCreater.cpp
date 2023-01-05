#include "Pch.h"

#include "Bullet.h"
#include "BulletCreater.h"

BulletCreater::BulletCreater(std::vector<Bullet*>* const activeList, 
							 std::vector<Bullet*>* const deactiveList)
	:activeBullet(activeList)
	,deActiveBullet(deactiveList)
{
}

BulletCreater::~BulletCreater()
{
}

Bullet* BulletCreater::Create(const VECTOR& inPosition, const VECTOR& inDirection)
{
	activeBullet->push_back(deActiveBullet->front());
	deActiveBullet->front();
	activeBullet->back()->Activate(inPosition, inDirection);

	return activeBullet->back();
}

bool BulletCreater::IsCreatableCheck()
{
	//‹ó‚«‚ª‚ ‚é
	if (deActiveBullet->empty() == false)
	{
		return true;
	}

	return false;
}
