#include "Pch.h"
#include "Title.h"

#include "GameDefine.h"
#include "SceneManager.h"
#include "KeyManager.h"

using namespace std;

const string Title::MOVIE_FOLDER_PATH = "Data/Movie/";
const string Title::DEMO_PATH = "Demo.mp4";
//const string Title::FILENAME_EXTENSION = ".mp4";
const string Title::IMAGE_FOLDER_PATH = "Data/Image/";
const string Title::TITLE_PATH = "Title";
const string Title::KEY_PATH = "Push_Space";
const string Title::FILENAME_EXTENSION = ".png";

//const int Title::BLINKING_TIMES = 6;

Title::Title(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	,state(DEMO)
	,movieGraphHandle()
	,frame(0)
{
}

Title::~Title()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Title::Initialize()
{
	string path = MOVIE_FOLDER_PATH;
	string fullpath = path + DEMO_PATH;
	movieGraphHandle = LoadGraph(fullpath.c_str());
	if (movieGraphHandle < 0)
	{
		printfDx("動画読み込みに失敗_demo");
	}

	alpha = 255;
	alphaAdd = -3;
	//blinkingTimes = BLINKING_TIMES;

	path = IMAGE_FOLDER_PATH;
	fullpath = path + TITLE_PATH + FILENAME_EXTENSION;
	titleImageHandle = LoadGraph(fullpath.c_str());
	if (titleImageHandle < 0)
	{
		printfDx("error");
	}
	
	path = IMAGE_FOLDER_PATH;
	fullpath = path + KEY_PATH + FILENAME_EXTENSION;
	keyImageHandle = LoadGraph(fullpath.c_str());
	if (keyImageHandle < 0)
	{
		printfDx("error");
	}

	
}

void Title::Finalize()
{

}

void Title::Activate()
{
	state = DEMO;
	alphaAdd = -3;
	frame = 0;

}

void Title::Deactivate()
{
	// 動画を停止にする
	PauseMovieToGraph(movieGraphHandle);
}

void Title::Update()
{


	if (KeyManager::GetInstance().CheckJustPressed(KEY_INPUT_SPACE))
	{
		alphaAdd *= 10;
		frame = 0;
		state = START;
	}
	
	if (state == START && frame >= 90)
	{
		PauseMovieToGraph(movieGraphHandle);
		parent->SetNextScene(SceneManager::GAME_MAIN);
		return;
	}

	++frame;
}

/// <summary>
/// タイトル描画処理
/// </summary>
void Title::Draw()
{
	// デモ映像再生終了したら最初に戻る
	if (GetMovieStateToGraph(movieGraphHandle) == 0)
	{
		// 動画再生タイミングを指定
		SeekMovieToGraph(movieGraphHandle, 0);
		//動画を再生できる状態にする
		PlayMovieToGraph(movieGraphHandle);
	}
	
	// デモ映像を再生する
	//DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, movieGraphHandle, FALSE);

	//タイトル名描画
	DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, titleImageHandle, TRUE);
	
	// " Push Space "を点滅させる
	alpha += alphaAdd;

	if (alpha <= 0 || alpha >= 255)
	{
		alphaAdd = -alphaAdd;
		alpha = prevAlpha;
	}
	
	prevAlpha = alpha;

	// " Push Space "を描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, keyImageHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}
