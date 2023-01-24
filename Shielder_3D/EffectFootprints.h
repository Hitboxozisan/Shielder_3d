#pragma once

#include "BillboardBase.h"

/// <summary>
/// 足跡エフェクト
/// 移動後にオブジェクトの足元にエフェクトを表示する
/// </summary>
class EffectFootprints final : public BillboardBase
{
public:
	EffectFootprints();
	~EffectFootprints();

	void Activate(const VECTOR& inPosition, float inSize);
	void Draw(const VECTOR& inPosition);

	void UpdateEach();

private:
	static const int DEFAULT_EXIST_FRAME;			//存在できる初期フレーム数
	static const float INCREASE_SIZE;				//1フレームで増加するサイズ

	float size;				//画像の大きさ

	float opacity;			//不透明度
};

