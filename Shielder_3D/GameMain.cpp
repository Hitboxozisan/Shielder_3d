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
/// 初期化処理
/// </summary>
void GameMain::Initialize()
{
	// 画像読み込み
	playGraphicHandle = LoadGraph(PLAY_GRAPHIC_PATH.c_str());
	// 画像読み込み（ここはあとで別クラスで処理させるべきか）
	resultImageHandle = LoadGraph("Data/Image/Result.png");

	// エフェクト管理クラス
	effectManager = new EffectManager();
	effectManager->Initialize();

	// 弾生成クラス
	bulletCreater = new BulletCreater(&activeBullet, &deactiveBullet);

	// カメラクラス
	camera = new Camera();
	
	// プレイヤークラス
	player = new Player(camera);
	player->Initialize(effectManager);

	// ボスクラス
	boss = new Boss(player,
					bulletCreater);
	boss->Initialize(effectManager);

	camera->Initialize(boss);

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

	background = new Background();
	background->Initialize();

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
	player->Activate();								// プレイヤークラス活性化処理
	boss->Activate();								// ボスクラス活性化処理
	
	camera->Activate(player->GetPosition(),
					 boss->GetPosition());			// カメラクラス活性化処理

	
	effectManager->CreateBackgroundEffect(ZERO_VECTOR);	// 背景エフェクトを生成
	uiManager->Activate();								// Ui管理クラス活性化処理

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
	// Effekseer描画のため適当な画像を描画する
	DrawGraph(0.0f, 0.0f, playGraphicHandle, FALSE);
	// 背景映像描画
	background->Draw();

	field->Draw();
	// エフェクト描画
	effectManager->Draw(player->GetPosition());
	
	// プレイヤー描画
	player->Draw();
	// エネミー描画
	boss->Draw();
	
	// 攻撃用弾描画
	for (auto itr = activeBullet.begin(); itr != activeBullet.end(); ++itr)
	{
		(*itr)->Draw();
	}
	// 待機用弾描画
	for (auto itr = deactiveBullet.begin(); itr != deactiveBullet.end(); ++itr)
	{
		//(*itr)->Draw();
	}

	

	// Ui描画
	uiManager->Draw(state, 
					player->GetPosition(), 
					boss->GetPosition(),
					player->GetHitPoint(),
					boss->GetHitPoint());

	// 画面をフェードアウト
	if (state == State::GAME_OVER || state == State::RESULT || state == State::FINISH)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// リザルト画面の表示
	if (state == State::RESULT)
	{
		// リザルト画像描画
		DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, resultImageHandle, TRUE);
		pushEnterAlpha += alphaAdd;						// 徐々に透明にする
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
	// デバッグ情報
	DrawFormatString(50.0f, 50.0f, GetColor(255, 255, 255), "PlayerX: %f", player->GetPosition().x);
	DrawFormatString(50.0f, 70.0f, GetColor(255, 255, 255), "PlayerZ: %f", player->GetPosition().z);
#endif // DEBUG

	
}

void GameMain::UpdateStart()
{
	camera->Update(player->GetPosition(),
				   boss->GetPosition());
	// 初期位置にカメラが移動したらゲームを開始する
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

	// 弾の処理（ここはもうちょっと綺麗にしたい）
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
	// ディアクティブな弾の更新処理
	for (auto itr = deactiveBullet.begin(); itr != deactiveBullet.end();)
	{
		
		// 発射していない弾はエネミーの周囲を回転させる
		(*itr)->RotationAboutObject(*itr,
									boss->GetPosition(),
									deactiveBullet.size());
		++itr;
		
	}


	// 当たり判定処理
	// 盾の処理をどうにかしたい
	// 盾は盾で個別に処理するべきか？
	hitChecker->Check(player,
					  player->GetShieldPointer(),
					  boss,
					  &activeBullet);

	// エフェクト更新処理
	effectManager->Update(player->GetPosition(),
						  boss->GetPosition());

	// プレイヤーが死んだ場合はゲームオーバーに
	if (!player->IsAlive())
	{
		state = State::GAME_OVER;
		pUpdate = &GameMain::UpdateGameOver;
	}

}

/// <summary>
/// ゲームオーバー処理
/// </summary>
void GameMain::UpdateGameOver()
{
	// 徐々に暗くしていく
	alpha++;

	// alpah値を増加させたら
	if (alpha >= 200)
	{
		alpha = 200;			//これ以上増減しないようにする
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
/// リザルト画面
/// </summary>
void GameMain::UpdateResult()
{
	float score = Random::GetInstance().GetRandomFloat(0, 9999999);

	//一定フレーム経過するまで
	//各スコアをランダムな数値を表示させる
	//フレームで判断ではなくカウントで判断のほうが良いかも
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


	//スペースキーもしくは一定時間経過でタイトル画面に移行する
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_RETURN) ||
		frame >= 600)
	{
		Deactivate();
		//SoundManager::GetInstance().StopBgm();
		parent->SetNextScene(SceneManager::TITLE);
	}
}
