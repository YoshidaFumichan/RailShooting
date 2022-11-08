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
	// ���N���X�̏���������
	BaseScene::Initialize();

	// �X�v���C�g�̐�������
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
	// ���N���X�̏I������
	BaseScene::Finalize();
}

void TitleScene::Update()
{
	// �V�[���؂�ւ�
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
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �w�i�X�v���C�g�̕`�揈��
	BackDraw(cmdList);

	// 3D�I�u�W�F�N�g�̕`�揈��
	ObjectDraw(cmdList);

	// �p�[�e�B�N���`�揈��
	particleMan->Draw(cmdList);

	// �O�i�X�v���C�g�̕`�揈��
	ForeDraw(cmdList);
}

void TitleScene::BackDraw(ID3D12GraphicsCommandList* cmdList)
{
	// �w�i�X�v���C�g�`��O����
	spriteCommon->PreDraw();

	// �w�i�X�v���C�g�`�揈��
	titleSprites["TitleBG"]->Draw();
	titleSprites["Title"]->Draw();
	titleSprites["PUSH_PLESE_SPACE"]->Draw();
}

void TitleScene::ObjectDraw(ID3D12GraphicsCommandList* cmdList)
{
#pragma region OBJ�̕`�揈��
	// 3D�I�u�W�F�N�g�̕`��O����
	Object3d::PreDraw(cmdList);

	// 3D�I�u�W�F�N�g�̕`�揈��

	// 3D�I�u�W�F�N�g�̕`��㏈��
	Object3d::PostDraw();
#pragma endregion

#pragma region FBX�̕`�揈��
	// FBX3D�I�u�W�F�N�g�̕`��O����
	FbxObject3d::PreDraw(cmdList);

	// FBX3D�I�u�W�F�N�g�̕`�揈��



	// FBX3D�I�u�W�F�N�g�̕`��㏈��
	FbxObject3d::PostDraw();
#pragma endregion
}

void TitleScene::ForeDraw(ID3D12GraphicsCommandList* cmdList)
{
	// �O�i�X�v���C�g�`��O����
	spriteCommon->PreDraw();

	// �O�i�X�v���C�g�`�揈��
}
