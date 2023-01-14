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
/// <param name="inPlayerHitPoint">�v���C���[��HitPoint</param>
void UiManager::Draw(GameMain::State state, 
					 VECTOR inPlayerPos, 
					 VECTOR inEnemyPos,
					 float inPlayerHitPoint,
					 float inEnemyHitPoint)
{
	++frame;
	switch (state)
	{
	case GameMain::State::START:
		
		break;

	case GameMain::State::GAME:
		// �v���C���[�̗͕̑`��
		DrawPlayerHitPoint(inPlayerHitPoint);
		DrawEnemyHitPoint(inEnemyHitPoint);
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

/// <summary>
/// �v���C���[��HitPoint��`�悷��
/// </summary>
/// <param name="inPlayerHitPoint">�v���C���[��HitPoint</param>
void UiManager::DrawPlayerHitPoint(float inPlayerHitPoint)
{
	// ���̕ӂ�͌�ɏC��
	// �ő�̗͂�100�Ƃ���
	float playerMaxHitPoint = 100.0f;
	int PosLX = 55; int PosLY = 980;
	int PosRX = PosLX + 490 * (inPlayerHitPoint / playerMaxHitPoint);
	int PosRY = 1015;

	int uiPosX = 300; int uiPosY = 1000;

	// �v���C���[��HitPoint��\��
	DrawBox(PosLX, PosLY, PosRX, PosRY, GetColor(0, 255, 0), TRUE);
	// HitPoint�Q�[�W�g�\��
	DrawRotaGraph(uiPosX, uiPosY, 0.8f, 0.0f, imageHandle[HP_PLAYER], TRUE);
}

/// <summary>
/// �G�l�~�[��HitPoint��`�悷��
/// </summary>
/// <param name="inEnemyHitPoint">�G�l�~�[��HitPoint</param>
void UiManager::DrawEnemyHitPoint(float inEnemyHitPoint)
{
	// ���̕ӂ�͌�ɏC��
	// �ő�̗͂�100�Ƃ���
	float enemyMaxHitPoint = 100.0f;
	int PosLX = 943; int PosLY = 90;
	int PosRX = PosLX + 750 * (inEnemyHitPoint / enemyMaxHitPoint);
	int PosRX2 = (PosLX - 10) + 750 * (-inEnemyHitPoint / enemyMaxHitPoint);
	int PosRY = 110;

	int uiPosX = 937; int uiPosY = 100;

	int subGreen = inEnemyHitPoint;

	// �G�l�~�[HitPoint�\��
	DrawBox(PosLX, PosLY, PosRX, PosRY, GetColor(246, 200 - subGreen, 0), TRUE);			// �E��
	DrawBox(PosLX - 10, PosLY, PosRX2, PosRY, GetColor(246, 200 - subGreen, 0), TRUE);		// ����
	// HitPoint�Q�[�W�g�\��
	DrawRotaGraph(uiPosX, uiPosY, 0.8, 0.0, imageHandle[HP_ENMEY], TRUE);
}




