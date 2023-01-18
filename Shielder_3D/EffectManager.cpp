#include "Pch.h"

#include "EffectBase.h"
#include "EffectManager.h"
#include "GuardEffect.h"
#include "DamageEffect.h"
#include "PlayerDiedEffect.h"
#include "SmokeEffect.h"
#include "ChargeEnergyEffect.h"
#include "EffectTeleport.h"

const int EffectManager::SMOKE_EFFECT_AMOUNT  = 16;
const int EffectManager::ENERGY_EFFECT_AMOUNT = 64;

const float EffectManager::SMOKE_EFFECT_SIZE = 15.0f;

//ベースクラスインスタンスの総量
const int EffectManager::BILLBOARD_AMOUNT = SMOKE_EFFECT_AMOUNT + ENERGY_EFFECT_AMOUNT;

const std::string EffectManager::SPARK_EFFECT_PATH			= "Data/Effect/blow.efkefc";
const std::string EffectManager::DAMAGE_EFFECT_PATH			= "Data/Effect/damage.efkefc";
const std::string EffectManager::RIGOR_EFFECT_GRAPHIC_PATH  = "Data/Effect/smoke.png";
const std::string EffectManager::ENERGY_EFFECT_GRAPHIC_PATH = "Data/Effect/energy.png";


EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Initialize()
{
	//画像読み込み
	smokeGraphicHandle  = LoadGraph(RIGOR_EFFECT_GRAPHIC_PATH.c_str());
	energyGraphicHandle = LoadGraph(ENERGY_EFFECT_GRAPHIC_PATH.c_str());
	

	//各エフェクト初期化
	effects[0] = new GuardEffect();
	effects[0]->Initialize();

	effects[1] = new DamageEffect();
	effects[1]->Initialize();

	effects[2] = new PlayerDiedEffect();
	effects[2]->Initialize();

	effects[3] = new EffectTeleport();
	effects[3]->Initialize();

	//effects[3] = new RecoveryEffect();
	//effects[3]->Initialize();
	
	//effects[4] = new PlayerLaserEffect();
	//effects[4]->Initialize();

	graphicEffects = new BillboardBase * [BILLBOARD_AMOUNT];

	int itr = 0;
	int length = 0;

	length += BILLBOARD_AMOUNT;
	for ( itr = 0 ; itr < length; ++itr)
	{
		// もっといい方法はないものか
		if (itr < SMOKE_EFFECT_AMOUNT)
		{
			graphicEffects[itr] = new SmokeEffect();
			graphicEffects[itr]->Initialize(&smokeGraphicHandle);
		}
		else
		{
			graphicEffects[itr] = new ChargeEnergyEffect();
			graphicEffects[itr]->Initialize(&energyGraphicHandle);
		}
	}
}

void EffectManager::Finalize()
{
	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Finalize();
		SafeDelete(effects[i]);
	}

	for (int i = 0; i < BILLBOARD_AMOUNT; ++i)
	{
		graphicEffects[i]->Finalize();
	}
}

void EffectManager::Activate(VECTOR inPosition)
{
	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Activate(inPosition);
	}
}

void EffectManager::Deactivate()
{
	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Deactivate();
	}

	for (int i = 0; i < BILLBOARD_AMOUNT; ++i)
	{
		graphicEffects[i]->Deactivate();
	}
}

void EffectManager::Update(VECTOR inPostion, VECTOR inEnemyPosition)
{
	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Update(inPostion, inEnemyPosition);
	}

	for (int i = 0; i < BILLBOARD_AMOUNT; ++i)
	{
		graphicEffects[i]->Update();
	}
}

void EffectManager::Draw(const VECTOR& inPosition)
{
	int itr = 0;
	int length = 0;



	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Draw();
	}

	length += BILLBOARD_AMOUNT;
	for (; itr < length; ++itr)
	{
		graphicEffects[itr]->Draw(inPosition);
	}
}

void EffectManager::CreateSparkEffect(const VECTOR& inPosition)
{
	if (effects[SPARK]->GetExist() == false)
	{
		effects[SPARK]->Activate(inPosition);
		return;
	}
}

/// <summary>
/// 粒子を発生させる
/// </summary>
/// <param name="inPosition"></param>
void EffectManager::CreateEnergyEffect(const VECTOR& inPosition)
{
	int count = 0;
	int itr = SMOKE_EFFECT_AMOUNT;
	int length = itr + ENERGY_EFFECT_AMOUNT;

	for (; itr < length; ++itr)
	{
		if (graphicEffects[itr]->GetExist())
		{
			++itr;
		}
		else
		{
			graphicEffects[itr]->Activate(inPosition, 10.0f);
			++count;
			if (count >= 32) return;
		}
	}
}

/// <summary>
/// 煙を生成する
/// </summary>
/// <param name="inPosition"></param>
void EffectManager::CreateSmokeEffect(const VECTOR& inPosition)
{
	int itr = 0;
	int length = itr + SMOKE_EFFECT_AMOUNT;

	for (; itr < length; ++itr)
	{
		if (graphicEffects[itr]->GetExist())
		{
			++itr;
		}
		else
		{
			graphicEffects[itr]->Activate(inPosition, 100.0f);
			return;
		}
	}
}

void EffectManager::CreateDamageEffect(const VECTOR& inPosition)
{
	if (effects[DAMAGE]->GetExist() == false)
	{
		effects[DAMAGE]->Activate(inPosition);
		return;
	}
}

void EffectManager::CreatePlayerDiedEffect(const VECTOR& inPosition)
{
	if (effects[PLAYER_DEAD]->GetExist() == false)
	{
		effects[PLAYER_DEAD]->Activate(inPosition);
		return;
	}
}

void EffectManager::CreateRecoveryEffect(const VECTOR& inPosition)
{
	/*if (effects[RECOVERY]->GetExist() == false)
	{
		effects[RECOVERY]->Activate(inPosition);
		return;
	}*/
}

void EffectManager::CreatePlayerLaser(const VECTOR& inPosition)
{
	/*if (effects[PLAYER_LASER]->GetExist() == false)
	{
		effects[PLAYER_LASER]->Activate(inPosition);
		return;
	}*/
}

/// <summary>
/// テレポートエフェクトを生成
/// </summary>
/// <param name="inPosition"></param>
void EffectManager::CreateTeleportEffect(const VECTOR& inPosition)
{
	if (effects[ENEMY_TELEPORT]->GetExist() == false)
	{
		effects[ENEMY_TELEPORT]->Activate(inPosition);
		return;
	}
}

/// <summary>
/// エフェクトが存在していないか
/// </summary>
/// <returns> true : 存在していない </returns>
bool EffectManager::GetEnergyEffectState()
{
	int energyBegin = SMOKE_EFFECT_AMOUNT + 1;
	int energyEnd = BILLBOARD_AMOUNT - 1;

	if (!graphicEffects[energyBegin]->GetExist() && !graphicEffects[energyEnd]->GetExist())
	{
		return true;
	}
	else
	{
		return false;
	}
}
