#include "BaseScene.h"
#include "CollisionManager.h";
#include "SceneManager.h";

DirectXCommon* BaseScene::dxCommon = nullptr;

void BaseScene::Initialize()
{
	// NULL検出
	assert(dxCommon);

	this->dxCommon = dxCommon;

	// インスタンス取得
	debugText = DebugText::GetInstance();
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	spriteCommon = SpriteCommon::GetInstance();
	particleMan = ParticleManager::GetInstance();
	collisionMan = CollisionManager::GetInstance();
	sceneManager = SceneManager::GetInstance();

	// カメラ生成処理
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	Object3d::SetCamera(camera);
	FbxObject3d::SetCamera(camera);
	particleMan->SetCamera(camera);

	// ライトグループの生成処理
	lightGroup = LightGroup::Create();
	Object3d::SetLightGroup(lightGroup);

}

void BaseScene::Finalize()
{
	safe_delete(camera);
	safe_delete(lightGroup);
}
