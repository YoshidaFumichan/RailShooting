#pragma once
#include "Framework.h"

/// <summary>
/// �Q�[���ŗL�̃N���X
/// </summary>
class MyGame : public Framework
{
public: // �����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MyGame();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MyGame() override;

	/// <summary>
	/// ���s����
	/// </summary>
	void Run() override;

private: // �����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �Q�[�����[�v
	/// </summary>
	void Loop() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;
};