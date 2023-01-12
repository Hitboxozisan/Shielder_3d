#include "Pch.h"

#include "Bullet.h"
#include "BulletCreater.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="activeList"></param>
/// <param name="deactiveList"></param>
BulletCreater::BulletCreater(std::list<Bullet*>* const activeList,
							 std::list<Bullet*>* const deactiveList)
	:activeBullet(activeList)
	,deActiveBullet(deactiveList)
{
}

/// <summary>
/// デストラクタ
/// </summary>
BulletCreater::~BulletCreater()
{
}

/// <summary>
/// 弾生成
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
/// <returns></returns>
Bullet* BulletCreater::Create(const VECTOR& inPosition, const VECTOR& inDirection)
{

	activeBullet->push_back(deActiveBullet->front());
	deActiveBullet->pop_front();
	activeBullet->back()->Activate(inPosition, inDirection);

	return activeBullet->back();
}

/// <summary>
/// 残り弾薬に空きがあるか
/// </summary>
/// <returns>空きがある</returns>
bool BulletCreater::IsCreatableCheck()
{
	//空きがある
	if (deActiveBullet->empty() == false)
	{
		return true;
	}

	return false;
}
