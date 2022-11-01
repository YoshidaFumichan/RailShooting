#include "PlayerBullet.h"

#include "CollisionManager.h"
#include "SphereCollider.h"
#include "ParticleManager.h"
#include "SafeDelete.h"

using namespace DirectX;

PlayerBullet* PlayerBullet::Create(Model* model)
{
	// 3Dオブジェクトのインスタンスを生成
	PlayerBullet* bullet = new PlayerBullet();
	if (bullet == nullptr) {
		return nullptr;
	}

	// 初期化処理
	if (!bullet->Initialize()) {
		delete bullet;
		assert(0);
	}

	if (model) {
		bullet->SetModel(model);
	}

	return bullet;
}

bool PlayerBullet::Initialize()
{
	// 基底クラスの初期化処理
	Object3d::Initialize();

	// プレイヤーバレッドクラス独自の初期化処理

	// コライダーの設定
	SetCollider(new SphereCollider(XMVECTOR({}), 0.4f));

	collider->SetObjectTag("PlayerBullet");

	return true;
}

void PlayerBullet::Move()
{
	distance -= speed;

	// ラジアンに変換
	float radian = rotation.y * DirectX::XM_PI / 180;

	position.x = sin(radian) * distance;
	position.z = cos(radian) * distance;

	// 敵に当たったら消滅フラグを立てる
	if (distance < -50) { isDelete = true; }
}


void PlayerBullet::Update()
{
	// 衝突時演出
	if (isLanding) {
		LandingAfter();
	}

	// 基底クラスの初期化処理
	if (!isLanding) {
		// プレイヤーバレッドクラス独自の更新処理
		Move();
		Object3d::Update();
	}
}

void PlayerBullet::Draw()
{
	// 基底クラスの初期化処理
	if (!isLanding) {
		Object3d::Draw();
	}

	// エネミークラス独自の描画処理


}

void PlayerBullet::OnCollision(const CollisionInfo& info)
{
	// エネミーとの衝突時
	if (info.collider->GetObjectTag() == "Enemy") {
		if (!isLanding) {
			isLanding = true;
			LandingEnemy(info);
		}
	}

}

void PlayerBullet::LandingEnemy(const CollisionInfo& info)
{
	effectCount = 60;
	// 着弾時のエフェクト処理
	for (int i = 0; i < 30; ++i) {
		XMFLOAT3 pos{};
		pos.x = info.inter.m128_f32[0];
		pos.y = info.inter.m128_f32[1];
		pos.z = info.inter.m128_f32[2];

		const float rnd_vel = 0.05f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.x = -(float)rand() / RAND_MAX * rnd_acc;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;
		acc.z = -(float)rand() / RAND_MAX * rnd_acc;

		ParticleManager::GetInstance()->Add(effectCount, position, vel, acc, { 1,1,1 }, { 1,0,0 }, 1, 0);
	}

}

void PlayerBullet::LandingAfter()
{
	// コライダーを削除
	if (collider) {
		CollisionManager::GetInstance()->RemoveCollider(collider);
		safe_delete(collider);
	}

	// エフェクト終了までのカウント
	effectCount--;

	// 消滅フラグ管理
	if (effectCount == 0) {
		isDelete = true;
	}
}
