#include "BaseScene.h"
#include "CollisionManager.h";
#include "SceneManager.h";

DirectXCommon* BaseScene::dxCommon = nullptr;

void BaseScene::Initialize()
{
	// NULL���o
	assert(dxCommon);

	this->dxCommon = dxCommon;

	// �C���X�^���X�擾
	debugText = DebugText::GetInstance();
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	spriteCommon = SpriteCommon::GetInstance();
	particleMan = ParticleManager::GetInstance();
	collisionMan = CollisionManager::GetInstance();
	sceneManager = SceneManager::GetInstance();

	// �J������������
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	Object3d::SetCamera(camera);
	FbxObject3d::SetCamera(camera);
	particleMan->SetCamera(camera);

	// ���C�g�O���[�v�̐�������
	lightGroup = LightGroup::Create();
	Object3d::SetLightGroup(lightGroup);

}

void BaseScene::Finalize()
{
	safe_delete(camera);
	safe_delete(lightGroup);
}
