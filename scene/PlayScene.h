#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Vector3.h"

#include <map>


/// <summary>
/// �Q�[���V�[��
/// </summary>
class PlayScene : public BaseScene
{
public: // �����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayScene();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;

private: // �����o�֐�
	/// <summary>
	/// �w�i�X�v���C�g�̕`�揈��
	/// </summary>
	void BackDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 3D�I�u�W�F�N�g�̕`�揈��
	/// </summary>
	void ObjectDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �O�i�X�v���C�g�̕`�揈��
	/// </summary>
	void ForeDraw(ID3D12GraphicsCommandList* cmdList);

private: // �����o�ϐ�
	// ���f���f�[�^�z��
	std::unordered_map<string, Model_p> models;
	// �v���C���[�N���X
	unique_ptr <Player> player = nullptr;
	// �G�l�~�[�f�[�^
	unique_ptr<Enemy> enemy = nullptr;
	// �I�u�W�F�N�g�f�[�^�z��
	std::unordered_map<string, Object3d_p> objects;

};