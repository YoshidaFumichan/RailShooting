#include "SceneManager.h"

#include "TitleScene.h"
#include "PlayScene.h"

SceneManager* SceneManager::GetInstance()
{
	// �C���X�^���X�̐���
	static SceneManager instance;

	return &instance;
}

void SceneManager::Initialize(BaseScene* startScene)
{
	// �V�[���̎擾
	scene = startScene;
	// �V�[���̏�����
	scene->Initialize();
}

void SceneManager::Finalize()
{
	// �V�[���̏I������
	scene->Finalize();
	// �V�[���̉��
	safe_delete(scene);
}

void SceneManager::Update()
{
	// ���̃V�[���������Ă�����
	if (nextScene) {
		// ���݂̃V�[���I������
		scene->Finalize();
		// ���݂̃V�[�����
		safe_delete(scene);
		// ���̃V�[���Ɉړ�
		scene = nextScene;
		// ���̃V�[���̏�����
		scene->Initialize();
		nextScene = nullptr;
	}

	// �V�[���X�V����
	scene->Update();
}

void SceneManager::Draw()
{
	// �V�[���`�揈��
	scene->Draw();
}
