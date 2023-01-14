#pragma once

#include "EffectBase.h"
#include "BillboardBase.h"
#include <string>

class EffectManager final
{
public:
	enum Effects
	{
		SPARK,				// スパーク
		DAMAGE,				// ダメージ
		PLAYER_DEAD,		// 死亡
		ENEMY_TELEPORT,		// 瞬間移動
		//RECOVERY,			// 回復
		//PLAYER_LASER,		// プレイヤー勝利エフェクト

		EFFECT_AMOUNT,		// エフェクトの総数
	};

	EffectManager();
	~EffectManager();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update(VECTOR inPostion, VECTOR inEnemyPosition);
	void Draw(const VECTOR& inPosition);

	void CreateSparkEffect(const VECTOR& inPosition);		// 火花を生成する
	void CreateEnergyEffect(const VECTOR& inPosition);		// 粒子を生成する
	void CreateSmokeEffect(const VECTOR& inPosition);		// 煙を生成する
	void CreateDamageEffect(const VECTOR& inPosition);		// ダメージエフェクトを生成する
	void CreatePlayerDiedEffect(const VECTOR& inPosition);	// プレイヤー死亡エフェクトを生成する
	void CreateRecoveryEffect(const VECTOR& inPosition);	// プレイヤー回復エフェクトを生成する
	void CreatePlayerLaser(const VECTOR& inPosition);		// プレイヤー勝利エフェクトを生成する
	void CreateTeleportEffect(const VECTOR& inPosition);	// テレポートエフェクトを生成する

	bool GetEnergyEffectState();							// 粒子エフェクトの状態を取得する

private:
	EffectManager(const EffectManager&);
	void operator=(const EffectManager&);

	static const std::string SPARK_EFFECT_PATH;
	static const std::string DAMAGE_EFFECT_PATH;
	static const std::string RIGOR_EFFECT_GRAPHIC_PATH;
	static const std::string ENERGY_EFFECT_GRAPHIC_PATH;

	static const int SMOKE_EFFECT_AMOUNT;
	static const int ENERGY_EFFECT_AMOUNT;

	// 画像エフェクトサイズ（これは各エフェクトのほうで指定すべきと思う）
	static const float SMOKE_EFFECT_SIZE;

	// ベースクラスインスタンスの総量
	// enum と こちらか統一する必要あり
	static const int BILLBOARD_AMOUNT;

	EffectBase* effects[EFFECT_AMOUNT];
	BillboardBase** graphicEffects;

	int smokeGraphicHandle;
	int energyGraphicHandle;
};

