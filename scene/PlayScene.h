#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Vector3.h"

#include <map>


/// <summary>
/// ゲームシーン
/// </summary>
class PlayScene : public BaseScene
{
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayScene();

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
	// モデルデータ配列
	std::unordered_map<string, Model_p> models;
	// プレイヤークラス
	unique_ptr <Player> player = nullptr;
	// エネミーデータ
	unique_ptr<Enemy> enemy = nullptr;
	// オブジェクトデータ配列
	std::unordered_map<string, Object3d_p> objects;

};