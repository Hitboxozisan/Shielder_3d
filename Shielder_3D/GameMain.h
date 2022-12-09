#pragma once

#include "SceneBase.h"
#include <vector>
#include <list>
#include <string>

class Player;
class CameraManager;

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

	enum State
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

	Player *player;
	CameraManager *cameraManager;

	//std::vector<BackgroundMeteor*> activeBackgroundMeteor;
	//std::vector<BackgroundMeteor*> deactiveBackgroundMeteor;
	//std::list<Bullet*> activeBullet;
	//std::list<Bullet*> deactiveBullet;

	// �e��Ԃɉ������X�V����
	void UpdateStart();
	void UpdateGame();
	void UpdateGameOver();
	void UpdateFinish();
	void UpdateResult();
	void (GameMain::* pUpdate)();

	int fontHandle;						// �t�H���g�p�n���h��
	int resultImageHandle;				// ���U���g��ʉ摜
	int pushEnterHandle;				// ���U���g��ʉ摜
	int lifeScore;						// �c��HitPoint�ɉ������X�R�A
	int trunkScore;						// �G�̑̊��Q�[�W�ɉ������X�R�A
	int totalScore;						// �g�[�^���X�R�A
	int frame;							// �o�߃t���[��

	int alpha;							// ALPHA�l�i�e�X�g�j
	int pushEnterAlpha;
	int alphaAdd;
};