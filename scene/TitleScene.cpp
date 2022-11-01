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
	// ���N���X�̏���������
	BaseScene::Initialize();

	// �X�v���C�g�̐�������
	spriteCommon->LoadTexture(1, L"Resources/title/TITLE.png");
	titleSprite.reset(Sprite::Create(1));
	spriteCommon->LoadTexture(2, L"Resources/title/BLACK.png");
	BGSprite.reset(Sprite::Create(2));

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	camera->SetEye({ 0, 2, -10 });
}

void TitleScene::Finalize()
{
	// ���N���X�̏I������
	BaseScene::Finalize();
}

void TitleScene::Update()
{
	// �V�[���؂�ւ�
	if (input->TriggerKey(DIK_RETURN))
	{
		change = true;
	}
	if (change)
	{
		// �^�C�g���X�v���C�g�̐F���擾
		XMFLOAT4 color = titleSprite->GetColor();
		// �A���t�@�l������
		color.w -= 0.01;
		// �^�C�g���X�v���C�g�̐F��ݒ�
		titleSprite->SetColor(color);
		if (color.w <= 0)
		{
			sceneManager->SetNextScene(new PlayScene);
		}
	}

	titleSprite->Update();
	// �J�����X�V����
	camera->Update();
	// �S�Փ˃`�F�b�N
	collisionMan->CheckAllCollisions();
	// �p�[�e�B�N���X�V����
	particleMan->Update();
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
	BGSprite->Draw();
	titleSprite->Draw();
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
