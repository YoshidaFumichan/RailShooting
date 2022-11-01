#pragma once
#include "MyGame.h"
#include "string"

class CollisionManager;

/// <summary>
/// シーン基底
/// </summary>
class BaseScene
{
protected: // エイリアス
	// std::を省略
	template <class T> using unique_ptr = std::unique_ptr<T>;
	using string = std::string;
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	using Object3d_p = unique_ptr<Object3d>;
	using Model_p = unique_ptr<Model>;
	using Sprite_p = unique_ptr<Sprite>;

public: // 静的メンバ関数
	/// <summary>
	/// DirectXCommon設定
	/// </summary>
	/// <param name="dxCommon">DirectXCommon</param>
	static void SetDirectXCommon(DirectXCommon* dxCommon) { BaseScene::dxCommon = dxCommon; }

public: // メンバ関数
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseScene() = default;
	
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;

protected: // 静的メンバ変数
	// DirectX基盤
	static DirectXCommon* dxCommon;

protected: // メンバ変数
	// スプライトの共通部分
	SpriteCommon* spriteCommon = nullptr;
	// パーティクルマネージャー
	ParticleManager* particleMan = nullptr;
	// 衝突マネージャー
	CollisionManager* collisionMan = nullptr;
	// デバッグテキスト
	DebugText* debugText = nullptr;
	// ライトグループ
	LightGroup* lightGroup = nullptr;
	// 入力
	Input* input = nullptr;
	// オーディオ
	Audio* audio = nullptr;
	// カメラ
	Camera* camera = nullptr;
	// Scene管理
	SceneManager* sceneManager;
};

