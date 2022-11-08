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
	// ���N���X�̏���������
	BaseScene::Initialize();

	// �v���C���[�̐�������
	models["Player"].reset(Model::CreateFromOBJ("chr_sword"));
	player.reset(Player::Create(models["Player"].get()));

	// �G�l�~�[�̐�������
	models["Enemy"].reset(Model::CreateFromOBJ("oopth3"));
	enemy.reset(Enemy::Create(models["Enemy"].get()));
	enemy->SetScale({ 0.5f, 0.5f, 0.5f });
	enemy->SetPosition({ 0,0,0 });
	enemy->SetTarget(player.get());

	// �X�J�C�h�[���̐�������
	models["Stage"].reset(Model::CreateFromOBJ("Stage"));
	objects["Stage"].reset(Object3d::Create(models["Stage"].get()));
	objects["Stage"]->SetScale({ 3.0f, 3.0f, 3.0f, });
	objects["Stage"]->SetPosition({ 0.0f, 15.0f, 0.0f, });
}

void PlayScene::Finalize()
{
	// ���N���X�̏I������
	BaseScene::Finalize();
}

void PlayScene::Update()
{
	// �v���C���[�̍X�V����
	player->Update();

	// �G�l�~�[�̍X�V����
	if (enemy) {
		enemy->Update();
		if (enemy->GetIsDelete()) {
			//enemy.get_deleter();
		}
	}
	// �I�u�W�F�N�g�̍X�V����
	for (auto& object : objects) {
		object.second->Update();
	}
	// �J�����X�V����
	camera->Update();
	// �S�Փ˃`�F�b�N
	collisionMan->CheckAllCollisions();
	// �p�[�e�B�N���X�V����
	particleMan->Update();
}

void PlayScene::Draw()
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

void PlayScene::BackDraw(ID3D12GraphicsCommandList* cmdList)
{
	// �w�i�X�v���C�g�`��O����
	spriteCommon->PreDraw();

	// �w�i�X�v���C�g�`�揈��

}

void PlayScene::ObjectDraw(ID3D12GraphicsCommandList* cmdList)
{
#pragma region OBJ�̕`�揈��
	// 3D�I�u�W�F�N�g�̕`��O����
	Object3d::PreDraw(cmdList);

	// 3D�I�u�W�F�N�g�̕`�揈��

	// �v���C���[�̕`�揈��
	player->Draw();
	// �G�l�~�[�̕`�揈��
	if (enemy) {
		enemy->Draw();
	}
	// �I�u�W�F�N�g�̕`�揈��
	for (auto& object : objects) {
		object.second->Draw();
	}

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

void PlayScene::ForeDraw(ID3D12GraphicsCommandList* cmdList)
{
	// �O�i�X�v���C�g�`��O����
	spriteCommon->PreDraw();

	// �O�i�X�v���C�g�`�揈��
	player->SpriteDraw();
	enemy->SpriteDraw();
}