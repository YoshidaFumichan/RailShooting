#pragma once
#include "Object3d.h"

/// <summary>
/// プレイヤーの弾丸
/// </summary>
class PlayerBullet : public Object3d
{
public: // 静的メンバ変数
	/// <summary>
	/// プレイヤー生成
	/// </summary>
	/// <returns>3Dオブジェクト</returns>
	static PlayerBullet* Create(Model* model = nullptr);

private: // メンバ変数
	/// <summary>
	/// 初期化処理
	/// </summary>
	bool Initialize()override;

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// エネミーに着弾時の処理
	/// </summary>
	void LandingEnemy(const CollisionInfo& info);

	/// <summary>
	/// 着弾後の処理
	/// </summary>
	void LandingAfter();

public: // メンバ変数
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw()override;

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	void OnCollision(const CollisionInfo& info)override;

	/// <summary>
	/// 射撃フラグの取得
	/// </summary>
	/// <returns>射撃フラグ</returns>
	const bool& GetIsShot() { return isShot; }

	/// <summary>
	/// 射撃フラグの設定
	/// </summary>
	/// <param name="isShot">射撃フラグ</param>
	void SetIsShot(const bool& isShot) { this->isShot = isShot; }

	/// <summary>
	/// 着弾フラグの取得
	/// </summary>
	/// <returns>着弾フラグ</returns>
	const bool& GetIsLanding() { return isLanding; }

	/// <summary>
	/// 着弾フラグの設定
	/// </summary>
	/// <param name="isShot">着弾フラグ</param>
	void SetIsLanding(const bool& isLanding) { this->isLanding = isLanding; }

	/// <summary>
	/// 消滅フラグの取得
	/// </summary>
	/// <returns>消滅フラグ</returns>
	const bool& GetIsDelete() { return isDelete; }

	/// <summary>
	/// 消滅フラグの設定
	/// </summary>
	/// <param name="isShot">消滅フラグ</param>
	void SetIsDelete(const bool& isDelete) { this->isDelete = isDelete; }

	/// <summary>
	/// 距離の取得
	/// </summary>
	/// <returns>距離</returns>
	const USHORT& GetDistance() { return distance; }

	/// <summary>
	/// 距離の設定
	/// </summary>
	/// <param name="isShot">距離</param>
	void SetDistance(const USHORT& distance) { this->distance = distance; }

	/// <summary>
	/// 発射元のコライダーを設定
	/// </summary>
	/// <param name="collider">コライダー</param>
	void SetParentCollider(BaseCollider* collider) { this->parentCollider = collider; }

private: // メンバ変数
	// 発射フラグ
	bool isShot = false;
	// 着弾フラグ
	bool isLanding = false;
	// 消滅フラグ
	bool isDelete = false;
	// スピード
	float speed = 0.1f;
	// 消滅までの距離
	float distance;
	// 発射元のコライダー
	BaseCollider* parentCollider = nullptr;
	// エフェクトの終了までの時間
	USHORT effectCount = 0;

};

