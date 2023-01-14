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
#include "EffectManager.h"
#include "Bullet.h"
#include "BulletCreater.h"
#include "ModelManager.h"
#include "UiManager.h"
#include "HitChecker.h"

const int	GameMain::PLAYER_AMOUNT     = 1;
const int	GameMain::ENEMY_AMOUNT      = 1;
const int	GameMain::CHARACTER_AMOUNT  = PLAYER_AMOUNT + ENEMY_AMOUNT;
const int   GameMain::MAX_METEOR_AMOUNT = 4;
const float GameMain::MAX_BULLET_AMOUNT = 8;

const std::string GameMain::PLAY_GRAPHIC_PATH = "Data/Image/playGraphicHandle.png";


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
	// �摜�ǂݍ���
	playGraphicHandle = LoadGraph(PLAY_GRAPHIC_PATH.c_str());

	// �G�t�F�N�g�Ǘ��N���X
	effectManager = new EffectManager();
	effectManager->Initialize();

	// �e�����N���X
	bulletCreater = new BulletCreater(&activeBullet, &deactiveBullet);

 	// �J�����N���X
	camera = new Camera();
	camera->Initialize();

	// �v���C���[�N���X
	player = new Player(camera);
	player->Initialize(effectManager);

	// �{�X�N���X
	boss = new Boss(player,
					bulletCreater);
	boss->Initialize(effectManager);

	// �o���b�g�N���X
	for (int i = 0; i < MAX_BULLET_AMOUNT; ++i)
	{
		deactiveBullet.push_back(new Bullet());
		deactiveBullet.back()->Initialize();
	}

	// �t�B�[���h�N���X
	field = new Field();
	field->Initialize();

	// Ui�Ǘ��N���X
	uiManager = new UiManager();
	uiManager->Initialize();

	// �����蔻��N���X
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
	player->Activate();								// �v���C���[�N���X����������
	boss->Activate();								// �{�X�N���X����������
	
	camera->Activate(player->GetPosition(),
					 boss->GetPosition());			// �J�����N���X����������
	//effectManager->Activate(player->GetPosition());	// �G�t�F�N�g�Ǘ��N���X����������
	uiManager->Activate();							// Ui�Ǘ��N���X����������

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
	// Effekseer�`��̂��ߓK���ȉ摜��`�悷��
	DrawGraph(0.0f, 0.0f, playGraphicHandle, FALSE);

	field->Draw();
	// �G�t�F�N�g�`��
	effectManager->Draw(player->GetPosition());
	// �v���C���[�`��
	player->Draw();
	// �G�l�~�[�`��
	boss->Draw();

	// �U���p�e�`��
	for (auto itr = activeBullet.begin(); itr != activeBullet.end(); ++itr)
	{
		(*itr)->Draw();
	}
	// �ҋ@�p�e�`��
	for (auto itr = deactiveBullet.begin(); itr != deactiveBullet.end(); ++itr)
	{
		(*itr)->Draw();
	}

	

	// Ui�`��
	uiManager->Draw(state, 
					player->GetPosition(), 
					boss->GetPosition(),
					player->GetHitPoint(),
					boss->GetHitPoint());
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

	// �e�̏����i�����͂�����������Y��ɂ������j
	// �A�N�e�B�u�Ȓe�̍X�V����
	for (auto itr = activeBullet.begin(); itr != activeBullet.end();)
	{
		// �����Ă������A�N�e�B�u���X�g
		if ((*itr)->Update() == false)
		{
			(*itr)->Deactivate();
			deactiveBullet.push_back(*itr);
			itr = activeBullet.erase(itr);
		}
		else
		{
			++itr;
		}
	}
	// �f�B�A�N�e�B�u�Ȓe�̍X�V����
	for (auto itr = deactiveBullet.begin(); itr != deactiveBullet.end();)
	{
		
		// ���˂��Ă��Ȃ��e�̓G�l�~�[�̎��͂���]������
		(*itr)->RotationAboutObject(*itr,
									boss->GetPosition(),
									deactiveBullet.size());
		++itr;
		
	}

	// �����蔻�菈��
	// ���̏������ǂ��ɂ�������
	// ���͏��Ōʂɏ�������ׂ����H
	hitChecker->Check(player,
					  player->GetShieldPointer(),
					  boss);

	// �G�t�F�N�g�X�V����
	effectManager->Update(player->GetPosition(),
						  boss->GetPosition());

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
