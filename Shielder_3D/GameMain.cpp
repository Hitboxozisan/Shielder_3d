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
/// 初期化処理
/// </summary>
void GameMain::Initialize()
{
	// 弾生成クラス
	bulletCreater = new BulletCreater(&activeBullet, &deactiveBullet);

 	// カメラクラス
	camera = new Camera();
	camera->Initialize();

	// プレイヤークラス
	player = new Player(camera);
	player->Initialize();

	// ボスクラス
	boss = new Boss(player,
					bulletCreater);
	boss->Initialize();

	// バレットクラス
	for (int i = 0; i < MAX_BULLET_AMOUNT; ++i)
	{
		deactiveBullet.push_back(new Bullet());
		deactiveBullet.back()->Initialize();
	}

	// フィールドクラス
	field = new Field();
	field->Initialize();

	// Ui管理クラス
	uiManager = new UiManager();
	uiManager->Initialize();

	// 当たり判定クラス
	hitChecker = new HitChecker();
}

/// <summary>
/// 終了処理
/// </summary>
void GameMain::Finalize()
{
	
}

/// <summary>
/// 活性化処理
/// </summary>
void GameMain::Activate()
{
	player->Activate();						// プレイヤークラス活性化処理
	boss->Activate();						// ボスクラス活性化処理
	
	camera->Activate(player->GetPosition(),
					 boss->GetPosition());	// カメラクラス活性化処理
	uiManager->Activate();					// Ui管理クラス活性化処理

	frame = 0;
	state = State::START;
	pUpdate = &GameMain::UpdateStart;

#ifdef DEBUG
	state = State::GAME;
	pUpdate = &GameMain::UpdateGame;
#endif
}

/// <summary>
/// 非活性化処理
/// </summary>
void GameMain::Deactivate()
{
	for (int i = 0; i < CHARACTER_AMOUNT; ++i)
	{
		
	}

	state = State::START;
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
	field->Draw();
	player->Draw();
	boss->Draw();

	// 攻撃用弾描画
	for (auto itr = activeBullet.begin(); itr != activeBullet.end(); ++itr)
	{
		(*itr)->Draw();
	}
	// 待機用弾描画
	for (auto itr = deactiveBullet.begin(); itr != deactiveBullet.end(); ++itr)
	{
		(*itr)->Draw();
	}

	// Ui描画
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

	// アクティブな弾の更新処理
	for (auto itr = activeBullet.begin(); itr != activeBullet.end();)
	{
		// 消えていたら非アクティブリスト
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

	// 当たり判定処理
	// 盾の処理をどうにかしたい
	// 盾は盾で個別に処理するべきか？
	hitChecker->Check(player,
					  player->GetShieldPointer(),
					  boss);

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
