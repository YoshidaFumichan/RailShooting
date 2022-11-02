#pragma once
#include "Object3d.h"
#include "Sprite.h"

#include "EnemyBullet.h"

/// <summary>
/// エネミークラス
/// </summary>
class Enemy : public Object3d
{
public: // 静的メンバ関数
	/// <summary>
	/// プレイヤー生成
	/// </summary>
	/// <returns>3Dオブジェクト</returns>
	static Enemy* Create(Model* model = nullptr);

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
	/// 撃破時の演出
	/// </summary>
	void Defeat();

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

	/// <summary>
	/// ヒットポイントを取得
	/// </summary>
	/// <returns>ヒットポイント</returns>
	const USHORT& GetHitPoint() { return hitPoint; }

	/// <summary>
	/// 生存フラグを取得
	/// </summary>
	/// <returns>生存フラグ</returns>
	const bool& GetIsAlive() { return isAlive; }

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
	/// ヒットポイントを設定
	/// </summary>
	/// <returns>ヒットポイント</returns>
	void SetHitPoint(const float& hitPoint) { this->hitPoint = hitPoint; }

	/// <summary>
	/// 生存フラグを設定
	/// </summary>
	/// <returns>生存フラグ</returns>
	void SetIsAlive(const bool& isAlive) { this->isAlive = isAlive; }

	/// <summary>
	/// ターゲット
	/// </summary>
	/// <param name="targetPosition">ターゲット</param>
	void SetTarget(const XMFLOAT3* targetRot) { this->targetRot = targetRot; }

private: // メンバ変数
	// ターゲット
	const XMFLOAT3* targetRot;
	// バレッドクラス
	EnemyBullet* bullet = nullptr;
	// HPバー用スプライト
	std::unique_ptr<Sprite> hpBarSprite;
	std::unique_ptr<Sprite> hpSprite;
	// HPスプライトの大きさ
	XMFLOAT2 startHPSize;
	XMFLOAT2 nowHPSize;
	// バレッドのディレイ
	USHORT bulletDelay = 60;
	// ヒットポイント
	float hitPoint = 1.0f;
	// 生存フラグ
	bool isAlive = true;
	// 消滅フラグ
	bool isDelete = false;
	// 撃破演出フラグ
	bool isDefeat = false;
	// 撃破演出時間
	SHORT defeatEffectTime = 180;
};