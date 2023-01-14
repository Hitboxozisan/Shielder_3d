#include "Pch.h"
#include <chrono>
#include <thread>
#include <random>
#include "Math3d.h"
#include "ChargeEnergyEffect.h"

using namespace Math3d;

const float ChargeEnergyEffect::DIFFUSION_SPEED			  = 30.0f;
const float ChargeEnergyEffect::MAX_DIFFUSION_DISTANCE	  = 50.0f;
const float ChargeEnergyEffect::MIN_DIFFUSION_DISTANCE	  = 15.0f;
const float ChargeEnergyEffect::INCREASE_SPEED_EACH_FRAME = 0.5f;

ChargeEnergyEffect::ChargeEnergyEffect()
{
}

ChargeEnergyEffect::~ChargeEnergyEffect()
{
}

void ChargeEnergyEffect::Activate(const VECTOR& inPosition, float inSize)
{
	//乱数用変数
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> next(MIN_DIFFUSION_DISTANCE, MAX_DIFFUSION_DISTANCE);
	std::uniform_real_distribution<> velocity1(0, 1);
	std::uniform_real_distribution<> velocity2(0, 1);
	std::uniform_real_distribution<> velocity3(0, 1);

	exist = true;
	existFrame = 100;
	position = inPosition;
	generationPosition = position;

	size = inSize;

	speed = 0.0f;
	velocity = VGet(velocity1(eng), velocity2(eng), velocity3(eng));
	opacity = 1.0f;
	diffusionDistance = next(eng);	//拡散距離を設定
	progressDistance = 0.0f;
}

/// <summary>
/// 拡散指定範囲まで粒子を拡散させる
/// </summary>
/// <returns></returns>
bool ChargeEnergyEffect::Diffusion()
{

	// 拡散指定距離まで粒子を拡散させる
	if (diffusionDistance >= progressDistance)
	{
		position = VAdd(position, VScale(velocity, DIFFUSION_SPEED));		// 拡散させる
		progressDistance = VSize(position - generationPosition);			// 発生位置からの距離を計算
		return false;
	}

	// 拡散させ終わった　　　
	return true;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="inPosition"></param>
void ChargeEnergyEffect::Draw(const VECTOR& inPosition)
{
	//存在しないなら処理しない
	if (exist == false)
	{
		return;
	}

	//SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255);	//ブレンドモード

	DrawBillboard3D(position, 0.5f, 0.5f, size, 0.0f, *graphicPointer, TRUE);		//画像の描画

	//SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255);	//ブレンドモード解除
}

/// <summary>
/// 更新処理
/// </summary>
void ChargeEnergyEffect::UpdateEach()
{
	// 拡散が完了したらエネミーの体幹ゲージ集まり始める
	if (Diffusion())
	{
		speed += INCREASE_SPEED_EACH_FRAME;
		VECTOR destination = ConvScreenPosToWorldPos(VGet(SCREEN_CENTER, 900.0f, 1.0f));
		// なぜかY軸の大きさが900に理由不明
		//VECTOR destination = VGet(SCREEN_CENTER, 900.0f, 0.0f);
		VECTOR force = destination - position;

		position = VAdd(position, VNorm(force) * speed);		//移動させる

		// 目的地に到達したら存在しない状態にする
		// X軸の誤差は考慮しない
		if (position.y >= destination.y)
		{
			exist = false;
		}
	}

	
}
