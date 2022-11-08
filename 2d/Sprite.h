#pragma once

#include <Windows.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <d3dx12.h>

#include "SpriteCommon.h"

/// <summary>
/// �X�v���C�g1�����̃N���X
/// </summary>
class Sprite
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // �ÓI�����o�ϐ�
	// �X�v���C�g�̊��
	static SpriteCommon* spriteCommon;
	// �f�o�C�X
	static ID3D12Device* dev;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;

public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI����������
	/// </summary>
	static void StaticInitialize(ID3D12Device* dev, ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �X�v���C�g����
	/// </summary>
	/// <param name="texNumber">�e�N�X�`���ԍ�</param>
	/// <param name="position">���W</param>
	/// <param name="color">�F</param>
	/// <param name="anchorpoint">�A���J�[�|�C���g</param>
	/// <param name="isFlipX">���E���]</param>
	/// <param name="isFlipY">�㉺���]</param>
	/// <returns>�������ꂽ�X�v���C�g</returns>
	static Sprite* Create(UINT texNumber, XMFLOAT2 position = { 0,0 }, XMFLOAT4 color = { 1, 1, 1, 1 }, XMFLOAT2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

public:  // �T�u�N���X
	/// <summary>
	/// ���_�f�[�^
	/// </summary>
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT2 uv;  // uv���W
	};

	/// <summary>
	/// �萔�o�b�t�@�p�f�[�^�\����
	/// </summary>
	struct ConstBufferData
	{
		XMFLOAT4 color; // �F (RGBA)
		XMMATRIX mat;   // �R�c�ϊ��s��
	};

public: // �����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Sprite();

	/// <summary>
	///  ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���_�o�b�t�@�̓]��
	/// </summary>
	void TransferVertexBuffer();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const XMFLOAT2& GetPosition() { return position; }

	/// <summary>
	/// �T�C�Y�̎擾
	/// </summary>
	/// <returns>�T�C�Y</returns>
	const XMFLOAT2& GetSize() { return size; }

	/// <summary>
	/// �F���擾
	/// </summary>
	/// <returns>�F</returns>
	const XMFLOAT4& GetColor() { return color; }

	/// <summary>
	/// �A���J�[�|�C���g�̎擾
	/// </summary>
	/// <returns>�A���J�[�|�C���g</returns>
	const XMFLOAT2& GetAnchorpoint() { return anchorpoint; }

	/// <summary>
	/// �e�N�X�`��������W�̎擾
	/// </summary>
	/// <returns>�e�N�X�`��������W</returns>
	const XMFLOAT2& GetTexLeftTop() { return texLeftTop; };

	/// <summary>
	/// �e�N�X�`���؂�o���T�C�Y�̎擾
	/// </summary>
	/// <returns>�e�N�X�`���؂�o���T�C�Y</returns>
	const XMFLOAT2& GetTexSize() { return texSize; }

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const XMFLOAT2& position) { this->position = position; }

	/// <summary>
	/// �傫���̐ݒ�
	/// </summary>
	/// <param name="size">�傫��</param>
	void SetSize(const XMFLOAT2& size) { this->size = size; TransferVertexBuffer(); }

	/// <summary>
	/// �F�̐ݒ�
	/// </summary>
	/// <param name="color">�F</param>
	void SetColor(const XMFLOAT4& color) { this->color = color; }

	/// <summary>
	/// �A���J�[�|�C���g�̐ݒ�
	/// </summary>
	/// <param name="anchorpoint">�A���J�[�|�C���g</param>
	void SetAnchorpoin(const XMFLOAT2& anchorpoint) { this->anchorpoint = anchorpoint; }

	/// <summary>
	/// �e�N�X�`��������W�̐ݒ�
	/// </summary>
	/// <param name="texLeftTop">�e�N�X�`��������W</param>
	void SetTexLeftTop(const XMFLOAT2& texLeftTop) { this->texLeftTop = texLeftTop; };

	/// <summary>
	/// �e�N�X�`���؂�o���T�C�Y�̐ݒ�
	/// </summary>
	/// <returns>�e�N�X�`���؂�o���T�C�Y</returns>
	void SetTexSize(const XMFLOAT2& texSize) { this->texSize = texSize; }

private: // �����o�ϐ�
	//���_�o�b�t�@;
	ComPtr<ID3D12Resource> vertBuff;
	//���_�o�b�t�@�r���[;
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�萔�o�b�t�@;
	ComPtr<ID3D12Resource> constBuff;
	// Z�����̉�]�p
	float rotation = 0.0f;
	// ���W
	XMFLOAT2 position = { 0,0 };
	// ���[���h�s��
	XMMATRIX matWorld;
	// �F(RGBA)
	XMFLOAT4 color = { 1, 1, 1, 1 };
	// �e�N�X�`���ԍ�
	UINT texNumber = 0;
	// �傫��
	XMFLOAT2 size = { 100, 100 };
	// �A���J�[�|�C���g
	XMFLOAT2 anchorpoint = { 0.5f, 0.5f };
	// ���E���]
	bool isFlipX = false;
	// �㉺���]
	bool isFlipY = false;
	// �e�N�X�`��������W
	XMFLOAT2 texLeftTop = { 0, 0 };
	// �e�N�X�`���؂�o���T�C�Y
	XMFLOAT2 texSize = { 100, 100 };
	// ��\��
	bool isInvisible = false;
};