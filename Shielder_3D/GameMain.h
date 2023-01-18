#pragma once

#include "SceneBase.h"
#include <vector>
#include <list>
#include <string>

class CameraManager;
class Player;
class Boss;
class Bullet;
class BulletCreater;
class Sword;
class Camera;
class EffectManager;
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
		START,			// �J�n��
		GAME,			// �Q�[����
		GAME_OVER,		// �Q�[���I�[�o�[
		FINISH,			// �I��
		RESULT			// ���ʉ��
	};

private:
	GameMain();
	GameMain(const GameMain&);
	void operator=(const GameMain&);

	static const int   PLAYER_AMOUNT;
	static const int   ENEMY_AMOUNT;
	static const int   CHARACTER_AMOUNT;
	static const int   MAX_METEOR_AMOUNT;
	static const float MAX_BULLET_AMOUNT;			// �e�̍ő吔

	static const std::string PLAY_GRAPHIC_PATH;
	
	State state;

	CameraManager *cameraManager;
	Player *player;
	Boss* boss;
	BulletCreater* bulletCreater;
	Sword* sword;
	Camera* camera;
	EffectManager* effectManager;
	Field* field;
	UiManager* uiManager;
	HitChecker* hitChecker;

	//std::vector<BackgroundMeteor*> activeBackgroundMeteor;
	//std::vector<BackgroundMeteor*> deactiveBackgroundMeteor;
	std::list<Bullet*> activeBullet;
	std::list<Bullet*> deactiveBullet;

	// �e��Ԃɉ������X�V����
	void UpdateStart();
	void UpdateGame();
	void UpdateGameOver();
	void UpdateFinish();
	void UpdateResult();
	void (GameMain::* pUpdate)();

	int playGraphicHandle;				// �G�t�F�N�g�`��p�̉摜
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