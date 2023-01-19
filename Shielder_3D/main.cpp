#include "Pch.h"
#include "Dxlib.h"

#include "SceneManager.h"
#include "DeltaTime.h"
#include "KeyManager.h"
#ifdef DEBUG
#include "WriteLineToField.h"
#endif // DEBUG


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(IS_WINDOW_MODE);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BIT_DEPTH);
	SetWaitVSyncFlag(TRUE);

	SetUseLighting(TRUE);

	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//Effekseer������������
	//�����͉�ʂɕ\������ő�p�[�e�B�N����
	if (Effekseer_Init(2200) == -1)
	{
		DxLib_End();
		return -1;
	}


	// Effekseer����������
	
	//DxLib_Init�֐��̑O�ɒu����FPS��������
	SetDrawScreen(DX_SCREEN_BACK);
	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	// Effekseer��2D�`��̐ݒ������B
	//Effekseer_Set2DSetting(SCREEN_WIDTH, SCREEN_HEIGHT);
	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);
	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);
	
	

#ifdef DEBUG
	WriteLineToField writeLineToField;
#endif // DEBUG

	SceneManager* sceneManager = new SceneManager();
	sceneManager->Initialize();

	DeltaTime::GetInstance().SetCount();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		DeltaTime::GetInstance().InstrumentationDeltaTime();	// deltaTime�v��
		KeyManager::GetInstance().Update();						// ���͏���

		sceneManager->Update();									// �e�V�[���ɉ������X�V����


		ClearDrawScreen();										// ��ʍX�V����


		sceneManager->Draw();									// �e�V�[���ɉ������`�揈��
#ifdef DEBUG
		writeLineToField.WriteLine();							// �t�B�[���h�Ƀ��C����`��
#endif // DEBUG
		ScreenFlip();
	}

	// Effekseer���I������
	Effkseer_End();

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}