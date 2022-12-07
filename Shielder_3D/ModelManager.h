#pragma once

#include <string>

using namespace std;

/// <summary>
/// ���f���}�l�[�W���[�N���X
/// </summary>
class ModelManager final
{
public:
	//���f���̎��
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

	static ModelManager& GetInstance();			// �C���X�^���X�̎擾

	const int& GetModelHandle(ModelKind modelKind)const;

private:

	void LoadAllModel();						// �S�Ẵ��f���̓ǂݍ���
	void DeleteAllModel();						// �S�Ẵ��f���̍폜

	static const string MODEL_FOLDER_PATH;
	static const string FIELD_PATH;
	static const string PLAYER_PATH;
	static const string ENEMY_PATH;
	static const string SHIELD_PATH;
	static const string BULLET_PATH;
	static const string METEOR_PATH;

	int modelHandle[MODEL_AMOUNT];
};

