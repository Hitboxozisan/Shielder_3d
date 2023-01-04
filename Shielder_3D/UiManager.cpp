#include "Pch.h"
#include <random>
#include "UiManager.h"

using std::string;

const std::string UiManager::GRAPHIC_FOLDER_PATH = "Data/Image/";
const std::string UiManager::UI_GRAPHIC_PATH = "ui";
const std::string UiManager::FILENAME_EXTENSION = ".png";

/// <summary>
/// コンストラクタ
/// </summary>
UiManager::UiManager()
	:imageHandle()
	,frame(0)
	,alpha(0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
UiManager::~UiManager()
{
	if (imageHandle[0] != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void UiManager::Initialize()
{
	string path = GRAPHIC_FOLDER_PATH + UI_GRAPHIC_PATH;
	string fullPath = path;

	alphaAdd = 4;

	for (int i = 0; i < IMAGE_AMOUNT; ++i)
	{
		fullPath = path + std::to_string(i) + FILENAME_EXTENSION;
		imageHandle[i] = LoadGraph(fullPath.c_str());

		if (imageHandle[i] < 0)
		{
			printfDx("画像読み込みに失敗_ui[%d]", i);
		}
	}
}

/// <summary>
/// 終了処理
/// </summary>
void UiManager::Finalize()
{
	for (int i = 0; i < IMAGE_AMOUNT; ++i)
	{
		DeleteGraph(imageHandle[i]);
		imageHandle[i] = NULL;
	}
}

/// <summary>
/// 活性化処理
/// </summary>
void UiManager::Activate()
{
	frame = 0;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="state"></param>
/// <param name="inPlayerPos">プレイヤーの座標</param>
/// <param name="inEnemyPos">エネミーの座標</param>
void UiManager::Draw(GameMain::State state, 
					 VECTOR inPlayerPos, 
					 VECTOR inEnemyPos)
{
	++frame;
	switch (state)
	{
	case GameMain::State::START:
		
		break;
	case GameMain::State::GAME:
		
		break;
	case GameMain::State::GAME_OVER:
		break;
	case GameMain::State::RESULT:

		break;
	default:
		break;
	}
}

/// <summary>
/// ロックオン時のカーソルを表示
/// </summary>
void UiManager::DrawRockOnCursor()
{
	// カーソルの描画
	DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0f, 0.0f, imageHandle[ROCK_ON_CURSOR], TRUE);
}




