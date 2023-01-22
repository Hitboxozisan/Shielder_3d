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
#include "EnemyManager.h"
#include "ModelManager.h"
#include "UiManager.h"
#include "Background.h"
#include "HitChecker.h"
#include "Random.h"

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
	// �摜�ǂݍ��݁i�����͂��ƂŕʃN���X�ŏ���������ׂ����j
	resultImageHandle = LoadGraph("Data/Image/Result.png");

	// �G�t�F�N�g�Ǘ��N���X
	effectManager = new EffectManager();
	effectManager->Initialize();

	// �e�����N���X
	bulletCreater = new BulletCreater(&activeBullet, &deactiveBullet);

	// �J�����N���X
	camera = new Camera();
	
	// �v���C���[�N���X
	player = new Player(camera);
	player->Initialize(effectManager);

	// �{�X�N���X
	boss = new Boss(player,
					bulletCreater);
	boss->Initialize(effectManager);

	camera->Initialize(boss);

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

	background = new Background();
	background->Initialize();

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

	
	effectManager->CreateBackgroundEffect(ZERO_VECTOR);	// �w�i�G�t�F�N�g�𐶐�
	uiManager->Activate();								// Ui�Ǘ��N���X����������

	frame = 0;
	alpha = 0;

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
	// �w�i�f���`��
	background->Draw();

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
		//(*itr)->Draw();
	}

	

	// Ui�`��
	uiManager->Draw(state, 
					player->GetPosition(), 
					boss->GetPosition(),
					player->GetHitPoint(),
					boss->GetHitPoint());

	// ��ʂ��t�F�[�h�A�E�g
	if (state == State::GAME_OVER || state == State::RESULT || state == State::FINISH)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// ���U���g��ʂ̕\��
	if (state == State::RESULT)
	{
		// ���U���g�摜�`��
		DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, resultImageHandle, TRUE);
		pushEnterAlpha += alphaAdd;						// ���X�ɓ����ɂ���
		if (pushEnterAlpha == 0 || pushEnterAlpha == 255)
		{
			alphaAdd = -alphaAdd;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, pushEnterAlpha);
		DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, pushEnterHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, pushEnterAlpha);
		DrawFormatStringToHandle(950, 400, GetColor(255, 255, 255), fontHandle, "%d", lifeScore);
		DrawFormatStringToHandle(950, 560, GetColor(255, 255, 255), fontHandle, "%d", trunkScore);
		DrawFormatStringToHandle(950, 870, GetColor(255, 255, 255), fontHandle, "%d", totalScore);
	}

#ifdef DEBUG
	// �f�o�b�O���
	DrawFormatString(50.0f, 50.0f, GetColor(255, 255, 255), "PlayerX: %f", player->GetPosition().x);
	DrawFormatString(50.0f, 70.0f, GetColor(255, 255, 255), "PlayerZ: %f", player->GetPosition().z);
#endif // DEBUG

	
}

void GameMain::UpdateStart()
{
	camera->Update(player->GetPosition(),
				   boss->GetPosition());
	// �����ʒu�ɃJ�������ړ�������Q�[�����J�n����
	if (camera->IsMovedCameraToInitialPosition())
	{
		state = State::GAME;
		pUpdate = &GameMain::UpdateGame;
	}
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
					  boss,
					  &activeBullet);

	// �G�t�F�N�g�X�V����
	effectManager->Update(player->GetPosition(),
						  boss->GetPosition());

	// �v���C���[�����񂾏ꍇ�̓Q�[���I�[�o�[��
	if (!player->IsAlive())
	{
		state = State::GAME_OVER;
		pUpdate = &GameMain::UpdateGameOver;
	}

}

/// <summary>
/// �Q�[���I�[�o�[����
/// </summary>
void GameMain::UpdateGameOver()
{
	// ���X�ɈÂ����Ă���
	alpha++;

	// alpah�l�𑝉���������
	if (alpha >= 200)
	{
		alpha = 200;			//����ȏ㑝�����Ȃ��悤�ɂ���
		state = State::RESULT;
		frame = 0;
		pUpdate = &GameMain::UpdateResult;
		//parent->SetNextScene(SceneManager::RESULT);
		//return;
	}

	effectManager->Update(player->GetPosition(), boss->GetPosition());
}

void GameMain::UpdateFinish()
{
	
}

/// <summary>
/// ���U���g���
/// </summary>
void GameMain::UpdateResult()
{
	float score = Random::GetInstance().GetRandomFloat(0, 9999999);

	//���t���[���o�߂���܂�
	//�e�X�R�A�������_���Ȑ��l��\��������
	//�t���[���Ŕ��f�ł͂Ȃ��J�E���g�Ŕ��f�̂ق����ǂ�����
	if (frame <= 90)
	{
		lifeScore = score;
		trunkScore = score;
		totalScore = score;
	}
	else if (frame <= 120)
	{
		//SoundManager::GetInstance().SetSePlayFlag(SoundManager::DECIDE_SCORE);
		lifeScore = player->GetHitPoint() * 15000;
		trunkScore = score;
		totalScore = score;
	}
	else if (frame <= 150)
	{
		//SoundManager::GetInstance().SetSePlayFlag(SoundManager::DECIDE_SCORE);
		trunkScore = boss->GetHitPoint() * 20000;
		totalScore = score;
	}
	else
	{
		//SoundManager::GetInstance().SetSePlayFlag(SoundManager::DECIDE_SCORE);
		totalScore = lifeScore + trunkScore;
	}


	//�X�y�[�X�L�[�������͈�莞�Ԍo�߂Ń^�C�g����ʂɈڍs����
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_RETURN) ||
		frame >= 600)
	{
		Deactivate();
		//SoundManager::GetInstance().StopBgm();
		parent->SetNextScene(SceneManager::TITLE);
	}
}
