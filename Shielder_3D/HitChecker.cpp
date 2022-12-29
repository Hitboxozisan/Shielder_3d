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
	// 処理なし
}

HitChecker::~HitChecker()
{
	// 処理なし
}

/// <summary>
/// 各当たり判定処理
/// </summary>
/// <param name="player"></param>
/// <param name="boss"></param>
void HitChecker::Check(Player* player,
					   Shield* shield,
					   Boss* boss)
{
	PlayerAndEnemy(player, boss);		// プレイヤーとエネミーの当たり判定
}

/// <summary>
/// プレイヤーとエネミーの当たり判定
/// </summary>
/// <param name="player">プレイヤーのポインタ</param>
/// <param name="boss">エネミーのポインタ</param>
void HitChecker::PlayerAndEnemy(Player* player, Boss* boss)
{
	VECTOR sub = boss->GetPosition() - player->GetPosition();
	// プレイヤーとエネミーの距離を計測
	float distance = VSize(sub);
	float radius = player->GetCollideRadius() + boss->GetCollideRadius();

	// プレイヤーとエネミーの距離がお互いの当たり判定半径より小さい場合当たっている
	if (distance <= radius)
	{
		
	}

}



