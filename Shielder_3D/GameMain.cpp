#include "Pch.h"
#include <chrono>
#include <thread>
#include <random>

#include "GameMain.h"

#include "KeyManager.h"
#include "SceneManager.h"
#include "Player.h"
#include "Character.h"
#include "CameraBase.h"
#include "CameraManager.h"
#include "ModelManager.h"

const int	GameMain::PLAYER_AMOUNT     = 1;
const int	GameMain::ENEMY_AMOUNT      = 1;
const int	GameMain::CHARACTER_AMOUNT  = PLAYER_AMOUNT + ENEMY_AMOUNT;
const int   GameMain::MAX_METEOR_AMOUNT = 4;
const float GameMain::MAX_BULLET_AMOUNT = 8;

GameMain::GameMain(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	,state(START)
	,pUpdate(nullptr)
	,frame()
	,alpha()
	,pushEnterAlpha()
	,alphaAdd(1)
{
}

GameMain::~GameMain()
{
	
}

void GameMain::Initialize()
{
	player = new Player();
	player->Initialize();

	cameraManager = new CameraManager();
	cameraManager->Initialize();
}

void GameMain::Finalize()
{
	
}

void GameMain::Activate()
{
	player->Activate();

	frame = 0;
	state = START;
	pUpdate = &GameMain::UpdateStart;

#ifdef DEBUG
	state = GAME;
	pUpdate = &GameMain::UpdateGame;
#endif
}

void GameMain::Deactivate()
{
	for (int i = 0; i < CHARACTER_AMOUNT; ++i)
	{
		
	}

	state = START;
}

/// <summary>
/// 更新処理
/// </summary>
void GameMain::Update()
{
	// ESCが押されたらタイトルへ
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_ESCAPE))
	{
		parent->SetNextScene(SceneManager::TITLE);
	}

	// 処理があれば
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();	// 状態ごとの更新処理
	}

	++frame;
}

/// <summary>
/// 描画処理
/// </summary>
void GameMain::Draw()
{
	player->Draw();
}

void GameMain::UpdateStart()
{
}

void GameMain::UpdateGame()
{
	player->Update();
	cameraManager->Update();
}

/// <summary>
/// ゲームオーバー処理
/// </summary>
void GameMain::UpdateGameOver()
{
	
}

void GameMain::UpdateFinish()
{
	
}

/// <summary>
/// リザルト画面
/// </summary>
void GameMain::UpdateResult()
{
	
}
