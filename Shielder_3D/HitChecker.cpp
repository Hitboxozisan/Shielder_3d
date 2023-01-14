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
/// コンストラクタ
/// </summary>
HitChecker::HitChecker()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
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
	PlayerAndEnemy(player, boss);				// プレイヤーとエネミーの当たり判定
	ShieldAndEnemy(player, shield, boss);		// シールドとエネミーの当たり判定
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
	
	// 力を加える向きを設定
	// 吹き飛ばす方向は逆方向
	VECTOR forceDirection = VNorm(sub);
	forceDirection.y = 0.0f;
	forceDirection = VScale(forceDirection, -1.0f);

	// プレイヤーとエネミーの距離がお互いの当たり判定半径より小さい場合当たっている
	if (distance <= radius &&
		player->GetCurrentState() != Player::State::DAMAGE)
	{
		// 接触音を再生

		// 各オブジェクト対応
		player->HitOtherCharacter(forceDirection);
		boss->HitOtherCharacter(forceDirection);
	}

}

/// <summary>
/// 盾とエネミーの当たり判定
/// </summary>
/// <param name="shield"></param>
/// <param name="boss"></param>
void HitChecker::ShieldAndEnemy(Player* player, Shield* shield, Boss* boss)
{
	VECTOR sub = boss->GetPosition() - shield->GetPosition();

	// 盾とエネミーの距離を計測
	float distance = VSize(sub);
	float radius = shield->GetCollideRadius() + boss->GetCollideRadius();

	// 力を加える向きを設定
	// エネミー
	VECTOR enemyForceDirection = VNorm(sub);
	
	// プレイヤーはエネミーとは逆方向に
	VECTOR playerForceDirection = VScale(enemyForceDirection, -1.0f);
	playerForceDirection.y = 0.0f;

	// シールドとエネミーの距離がお互いの当たり判定半径より小さい場合当たっている
	if (distance <= radius &&
		shield->GetState() == Shield::State::DEPLOYMENT)
	{
		// 防御音再生

		// 各オブジェクト対応
		shield->HitOtherCharacter();
		player->HitShieldOtherCharacter(playerForceDirection);
		boss->HitShield(enemyForceDirection, shield->isJust());
	}
}



