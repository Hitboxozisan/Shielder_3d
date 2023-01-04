#include "Pch.h"
#include <chrono>
#include <thread>
#include <random>

#include "GameMain.h"

#include "KeyManager.h"
#include "SceneManager.h"
#include "Field.h"
#include "Boss.h"
#include "Player.h"
#include "Character.h"
#include "Camera.h"
#include "CameraBase.h"
#include "CameraManager.h"
#include "ModelManager.h"
#include "UiManager.h"
#include "HitChecker.h"

const int	GameMain::PLAYER_AMOUNT     = 1;
const int	GameMain::ENEMY_AMOUNT      = 1;
const int	GameMain::CHARACTER_AMOUNT  = PLAYER_AMOUNT + ENEMY_AMOUNT;
const int   GameMain::MAX_METEOR_AMOUNT = 4;
const float GameMain::MAX_BULLET_AMOUNT = 8;

GameMain::GameMain(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	,state(State::START)
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

/// <summary>
/// ����������
/// </summary>
void GameMain::Initialize()
{
	// �J�����Ǘ��N���X�i�g�p���Ȃ��\����j
	cameraManager = new CameraManager();
	cameraManager->Initialize();
 	// �J�����N���X
	camera = new Camera();
	camera->Initialize();

	// �v���C���[�N���X
	player = new Player(camera);
	player->Initialize();

	// �{�X�N���X
	boss = new Boss(player);
	boss->Initialize();

	// �t�B�[���h�N���X
	field = new Field();
	field->Initialize();

	// Ui�Ǘ��N���X
	uiManager = new UiManager();
	uiManager->Initialize();

	hitChecker = new HitChecker();
}

/// <summary>
/// �I������
/// </summary>
void GameMain::Finalize()
{
	
}

/// <summary>
/// ����������
/// </summary>
void GameMain::Activate()
{
	player->Activate();						// �v���C���[�N���X����������
	boss->Activate();						// �{�X�N���X����������
	camera->Activate(player->GetPosition(),
					 boss->GetPosition());	// �J�����N���X����������
	uiManager->Activate();					// Ui�Ǘ��N���X����������

	frame = 0;
	state = State::START;
	pUpdate = &GameMain::UpdateStart;

#ifdef DEBUG
	state = State::GAME;
	pUpdate = &GameMain::UpdateGame;
#endif
}

/// <summary>
/// �񊈐�������
/// </summary>
void GameMain::Deactivate()
{
	for (int i = 0; i < CHARACTER_AMOUNT; ++i)
	{
		
	}

	state = State::START;
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
	field->Draw();
	player->Draw();
	boss->Draw();
	uiManager->Draw(state, 
					player->GetPosition(), 
					boss->GetPosition());
}

void GameMain::UpdateStart()
{
}

void GameMain::UpdateGame()
{
	//cameraManager->Update();
	player->Update();
	boss->Update();
	camera->Update(player->GetPosition(),
				   boss->GetPosition());
	// �����蔻�菈��
	// ���̏������ǂ��ɂ�������
	// ���͏��Ōʂɏ�������ׂ����H
	hitChecker->Check(player,
					  player->GetShieldPointer(),
					  boss);

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
