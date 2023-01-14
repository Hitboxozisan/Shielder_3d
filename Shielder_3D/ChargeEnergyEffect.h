#pragma once

#include "BillboardBase.h"

class ChargeEnergyEffect final : public BillboardBase
{
public:
	ChargeEnergyEffect();
	~ChargeEnergyEffect();

	void Activate(const VECTOR& inPosition, float inSize);	// 活性化処理
	bool Diffusion();										// エフェクトを拡散させる
	void Draw(const VECTOR& inPosition);					// 描画

	void UpdateEach();										// 粒子をゲージまで集める
private:
	//static const float INITIAL_SIZE;						// 初期サイズ
	static const float DIFFUSION_SPEED;						// 拡散速度
	static const float MAX_DIFFUSION_DISTANCE;				// 最大拡散距離
	static const float MIN_DIFFUSION_DISTANCE;				// 最小拡散距離
	static const float INCREASE_SPEED_EACH_FRAME;			// 1フレームごと速度の増加量

	float size;			// 画像の大きさ

	VECTOR generationPosition;		// 発生位置
	VECTOR velocity;				// 現在の速度、加速度、向き
	float  speed;					// 移動速度（velocityとの違いは？）
	float  opacity;					// 不透明度
	float  diffusionDistance;		// 拡散距離
	float  progressDistance;		// 進行距離
};

