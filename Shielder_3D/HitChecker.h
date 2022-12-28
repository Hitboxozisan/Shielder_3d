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

private:
	int hitStopTime;
};

