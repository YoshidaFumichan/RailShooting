#include "Framework.h"
#include "SceneManager.h"

#include "BaseScene.h"
#include <cassert>

Framework::Framework()
{
}

Framework::~Framework()
{
}

void Framework::Run()
{
	// 初期化処理
	Initialize();
	// ゲームループ
	Loop();
	// 終了処理
	Finalize();
}

void Framework::Initialize()
{
	// WindowsAPIの初期化処理
	win = new WinApp();
	win->Initialize();

	// DirectXの初期化処理
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(win);

	// Inputクラス初期化処理
	// インスタンス取得
	input = Input::GetInstance();
	if (!input->Initialize(win)) {
		assert(0);
		return;
	}

	// Audio初期化処理
	// インスタンス取得
	audio = Audio::GetInstance();
	if (!audio->Initialize()) {
		assert(0);
		return;
	}

	// SpriteCommon共通初期化
	SpriteCommon::GetInstance()->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), WinApp::window_width, WinApp::window_height);

	// Sprite静的初期化処理
	Sprite::StaticInitialize(dxCommon->GetDevice(), dxCommon->GetCommandList());

	// DebugText初期化処理
	// インスタンスの取得
	debugText = DebugText::GetInstance();
	debugText->Initialize();

	// ライトグループ初期化処理
	LightGroup::StaticInitialize(dxCommon->GetDevice());

	// Object3D静的初期化処理
	Object3d::StaticInitialize(dxCommon->GetDevice());

	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());

	// FbxObject3D静的初期化処理
	FbxObject3d::StaticInitialize(dxCommon->GetDevice());

	// パーティクル共通初期化処理
	ParticleManager::GetInstance()->Initialize(dxCommon->GetDevice());

	// シーンの静的初期化
	BaseScene::SetDirectXCommon(dxCommon);

	// シーンマネージャーのインスタンスを取得
	sceneManager = SceneManager::GetInstance();
}

void Framework::Finalize()
{
	// Audioの終了処理
	audio->Finalize();
	// デバッグテキストの終了処理
	debugText->Finalize();
	// シーンマネージャー終了処理
	sceneManager->Finalize();
	// DirectX基盤解放
	safe_delete(dxCommon);
	// WindowsAPIの終了処理
	win->Finalize();
	// WindowsAPI解放
	safe_delete(win);
}

void Framework::Loop()
{
	// ゲームループ
	while (true)
	{
		// メッセージ処理
		if (win->ProcessMessage() || input->PushKey(DIK_ESCAPE)) { break; }
		// 更新処理
		Update();
		// 描画処理
		Draw();
	}
}

void Framework::Update()
{
	// Input更新処理
	input->Update();
	// Scene更新処理
	sceneManager->Update();

}

void Framework::Draw()
{
	// コマンドリストを取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// 描画前処理
	dxCommon->PreDraw();
	// 描画後処理
	//// Scene描画処理
	sceneManager->Draw();
	// デバッグテキストの全描画
	debugText->DrawAll(cmdList);
	dxCommon->PostDraw();
}