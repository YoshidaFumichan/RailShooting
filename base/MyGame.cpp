#include "MyGame.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"

#include <cassert>

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::Run()
{
	// 基底クラスの実行処理
	Framework::Run();
}

void MyGame::Initialize()
{
	// 基底クラスの初期化処理
	Framework::Initialize();

	// シーン初期化処理
	sceneManager->Initialize(new TitleScene);
}

void MyGame::Finalize()
{
	// 基底クラスの終了処理
	Framework::Finalize();
}

void MyGame::Loop()
{
	// ゲームループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage() || input->PushKey(DIK_ESCAPE)) { break; }
		// 更新処理
		Update();
		// 描画処理
		Draw();
	}
}

void MyGame::Update()
{
	// Input更新処理
	input->Update();
	// Scene更新処理
	sceneManager->Update();
}

void MyGame::Draw()
{
	// フレームワークの描画処理
	Framework::Draw();
}
