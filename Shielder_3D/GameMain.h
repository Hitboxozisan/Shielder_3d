#pragma once

#include "SceneBase.h"
#include <vector>
#include <list>
#include <string>

class CameraManager;
class Player;
class Boss;
class Camera;
class Field;
class UiManager;
class HitChecker;

class GameMain final : public SceneBase
{
public:
	GameMain(SceneManager* const sceneManager);
	~GameMain();

	void Initialize();
	void Finalize();
	void Activate();
	void Deactivate();
	void Update();
	void Draw();

	enum class State
	{
		START,
		GAME,
		GAME_OVER,
		FINISH,
		RESULT
	};

private:
	GameMain();
	GameMain(const GameMain&);
	void operator=(const GameMain&);

	static const int   PLAYER_AMOUNT;
	static const int   ENEMY_AMOUNT;
	static const int   CHARACTER_AMOUNT;
	static const int   MAX_METEOR_AMOUNT;
	static const float MAX_BULLET_AMOUNT;
	
	State state;

	CameraManager *cameraManager;
	Player *player;
	Boss* boss;
	Camera* camera;
	Field* field;
	UiManager* uiManager;
	HitChecker* hitChecker;

	//std::vector<BackgroundMeteor*> activeBackgroundMeteor;
	//std::vector<BackgroundMeteor*> deactiveBackgroundMeteor;
	//std::list<Bullet*> activeBullet;
	//std::list<Bullet*> deactiveBullet;

	// 各状態に応じた更新処理
	void UpdateStart();
	void UpdateGame();
	void UpdateGameOver();
	void UpdateFinish();
	void UpdateResult();
	void (GameMain::* pUpdate)();

	int fontHandle;						// フォント用ハンドル
	int resultImageHandle;				// リザルト画面画像
	int pushEnterHandle;				// リザルト画面画像
	int lifeScore;						// 残りHitPointに応じたスコア
	int trunkScore;						// 敵の体幹ゲージに応じたスコア
	int totalScore;						// トータルスコア
	int frame;							// 経過フレーム

	int alpha;							// ALPHA値（テスト）
	int pushEnterAlpha;
	int alphaAdd;
};