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
	//�f���f���Đ��I��������ŏ��ɖ߂�
	if (GetMovieStateToGraph(img) == 0)
	{
		// ����Đ��^�C�~���O���w��
		SeekMovieToGraph(img, 0);
		//������Đ��ł����Ԃɂ���
		PlayMovieToGraph(img);
	}
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, img, FALSE);

	// �w�i�`��i2D�j
	//DrawGraph(position.x, position.y, img, TRUE);
}
