#pragma once

#include <string>

using namespace std;

/// <summary>
/// モデルマネージャークラス
/// </summary>
class ModelManager final
{
public:
	//モデルの種類
	enum ModelKind
	{
		FIELD = 0,
		PLAYER,
		ENEMY,
		SHIELD,
		BULLET,
		METEOR,

		MODEL_AMOUNT
	};

	ModelManager();
	~ModelManager();

	static ModelManager& GetInstance();			// インスタンスの取得

	const int& GetModelHandle(ModelKind modelKind)const;

private:

	void LoadAllModel();						// 全てのモデルの読み込み
	void DeleteAllModel();						// 全てのモデルの削除

	static const string MODEL_FOLDER_PATH;
	static const string FIELD_PATH;
	static const string PLAYER_PATH;
	static const string ENEMY_PATH;
	static const string SHIELD_PATH;
	static const string BULLET_PATH;
	static const string METEOR_PATH;

	int modelHandle[MODEL_AMOUNT];
};

