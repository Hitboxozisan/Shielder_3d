#include "Pch.h"
#include <random>
#include "UiManager.h"

using std::string;

const std::string UiManager::GRAPHIC_FOLDER_PATH = "Data/Image/";
const std::string UiManager::UI_GRAPHIC_PATH = "ui";
const std::string UiManager::FILENAME_EXTENSION = ".png";

/// <summary>
/// �R���X�g���N�^
/// </summary>
UiManager::UiManager()
	:imageHandle()
	,frame(0)
	,alpha(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UiManager::~UiManager()
{
	if (imageHandle[0] != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
void UiManager::Initialize()
{
	string path = GRAPHIC_FOLDER_PATH + UI_GRAPHIC_PATH;
	string fullPath = path;

	alphaAdd = 4;

	for (int i = 0; i < IMAGE_AMOUNT; ++i)
	{
		fullPath = path + std::to_string(i) + FILENAME_EXTENSION;
		imageHandle[i] = LoadGraph(fullPath.c_str());

		if (imageHandle[i] < 0)
		{
			printfDx("�摜�ǂݍ��݂Ɏ��s_ui[%d]", i);
		}
	}
}

/// <summary>
/// �I������
/// </summary>
void UiManager::Finalize()
{
	for (int i = 0; i < IMAGE_AMOUNT; ++i)
	{
		DeleteGraph(imageHandle[i]);
		imageHandle[i] = NULL;
	}
}

/// <summary>
/// ����������
/// </summary>
void UiManager::Activate()
{
	frame = 0;
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="state"></param>
/// <param name="inPlayerPos">�v���C���[�̍��W</param>
/// <param name="inEnemyPos">�G�l�~�[�̍��W</param>
void UiManager::Draw(GameMain::State state, 
					 VECTOR inPlayerPos, 
					 VECTOR inEnemyPos)
{
	++frame;
	switch (state)
	{
	case GameMain::State::START:
		
		break;
	case GameMain::State::GAME:
		
		break;
	case GameMain::State::GAME_OVER:
		break;
	case GameMain::State::RESULT:

		break;
	default:
		break;
	}
}

/// <summary>
/// ���b�N�I�����̃J�[�\����\��
/// </summary>
void UiManager::DrawRockOnCursor()
{
	// �J�[�\���̕`��
	DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0f, 0.0f, imageHandle[ROCK_ON_CURSOR], TRUE);
}




