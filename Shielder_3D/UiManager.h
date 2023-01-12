#pragma once

#include "GameMain.h"
#include <string>

class UiManager
{
public:
	UiManager();
	~UiManager();

	void Initialize();						// ����������
	void Finalize();						// �I������
	void Activate();						// ����������
	void Draw(GameMain::State state,
			  VECTOR inPlayerPos,
			  VECTOR inEnemyPos,
			  float inPlayerHitPoint,
			  float inEnemyHitPoint);		// �`�揈��

private:
	UiManager(const UiManager&);
	void operator=(const UiManager&);

	void DrawRockOnCursor();
	void DrawPlayerHitPoint(float inPlayerHitPoint);	// �v���C���[��HitPoint��`�悷��
	void DrawEnemyHitPoint(float inEnemyHitPoint);		// �G�l�~�[��HitPoint��`�悷��
	
	static const std::string GRAPHIC_FOLDER_PATH;
	static const std::string UI_GRAPHIC_PATH;
	static const std::string FILENAME_EXTENSION;

	// map �ŊǗ��ł������H
	// �摜���
	enum Image
	{
		ROCK_ON_CURSOR,		// ���b�N�I���J�[�\��
		HP_PLAYER,			// �v���C���[��HitPoint
		HP_ENMEY,			// �{�X��HitPoint
		
		IMAGE_AMOUNT		// �摜����
	};

	/*struct EnemyTrunkPosition
	{
		int GaugeX;
		int GaugeY;
		int boxX;
		int boxY;
		int prevGaugeX;
		int prevGaugeY;
		int prevBoxX;
		int prevBoxY;
	};*/

	int imageHandle[IMAGE_AMOUNT];
	int frame;
	int alpha;
	int alphaAdd;


};

