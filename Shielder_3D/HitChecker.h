//----------------------------------------------------------------
// <�s��E�o�O>
// �E
// <note>
// �ECheck�֐���GameObject�ł܂Ƃ߂ă^�O�ŃI�u�W�F�N�g�𔻒f�����ق����������������
//----------------------------------------------------------------
#pragma once

class Character;
class Player;
class Shield;
class Boss;
class Bullt;

class HitChecker final
{
public:
	HitChecker();
	~HitChecker();

	void Check(Player* player,
			   Shield* shield,
			   Boss* boss);

	// �قƂ�ǎ����悤�Ȃ��̂܂Ƃ߂��邩�H
	void PlayerAndEnemy(Player* player, Boss* boss);		// �v���C���[�ƃG�l�~�[�̓����蔻��
	void ShieldAndEnemy(Player* player,
						Shield* shield,
						Boss* boss);						// ���ƃG�l�~�[�̓����蔻��
	void ShieldAndSword();									// ���ƌ��̓����蔻��
	void SwordAndCharacter();								// ���ƃL�����N�^�[�̓����蔻��
	//void BulletAndPlayer(Player* player, Boss* boss, std::list<Bullet*>* bullet);	// �e�ƃv���C���[�̓����蔻��

private:
	int hitStopTime;
};

