#pragma once
#include "Object3d.h"
#include "Sprite.h"
#include "PlayerBullet.h"
#include "Vector3.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public Object3d
{
public: // 静的メンバ関数
	/// <summary>
	/// プレイヤー生成
	/// </summary>
	/// <returns>3Dオブジェクト</returns>
	static Player* Create(Model* model = nullptr);

private: // メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	bool Initialize()override;

	/// <summary>
	/// 弾の発射処理
	/// </summary>
	void Shot();

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// カメラ座標を更新
	/// </summary>
	void UpdateCameraPosition();

public: // メンバ関数
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw()override;

	/// <summary>
	/// スプライト描画処理
	/// </summary>
	void SpriteDraw();

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	void OnCollision(const CollisionInfo& info)override;

private: // メンバ変数
	// HPバー用スプライト
	std::unique_ptr<Sprite> hpBarSprite;
	std::unique_ptr<Sprite> hpSprite;
	// HPスプライトの大きさ
	XMFLOAT2 startHPSize = {};
	XMFLOAT2 nowHPSize = {};
	// ヒットポイント
	float hitPoint = 1.0f;
	// エネミーとの距離
	float distance = 20.0;
	// 移動速度
	float speed = 0.5f;
	// 弾丸クラス配列
	PlayerBullet* bullets[30];
	// カメラ座標
	XMFLOAT3 cameraEye;
	// ターゲットの座標
	XMFLOAT3 targetPosition = { 0,1,0 };
	// 生存フラグ
	bool isAlive = true;
	// バレッドのディレイ
	USHORT bulletDelay = 60;

};