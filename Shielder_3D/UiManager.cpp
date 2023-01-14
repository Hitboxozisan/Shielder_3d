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
/// <param name="inPlayerHitPoint">プレイヤーのHitPoint</param>
void UiManager::Draw(GameMain::State state, 
					 VECTOR inPlayerPos, 
					 VECTOR inEnemyPos,
					 float inPlayerHitPoint,
					 float inEnemyHitPoint)
{
	++frame;
	switch (state)
	{
	case GameMain::State::START:
		
		break;

	case GameMain::State::GAME:
		// プレイヤーの体力描画
		DrawPlayerHitPoint(inPlayerHitPoint);
		DrawEnemyHitPoint(inEnemyHitPoint);
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

/// <summary>
/// プレイヤーのHitPointを描画する
/// </summary>
/// <param name="inPlayerHitPoint">プレイヤーのHitPoint</param>
void UiManager::DrawPlayerHitPoint(float inPlayerHitPoint)
{
	// この辺りは後に修正
	// 最大体力を100とする
	float playerMaxHitPoint = 100.0f;
	int PosLX = 55; int PosLY = 980;
	int PosRX = PosLX + 490 * (inPlayerHitPoint / playerMaxHitPoint);
	int PosRY = 1015;

	int uiPosX = 300; int uiPosY = 1000;

	// プレイヤーのHitPointを表示
	DrawBox(PosLX, PosLY, PosRX, PosRY, GetColor(0, 255, 0), TRUE);
	// HitPointゲージ枠表示
	DrawRotaGraph(uiPosX, uiPosY, 0.8f, 0.0f, imageHandle[HP_PLAYER], TRUE);
}

/// <summary>
/// エネミーのHitPointを描画する
/// </summary>
/// <param name="inEnemyHitPoint">エネミーのHitPoint</param>
void UiManager::DrawEnemyHitPoint(float inEnemyHitPoint)
{
	// この辺りは後に修正
	// 最大体力を100とする
	float enemyMaxHitPoint = 100.0f;
	int PosLX = 943; int PosLY = 90;
	int PosRX = PosLX + 750 * (inEnemyHitPoint / enemyMaxHitPoint);
	int PosRX2 = (PosLX - 10) + 750 * (-inEnemyHitPoint / enemyMaxHitPoint);
	int PosRY = 110;

	int uiPosX = 937; int uiPosY = 100;

	int subGreen = inEnemyHitPoint;

	// エネミーHitPoint表示
	DrawBox(PosLX, PosLY, PosRX, PosRY, GetColor(246, 200 - subGreen, 0), TRUE);			// 右側
	DrawBox(PosLX - 10, PosLY, PosRX2, PosRY, GetColor(246, 200 - subGreen, 0), TRUE);		// 左側
	// HitPointゲージ枠表示
	DrawRotaGraph(uiPosX, uiPosY, 0.8, 0.0, imageHandle[HP_ENMEY], TRUE);
}




