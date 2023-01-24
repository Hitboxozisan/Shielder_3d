#include "Pch.h"

#include "DeltaTime.h"
#include "EffectFootprints.h"

const int	EffectFootprints::DEFAULT_EXIST_FRAME = 60;
const float EffectFootprints::INCREASE_SIZE = 0.8f;

/// <summary>
/// コンストラクタ
/// </summary>
EffectFootprints::EffectFootprints()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
EffectFootprints::~EffectFootprints()
{
	// 処理なし
}

/// <summary>
/// 活性化処理
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inSize"></param>
void EffectFootprints::Activate(const VECTOR& inPosition, float inSize)
{
	position = inPosition;		// 発生位置を設定
	position.y = 0.0f;			// 地面からエフェクトを出す

	size = inSize;

	exist = true;
	existFrame = DEFAULT_EXIST_FRAME;

	opacity = 255.0f;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="inPosition"></param>
void EffectFootprints::Draw(const VECTOR& inPosition)
{
	//存在しないなら処理しない
	if (exist == false)
	{
		return;
	}

	// alpha値をいじるとUiがくそ明るくなるため不使用

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, opacity);
	DrawBillboard3D(position, 0.5f, 0.5f, size, 0.0f, *graphicPointer, TRUE);		//画像の描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// 更新処理
/// </summary>
void EffectFootprints::UpdateEach()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	// 徐々に透明にする
	opacity -= deltaTime;
}
