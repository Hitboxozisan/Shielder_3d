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

}

/// <summary>
/// �v���C���[�ƓG�̓����蔻��
/// </summary>
/// <param name="player">�v���C���[�̃|�C���^</param>
/// <param name="boss">�G�l�~�[�̃|�C���^</param>
void HitChecker::PlayerAndEnemy(Player* player, Boss* boss)
{
	VECTOR sub = player->GetPosition() - boss->GetPosition();

}



