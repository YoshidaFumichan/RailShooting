#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include "DebugText.h"
#include "Sprite.h"
#include "Object3d.h"
#include "FbxObject3d.h"
#include "FbxLoader.h"
#include "ParticleManager.h"

#include "SafeDelete.h"

class SceneManager;

/// <summary>
/// �t���[�����[�N
/// </summary>
class Framework
{
public: // �����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Framework();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual~Framework();

	/// <summary>
	/// ���s����
	/// </summary>
	virtual void Run();

protected: // �����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �I������
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// �Q�[�����[�v
	/// </summary>
	virtual void Loop();

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw();

protected: // �����o�֐�
	// WindowsAPI��ՃN���X
	WinApp* win = nullptr;
	// DirectX12��ՃN���X
	DirectXCommon* dxCommon = nullptr;
	// Input�N���X
	Input* input = nullptr;
	// Audio�N���X
	Audio* audio = nullptr;
	// DebugText�N���X
	DebugText* debugText = nullptr;
	// Scene�Ǘ��N���X
	SceneManager* sceneManager = nullptr;
};