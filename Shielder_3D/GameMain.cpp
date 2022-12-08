#include "Pch.h"
#include <chrono>
#include <thread>
#include <random>

#include "GameMain.h"

#include "KeyManager.h"
#include "SceneManager.h"
#include "Player.h"
#include "Character.h"
#include "Camera.h"
#include "ModelManager.h"

const string GameMain::IMAGE_FOLDER_PATH  = "Data/Image/";
const string GameMain::RESULT_PATH		  = "Result";
const string GameMain::FILENAME_EXTENSION = ".png";

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
	
}

void GameMain::Finalize()
{
	
}

void GameMain::Activate()
{
	

	frame = 0;
	state = START;
	pUpdate = &GameMain::UpdateStart;

#ifdef DEBUG
	state = START;
	pUpdate = &GameMain::UpdateStart;
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
/// �X�V����
/// </summary>
void GameMain::Update()
{
	// ESC�������ꂽ��^�C�g����
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_ESCAPE))
	{
		parent->SetNextScene(SceneManager::TITLE);
	}

	// �����������
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();	// ��Ԃ��Ƃ̍X�V����
	}

	++frame;
}

/// <summary>
/// �`�揈��
/// </summary>
void GameMain::Draw()
{
	

}

void GameMain::UpdateStart()
{


	
}

void GameMain::UpdateGame()
{
	
}

/// <summary>
/// �Q�[���I�[�o�[����
/// </summary>
void GameMain::UpdateGameOver()
{
	
}

void GameMain::UpdateFinish()
{
	
}

/// <summary>
/// ���U���g���
/// </summary>
void GameMain::UpdateResult()
{
	
}
