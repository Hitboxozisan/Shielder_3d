#pragma once

#include "GameMain.h"
#include <string>

class UiManager
{
public:
	UiManager();
	~UiManager();

	void Initialize();						// ‰Šú‰»ˆ—
	void Finalize();						// I—¹ˆ—
	void Activate();						// Šˆ«‰»ˆ—
	void Draw(GameMain::State state,
			  VECTOR inPlayerPos,
			  VECTOR inEnemyPos);			// •`‰æˆ—

private:
	UiManager(const UiManager&);
	void operator=(const UiManager&);

	void DrawRockOnCursor();
	
	static const std::string GRAPHIC_FOLDER_PATH;
	static const std::string UI_GRAPHIC_PATH;
	static const std::string FILENAME_EXTENSION;

	// map ‚ÅŠÇ—‚Å‚«‚»‚¤H
	// ‰æ‘œí—Ş
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

