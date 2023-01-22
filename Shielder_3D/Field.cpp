#include "Pch.h"
#include "Field.h"

#include "ModelManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
Field::Field()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Field::~Field()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Field::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::FIELD));
	MV1SetScale(modelHandle, VGet(1.5f, 1.0f, 1.5f));														//モデルのサイズ変更

	position = VGet(0.0f, -80.0f, 0.0f);
	MV1SetPosition(modelHandle, position);
	//MV1SetRotationXYZ(modelHandle, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
}

/// <summary>
/// 描画処理
/// </summary>
void Field::Draw()
{
	MV1DrawModel(modelHandle);
}
