#include "TitleScene.h"
#include "Collision.h"
#include "CollisionManager.h";
#include "SphereCollider.h";
#include "SceneManager.h"
#include "PlayScene.h"

#include "Vector3.h"

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
	spriteCommon->LoadTexture(1, L"Resources/title/TITLE.png");
	titleSprite.reset(Sprite::Create(1));
	spriteCommon->LoadTexture(2, L"Resources/title/BLACK.png");
	BGSprite.reset(Sprite::Create(2));

	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetEye({ 0, 2, -10 });
}

void TitleScene::Finalize()
{
	// 基底クラスの終了処理
	BaseScene::Finalize();
}

void TitleScene::Update()
{
	// シーン切り替え
	if (input->TriggerKey(DIK_RETURN))
	{
		change = true;
	}
	if (change)
	{
		// タイトルスプライトの色を取得
		XMFLOAT4 color = titleSprite->GetColor();
		// アルファ値を加減
		color.w -= 0.01;
		// タイトルスプライトの色を設定
		titleSprite->SetColor(color);
		if (color.w <= 0)
		{
			sceneManager->SetNextScene(new PlayScene);
		}
	}

	titleSprite->Update();
	// カメラ更新処理
	camera->Update();
	// 全衝突チェック
	collisionMan->CheckAllCollisions();
	// パーティクル更新処理
	particleMan->Update();
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
	BGSprite->Draw();
	titleSprite->Draw();
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
