#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>

#include "PipelineSet.h"

/// <summary>
/// �X�v���C�g�̋��ʕ���
/// </summary>
class SpriteCommon
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMMATRIX = DirectX::XMMATRIX;

public: // �ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static SpriteCommon* GetInstance();

public: // �ÓI�����o�ϐ�
	// �e�N�X�`���̍ő喇��
	static const int spriteSRVCount = 512;

public: // �����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="dev">�f�o�C�X</param>
	/// <param name="cmdList">�R�}���h���X�g</param>
	/// <param name="window_width">�E�B���h�E����</param>
	/// <param name="window_height">�E�B���h�E�c��</param>
	void Initialize(ID3D12Device* dev, ID3D12GraphicsCommandList* cmdList, int window_width, int window_height);

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="texNumber">�e�N�X�`���ԍ�</param>
	/// <param name="filename">�e�N�X�`���̖��O</param>
	bool LoadTexture(UINT texNumber, const wchar_t* filename);

	/// <summary>
	/// �`��O����
	/// </summary>
	void PreDraw();

	/// <summary>
	/// �f�X�N���v�^�q�[�v�̃Z�b�g
	/// </summary>
	void SetDescriptorHeaps();

	/// <summary>
	/// ���[�g�f�X�N���v�^�e�[�u���̐ݒ�
	/// </summary>
	/// <param name="rootParameterIndex">���[�g�p�����[�^�[�ԍ�</param>
	/// <param name="texNumber">�e�N�X�`���ԍ�</param>
	void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, UINT texNumber);

	/// <summary>
	/// �e�N�X�`���̎擾
	/// </summary>
	/// <param name="texNumber">�e�N�X�`���ԍ�</param>
	/// <returns>�e�N�X�`��</returns>
	ID3D12Resource* GetTexBuff(int texNumber);

	/// <summary>
	/// �ˉe�s��̎擾
	/// </summary>
	/// <returns>�ˉe�s��</returns>
	const XMMATRIX& GetMatProjection() { return matProjection; }

private: // �����o�֐�
	/// <summary>
	/// �O���t�B�b�N�X�p�C�v���C���̐���
	/// </summary>
	void CreateGraphicsPipeline();

	SpriteCommon() = default;
	SpriteCommon(const SpriteCommon&) = delete;
	~SpriteCommon() = default;
	SpriteCommon& operator=(const SpriteCommon&) = delete;
private: // �����o�ϐ�
	// �f�o�C�X
	ID3D12Device* dev = nullptr;
	// DX�R�}���h���X�g
	ID3D12GraphicsCommandList* cmdList = nullptr;
	// �p�C�v���C���Z�b�g
	PipelineSet pipelineSet;
	// �ˉe�s��
	XMMATRIX matProjection{};
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// �e�N�X�`���o�b�t�@�̔z��
	ComPtr<ID3D12Resource> texBuff[spriteSRVCount];
};