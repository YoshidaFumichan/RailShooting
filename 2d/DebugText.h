#pragma once

#include "Sprite.h"

// �f�o�b�O������N���X�̒�`
class DebugText
{
private: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;

public: // �ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static DebugText* GetInstance();

private: // �ÓI�����o�ϐ�    
	static const int maxCharCount = 256;    // �ő啶����
	static const int fontWidth = 9;         // �t�H���g�摜��1�������̉���
	static const int fontHeight = 18;       // �t�H���g�摜��1�������̏c��
	static const int fontLineCount = 14;    // �t�H���g�摜��1�s���̕�����

public: // �����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	/// <summary>
	/// ������̕`��
	/// </summary>
	/// <param name="text">������</param>
	/// <param name="position">���W</param>
	/// <param name="scale">�傫��</param>
	void Print(const std::string& text, XMFLOAT2 position = { 0.0f,0.0f }, float scale = 1.0f);

	/// <summary>
	/// �S�`��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void DrawAll(ID3D12GraphicsCommandList* cmdList);

private: // �����o�ϐ�
	// �X�v���C�g�̋��ʕ���
	SpriteCommon* spriteCommon;
	// �X�v���C�g�f�[�^�̔z��
	Sprite* spriteDatas[maxCharCount];
	// �X�v���C�g�f�[�^�z��̓Y�����ԍ�
	int spriteIndex = 0;
};