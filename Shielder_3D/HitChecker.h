//----------------------------------------------------------------
// <不具合・バグ>
// ・
// <note>
// ・Check関数はGameObjectでまとめてタグでオブジェクトを判断したほうがいいかもしれん
//----------------------------------------------------------------
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

	// ほとんど似たようなものまとめられるか？
	void PlayerAndEnemy(Player* player, Boss* boss);		// プレイヤーとエネミーの当たり判定
	void ShieldAndEnemy(Player* player,
						Shield* shield,
						Boss* boss);						// 盾とエネミーの当たり判定

private:
	int hitStopTime;
};

