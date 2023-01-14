#include "Pch.h"
#include "HitChecker.h"

#include "GameDefine.h"
#include "Character.h"
#include "Player.h"
#include "Shield.h"
#include "Boss.h"
#include "SoundManager.h"

using namespace Math3d;

/// <summary>
/// �R���X�g���N�^
/// </summary>
HitChecker::HitChecker()
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
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
	PlayerAndEnemy(player, boss);				// �v���C���[�ƃG�l�~�[�̓����蔻��
	ShieldAndEnemy(player, shield, boss);		// �V�[���h�ƃG�l�~�[�̓����蔻��
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
	
	// �͂������������ݒ�
	// ������΂������͋t����
	VECTOR forceDirection = VNorm(sub);
	forceDirection.y = 0.0f;
	forceDirection = VScale(forceDirection, -1.0f);

	// �v���C���[�ƃG�l�~�[�̋��������݂��̓����蔻�蔼�a��菬�����ꍇ�������Ă���
	if (distance <= radius &&
		player->GetCurrentState() != Player::State::DAMAGE)
	{
		// �ڐG�����Đ�

		// �e�I�u�W�F�N�g�Ή�
		player->HitOtherCharacter(forceDirection);
		boss->HitOtherCharacter(forceDirection);
	}

}

/// <summary>
/// ���ƃG�l�~�[�̓����蔻��
/// </summary>
/// <param name="shield"></param>
/// <param name="boss"></param>
void HitChecker::ShieldAndEnemy(Player* player, Shield* shield, Boss* boss)
{
	VECTOR sub = boss->GetPosition() - shield->GetPosition();

	// ���ƃG�l�~�[�̋������v��
	float distance = VSize(sub);
	float radius = shield->GetCollideRadius() + boss->GetCollideRadius();

	// �͂������������ݒ�
	// �G�l�~�[
	VECTOR enemyForceDirection = VNorm(sub);
	
	// �v���C���[�̓G�l�~�[�Ƃ͋t������
	VECTOR playerForceDirection = VScale(enemyForceDirection, -1.0f);
	playerForceDirection.y = 0.0f;

	// �V�[���h�ƃG�l�~�[�̋��������݂��̓����蔻�蔼�a��菬�����ꍇ�������Ă���
	if (distance <= radius &&
		shield->GetState() == Shield::State::DEPLOYMENT)
	{
		// �h�䉹�Đ�

		// �e�I�u�W�F�N�g�Ή�
		shield->HitOtherCharacter();
		player->HitShieldOtherCharacter(playerForceDirection);
		boss->HitShield(enemyForceDirection, shield->isJust());
	}
}



