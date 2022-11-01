#pragma once
#include "Framework.h"

/// <summary>
/// ゲーム固有のクラス
/// </summary>
class MyGame : public Framework
{
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MyGame();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MyGame() override;

	/// <summary>
	/// 実行処理
	/// </summary>
	void Run() override;

private: // メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// ゲームループ
	/// </summary>
	void Loop() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};