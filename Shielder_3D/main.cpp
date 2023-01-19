#include "Pch.h"
#include "Dxlib.h"

#include "SceneManager.h"
#include "DeltaTime.h"
#include "KeyManager.h"
#ifdef DEBUG
#include "WriteLineToField.h"
#endif // DEBUG


// プログラムは WinMain から始まります
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

	//Effekseerを初期化する
	//引数は画面に表示する最大パーティクル数
	if (Effekseer_Init(2200) == -1)
	{
		DxLib_End();
		return -1;
	}


	// Effekseer初期化処理
	
	//DxLib_Init関数の前に置くとFPSが落ちる
	SetDrawScreen(DX_SCREEN_BACK);
	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	// Effekseerに2D描画の設定をする。
	//Effekseer_Set2DSetting(SCREEN_WIDTH, SCREEN_HEIGHT);
	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);
	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);
	
	

#ifdef DEBUG
	WriteLineToField writeLineToField;
#endif // DEBUG

	SceneManager* sceneManager = new SceneManager();
	sceneManager->Initialize();

	DeltaTime::GetInstance().SetCount();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		DeltaTime::GetInstance().InstrumentationDeltaTime();	// deltaTime計測
		KeyManager::GetInstance().Update();						// 入力処理

		sceneManager->Update();									// 各シーンに応じた更新処理


		ClearDrawScreen();										// 画面更新処理


		sceneManager->Draw();									// 各シーンに応じた描画処理
#ifdef DEBUG
		writeLineToField.WriteLine();							// フィールドにラインを描画
#endif // DEBUG
		ScreenFlip();
	}

	// Effekseerを終了する
	Effkseer_End();

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}