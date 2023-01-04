#pragma once

#include "GameMain.h"
#include <string>

class UiManager
{
public:
	UiManager();
	~UiManager();

	void Initialize();						// 初期化処理
	void Finalize();						// 終了処理
	void Activate();						// 活性化処理
	void Draw(GameMain::State state,
			  VECTOR inPlayerPos,
			  VECTOR inEnemyPos);			// 描画処理

private:
	UiManager(const UiManager&);
	void operator=(const UiManager&);

	void DrawRockOnCursor();
	
	static const std::string GRAPHIC_FOLDER_PATH;
	static const std::string UI_GRAPHIC_PATH;
	static const std::string FILENAME_EXTENSION;

	// map で管理できそう？
	// 画像種類
	enum Image
	{
		ROCK_ON_CURSOR,
		IMAGE_AMOUNT
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

