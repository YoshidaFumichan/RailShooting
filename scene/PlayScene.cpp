#include "PlayScene.h"
#include "Collision.h"
#include "CollisionManager.h";
#include "SphereCollider.h";

#include "SceneManager.h"
#include "TitleScene.h"

#include <cassert>

using namespace DirectX;
using namespace std;

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	// 基底クラスの初期化処理
	BaseScene::Initialize();

	// プレイヤーの生成処理
	models["Player"].reset(Model::CreateFromOBJ("chr_sword"));
	player.reset(Player::Create(models["Player"].get()));

	// エネミーの生成処理
	models["Enemy"].reset(Model::CreateFromOBJ("oopth3"));
	enemy.reset(Enemy::Create(models["Enemy"].get()));
	enemy->SetScale({ 0.5f, 0.5f, 0.5f });
	enemy->SetPosition({ 0,0,0 });
	enemy->SetTarget(player.get());

	// スカイドームの生成処理
	models["Stage"].reset(Model::CreateFromOBJ("Stage"));
	objects["Stage"].reset(Object3d::Create(models["Stage"].get()));
	objects["Stage"]->SetScale({ 3.0f, 3.0f, 3.0f, });
	objects["Stage"]->SetPosition({ 0.0f, 15.0f, 0.0f, });
}

void PlayScene::Finalize()
{
	// 基底クラスの終了処理
	BaseScene::Finalize();
}

void PlayScene::Update()
{
	// プレイヤーの更新処理
	player->Update();

	// エネミーの更新処理
	if (enemy) {
		enemy->Update();
		if (enemy->GetIsDelete()) {
			//enemy.get_deleter();
		}
	}
	// オブジェクトの更新処理
	for (auto& object : objects) {
		object.second->Update();
	}
	// カメラ更新処理
	camera->Update();
	// 全衝突チェック
	collisionMan->CheckAllCollisions();
	// パーティクル更新処理
	particleMan->Update();
}

void PlayScene::Draw()
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

void PlayScene::BackDraw(ID3D12GraphicsCommandList* cmdList)
{
	// 背景スプライト描画前処理
	spriteCommon->PreDraw();

	// 背景スプライト描画処理

}

void PlayScene::ObjectDraw(ID3D12GraphicsCommandList* cmdList)
{
#pragma region OBJの描画処理
	// 3Dオブジェクトの描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブジェクトの描画処理

	// プレイヤーの描画処理
	player->Draw();
	// エネミーの描画処理
	if (enemy) {
		enemy->Draw();
	}
	// オブジェクトの描画処理
	for (auto& object : objects) {
		object.second->Draw();
	}

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

void PlayScene::ForeDraw(ID3D12GraphicsCommandList* cmdList)
{
	// 前景スプライト描画前処理
	spriteCommon->PreDraw();

	// 前景スプライト描画処理
	player->SpriteDraw();
	enemy->SpriteDraw();
}