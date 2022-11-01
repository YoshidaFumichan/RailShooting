#pragma once
#include "BaseScene.h"

/// <summary>
/// �V�[���Ǘ�
/// </summary>
class SceneManager
{

public: // �ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static SceneManager* GetInstance();

private: // �����o�֐�
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;	
	~SceneManager() = default;
	SceneManager& operator=(const SceneManager&) = delete;

public: // �����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(BaseScene* fastScene);

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���̃V�[���̗\��ݒ�
	/// </summary>
	/// <param name="baseScene">���̃V�[��</param>
	void SetNextScene(BaseScene* nextScene) { this->nextScene = nextScene; }


private: // �����o�ϐ�
	// ���݂̃V�[��
	BaseScene* scene = nullptr;
	// ���̃V�[��
	BaseScene* nextScene = nullptr;
};