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

	void PlayerAndEnemy(Player* player, Boss* boss);		// プレイヤーと敵の当たり判定

private:
	int hitStopTime;
};

