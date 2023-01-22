#include "Pch.h"
#include <string>
#include "Background.h"

const float Background::SIZE = 1.0f;
const VECTOR Background::INITIAL_POSITION = VGet(0.0f, 0.0f, 0.0f);

Background::Background()
{
}

Background::~Background()
{
}

void Background::Initialize()
{
	std::string fullPath = "Data/Movie/background.mp4";
	img = LoadGraph(fullPath.c_str());
	position = INITIAL_POSITION;
}

void Background::Update()
{
}

void Background::Draw()
{
	//デモ映像再生終了したら最初に戻る
	if (GetMovieStateToGraph(img) == 0)
	{
		// 動画再生タイミングを指定
		SeekMovieToGraph(img, 0);
		//動画を再生できる状態にする
		PlayMovieToGraph(img);
	}
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, img, FALSE);

	// 背景描画（2D）
	//DrawGraph(position.x, position.y, img, TRUE);
}
