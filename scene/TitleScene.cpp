#include "TitleScene.h"
#include "CollisionManager.h";
#include "SphereCollider.h";
#include "SceneManager.h"
#include "PlayScene.h"
#include "Vector1.h"

#include "SafeDelete.h"

#include <cassert>

using namespace DirectX;
using namespace std;

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	// 基底クラスの初期化処理
	BaseScene::Initialize();

	// スプライトの生成処理
	if (!spriteCommon->LoadTexture(1, L"Resources/Title/TitleBG.png")) {
		assert(0);
		return;
	}
	if (!spriteCommon->LoadTexture(2, L"Resources/Title/Title.png")) {
		assert(0);
		return;
	}
	if (!spriteCommon->LoadTexture(3, L"Resources/Title/PUSH_PLESE_SPACE.png")) {
		assert(0);
		return;
	}
	if (!spriteCommon->LoadTexture(4, L"Resources/effect1.png")) {
		assert(0);
		return;
	}
	titleSprites["TitleBG"].reset(Sprite::Create(1));
	titleSprites["Title"].reset(Sprite::Create(2));
	titleSprites["PUSH_PLESE_SPACE"].reset(Sprite::Create(3));
	titleSprites["PUSH_PLESE_SPACE"]->SetPosition({ 0.0f, 100.0f });
}

void TitleScene::Finalize()
{
	// 基底クラスの終了処理
	BaseScene::Finalize();
}

void TitleScene::Update()
{
	// シーン切り替え
	if (input->TriggerKey(DIK_SPACE))
	{
		change = true;
		changeTimer.CountStart();
	}

	if (change)
	{
		XMFLOAT4 color = titleSprites["Title"]->GetColor();
		color.w = lerp(1.0f, 0.01f, changeTimer.GetRatio(changeSeconds));
		for (auto& sprite : titleSprites) {
			sprite.second->SetColor(color);
		}
		if (changeTimer.GetRatio(changeSeconds) == 1.0f) {
			sceneManager->SetNextScene(new PlayScene);
		}
	}

	for (auto& sprite : titleSprites) {
		sprite.second->Update();
	}
}

void TitleScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// 背景スプライトの描画処理
	BackDraw(cmdList);

	// 3Dオブジェクトの描画処理
	ObjectDraw(cmdList);

	// パーティクル描画処理
	particleMan->Draw(cmdList);

	// 前景スプライトの描画処理
	ForeDraw(cmdList);
}

void TitleScene::BackDraw(ID3D12GraphicsCommandList* cmdList)
{
	// 背景スプライト描画前処理
	spriteCommon->PreDraw();

	// 背景スプライト描画処理
	titleSprites["TitleBG"]->Draw();
	titleSprites["Title"]->Draw();
	titleSprites["PUSH_PLESE_SPACE"]->Draw();
}

void TitleScene::ObjectDraw(ID3D12GraphicsCommandList* cmdList)
{
#pragma region OBJの描画処理
	// 3Dオブジェクトの描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブジェクトの描画処理

	// 3Dオブジェクトの描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region FBXの描画処理
	// FBX3Dオブジェクトの描画前処理
	FbxObject3d::PreDraw(cmdList);

	// FBX3Dオブジェクトの描画処理



	// FBX3Dオブジェクトの描画後処理
	FbxObject3d::PostDraw();
#pragma endregion
}

void TitleScene::ForeDraw(ID3D12GraphicsCommandList* cmdList)
{
	// 前景スプライト描画前処理
	spriteCommon->PreDraw();

	// 前景スプライト描画処理
}
