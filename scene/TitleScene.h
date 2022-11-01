#pragma once

#include "BaseScene.h"


/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public BaseScene
{
public: // �����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TitleScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TitleScene();

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
	// �^�C�g����ʂ̃X�v���C�g
	Sprite_p titleSprite = nullptr;
	// �w�i�p�X�v���C�g
	Sprite_p BGSprite = nullptr;
	// �V�[���؂�ւ��p�t���O
	bool change = false;

};