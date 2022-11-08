#pragma once
#include "BaseScene.h"
#include "Timer.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public BaseScene
{
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private: // メンバ関数
	/// <summary>
	/// 背景スプライトの描画処理
	/// </summary>
	void BackDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 3Dオブジェクトの描画処理
	/// </summary>
	void ObjectDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 前景スプライトの描画処理
	/// </summary>
	void ForeDraw(ID3D12GraphicsCommandList* cmdList);

private: // メンバ変数
	// タイトル画面のスプライト
	std::map<string, Sprite_p> titleSprites;
	// シーン切り替え用フラグ
	bool change = false;
	Timer changeTimer;
	float changeSeconds = 3.0f;
	XMFLOAT2 whiteSize = {};
};