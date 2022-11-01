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
	// ���N���X�̎��s����
	Framework::Run();
}

void MyGame::Initialize()
{
	// ���N���X�̏���������
	Framework::Initialize();

	// �V�[������������
	sceneManager->Initialize(new TitleScene);
}

void MyGame::Finalize()
{
	// ���N���X�̏I������
	Framework::Finalize();
}

void MyGame::Loop()
{
	// �Q�[�����[�v
	while (true) {
		// ���b�Z�[�W����
		if (win->ProcessMessage() || input->PushKey(DIK_ESCAPE)) { break; }
		// �X�V����
		Update();
		// �`�揈��
		Draw();
	}
}

void MyGame::Update()
{
	// Input�X�V����
	input->Update();
	// Scene�X�V����
	sceneManager->Update();
}

void MyGame::Draw()
{
	// �t���[�����[�N�̕`�揈��
	Framework::Draw();
}
