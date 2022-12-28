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

}

/// <summary>
/// プレイヤーと敵の当たり判定
/// </summary>
/// <param name="player">プレイヤーのポインタ</param>
/// <param name="boss">エネミーのポインタ</param>
void HitChecker::PlayerAndEnemy(Player* player, Boss* boss)
{
	VECTOR sub = player->GetPosition() - boss->GetPosition();

}



