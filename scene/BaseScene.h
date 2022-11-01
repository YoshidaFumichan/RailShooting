#pragma once
#include "MyGame.h"
#include "string"

class CollisionManager;

/// <summary>
/// �V�[�����
/// </summary>
class BaseScene
{
protected: // �G�C���A�X
	// std::���ȗ�
	template <class T> using unique_ptr = std::unique_ptr<T>;
	using string = std::string;
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	using Object3d_p = unique_ptr<Object3d>;
	using Model_p = unique_ptr<Model>;
	using Sprite_p = unique_ptr<Sprite>;

public: // �ÓI�����o�֐�
	/// <summary>
	/// DirectXCommon�ݒ�
	/// </summary>
	/// <param name="dxCommon">DirectXCommon</param>
	static void SetDirectXCommon(DirectXCommon* dxCommon) { BaseScene::dxCommon = dxCommon; }

public: // �����o�֐�
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~BaseScene() = default;
	
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �I������
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() = 0;

protected: // �ÓI�����o�ϐ�
	// DirectX���
	static DirectXCommon* dxCommon;

protected: // �����o�ϐ�
	// �X�v���C�g�̋��ʕ���
	SpriteCommon* spriteCommon = nullptr;
	// �p�[�e�B�N���}�l�[�W���[
	ParticleManager* particleMan = nullptr;
	// �Փ˃}�l�[�W���[
	CollisionManager* collisionMan = nullptr;
	// �f�o�b�O�e�L�X�g
	DebugText* debugText = nullptr;
	// ���C�g�O���[�v
	LightGroup* lightGroup = nullptr;
	// ����
	Input* input = nullptr;
	// �I�[�f�B�I
	Audio* audio = nullptr;
	// �J����
	Camera* camera = nullptr;
	// Scene�Ǘ�
	SceneManager* sceneManager;
};

