#include "Pch.h"
#include "ModelManager.h"

const string ModelManager::MODEL_FOLDER_PATH = "Data/Model/";
const string ModelManager::FIELD_PATH		 = "Field/TestField.mv1";
const string ModelManager::PLAYER_PATH		 = "Player/Player.mv1";
const string ModelManager::ENEMY_PATH		 = "Enemy/Enemy.mv1";
const string ModelManager::SHIELD_PATH		 = "Shield/Shield.mv1";
const string ModelManager::BULLET_PATH		 = "Bullet/Bullet.mv1";
const string ModelManager::METEOR_PATH		 = "Meteor/Meteor.mv1";

/// <summary>
/// コンストラクタ
/// </summary>
ModelManager::ModelManager()
	:modelHandle()
{
	LoadAllModel();
}

/// <summary>
/// デストラクタ
/// </summary>
ModelManager::~ModelManager()
{
	DeleteAllModel();
}

/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns></returns>
ModelManager& ModelManager::GetInstance()
{
	static ModelManager ModelManager;
	return ModelManager;
}

/// <summary>
/// 全てのモデルの読み込み
/// </summary>
void ModelManager::LoadAllModel()
{
	string fullPath = MODEL_FOLDER_PATH + FIELD_PATH;
	modelHandle[FIELD] = MV1LoadModel(fullPath.c_str());

	fullPath = MODEL_FOLDER_PATH + PLAYER_PATH;
	modelHandle[PLAYER] = MV1LoadModel(fullPath.c_str());

	fullPath = MODEL_FOLDER_PATH + ENEMY_PATH;
	modelHandle[ENEMY] = MV1LoadModel(fullPath.c_str());

	fullPath = MODEL_FOLDER_PATH + SHIELD_PATH;
	modelHandle[SHIELD] = MV1LoadModel(fullPath.c_str());

	fullPath = MODEL_FOLDER_PATH + BULLET_PATH;
	modelHandle[BULLET] = MV1LoadModel(fullPath.c_str());

	fullPath = MODEL_FOLDER_PATH + FIELD_PATH;
	modelHandle[FIELD] = MV1LoadModel(fullPath.c_str());

	fullPath = MODEL_FOLDER_PATH + METEOR_PATH;
	modelHandle[METEOR] = MV1LoadModel(fullPath.c_str());

	// エラー処理
	for (int i = 0; i < MODEL_AMOUNT; ++i)
	{
		if (modelHandle[i] < 0)
		{
			printfDx("モデルデータの読み込み失敗_[%d]\n", i);
		}
	}
}

/// <summary>
/// 全てのモデルの削除
/// </summary>
void ModelManager::DeleteAllModel()
{
	for (int i = 0; i < MODEL_AMOUNT; ++i)
	{
		if (modelHandle[i] != NULL)
		{
			MV1DeleteModel(modelHandle[i]);
			modelHandle[i] = NULL;
		}
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="modelKind"></param>
/// <returns></returns>
const int& ModelManager::GetModelHandle(ModelKind modelKind) const
{
	if (modelKind == MODEL_AMOUNT)
	{
		printfDx("不正な値を参照しています_ModelManager");
		return modelHandle[0];
	}

	return modelHandle[modelKind];
}