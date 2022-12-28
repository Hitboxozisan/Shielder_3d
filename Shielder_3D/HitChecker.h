#pragma once

class Character;
class Player;
class Shield;
class Boss;

class HitChecker final
{
public:
	HitChecker();
	~HitChecker();

	void Check(Player* player,
		Shield* shield,
		Boss* boss);

	void PlayerAndEnemy(Player* player, Boss* boss);		// �v���C���[�ƓG�̓����蔻��

private:
	int hitStopTime;
};

