#include "Pch.h"
#include "HitChecker.h"

#include "GameDefine.h"
#include "Character.h"
#include "Player.h"
#include "Shield.h"
#include "Boss.h"
#include "SoundManager.h"

using namespace Math3d;

HitChecker::HitChecker()
{
	// �����Ȃ�
}

HitChecker::~HitChecker()
{
	// �����Ȃ�
}

/// <summary>
/// �e�����蔻�菈��
/// </summary>
/// <param name="player"></param>
/// <param name="boss"></param>
void HitChecker::Check(Player* player,
					   Shield* shield,
					   Boss* boss)
{
	PlayerAndEnemy(player, boss);		// �v���C���[�ƃG�l�~�[�̓����蔻��
}

/// <summary>
/// �v���C���[�ƃG�l�~�[�̓����蔻��
/// </summary>
/// <param name="player">�v���C���[�̃|�C���^</param>
/// <param name="boss">�G�l�~�[�̃|�C���^</param>
void HitChecker::PlayerAndEnemy(Player* player, Boss* boss)
{
	VECTOR sub = boss->GetPosition() - player->GetPosition();
	// �v���C���[�ƃG�l�~�[�̋������v��
	float distance = VSize(sub);
	float radius = player->GetCollideRadius() + boss->GetCollideRadius();

	// �v���C���[�ƃG�l�~�[�̋��������݂��̓����蔻�蔼�a��菬�����ꍇ�������Ă���
	if (distance <= radius)
	{
		
	}

}



