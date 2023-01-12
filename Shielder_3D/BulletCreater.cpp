#include "Pch.h"

#include "Bullet.h"
#include "BulletCreater.h"

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
BulletCreater::~BulletCreater()
{
}

/// <summary>
/// �e����
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
/// �c��e��ɋ󂫂����邩
/// </summary>
/// <returns>�󂫂�����</returns>
bool BulletCreater::IsCreatableCheck()
{
	//�󂫂�����
	if (deActiveBullet->empty() == false)
	{
		return true;
	}

	return false;
}
