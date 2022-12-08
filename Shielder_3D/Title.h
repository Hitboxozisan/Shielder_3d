#pragma once

#include "SceneBase.h"

#include <string>

class Title final : public SceneBase
{
public:
	enum State
	{
		DEMO,
		START
	};

	Title(SceneManager* const sceneManager);
	~Title();

	void Initialize();	//初期化処理
	void Finalize();	//終了処理
	void Activate();	//活性化処理
	void Deactivate();	//非活性化処理
	void Update();		//更新処理
	void Draw();		//描画処理

private:
	Title();
	Title(const Title&);
	void operator=(const Title&);

	static const std::string MOVIE_FOLDER_PATH;
	static const std::string DEMO_PATH;
	//static const std::string FILENAME_EXTENSION;
	static const std::string IMAGE_FOLDER_PATH;
	static const std::string TITLE_PATH;
	static const std::string KEY_PATH;
	static const std::string FILENAME_EXTENSION;

	static const int BLINKING_TIMES;				// ゲーム開始時のアイコン点滅回数

	State state;
	int movieGraphHandle;
	int titleImageHandle;
	int keyImageHandle;

	int alpha;
	int prevAlpha;
	int alphaAdd;
	int frame;

	//int blinkingTimes;
};

