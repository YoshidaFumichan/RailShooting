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
/// フレームワーク
/// </summary>
class Framework
{
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Framework();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual~Framework();

	/// <summary>
	/// 実行処理
	/// </summary>
	virtual void Run();

protected: // メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// ゲームループ
	/// </summary>
	virtual void Loop();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();

protected: // メンバ関数
	// WindowsAPI基盤クラス
	WinApp* win = nullptr;
	// DirectX12基盤クラス
	DirectXCommon* dxCommon = nullptr;
	// Inputクラス
	Input* input = nullptr;
	// Audioクラス
	Audio* audio = nullptr;
	// DebugTextクラス
	DebugText* debugText = nullptr;
	// Scene管理クラス
	SceneManager* sceneManager = nullptr;
};