#include "EnemyBullet.h"

#include "CollisionManager.h"
#include "SphereCollider.h"
#include "ParticleManager.h"
#include "SafeDelete.h"

using namespace DirectX;

EnemyBullet* EnemyBullet::Create(Model* model)
{
	// 3Dオブジェクトのインスタンスを生成
	EnemyBullet* bullet = new EnemyBullet();
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

bool EnemyBullet::Initialize()
{
	// 基底クラスの初期化処理
	Object3d::Initialize();

	// プレイヤーバレッドクラス独自の初期化処理
	
	SetScale({ 0.5f, 0.5f, 0.5f, });


	// コライダーの設定
	SetCollider(new SphereCollider(XMVECTOR({}), 0.4f));

	collider->SetObjectTag("EnemyBullet");

	return true;
}

void EnemyBullet::Move()
{
	distance += speed;

	// ラジアンに変換
	float radian = rotation.y * DirectX::XM_PI / 180;

	position.x = sin(radian) * distance;
	position.z = cos(radian) * distance;

	// 敵に当たったら消滅フラグを立てる
	if (distance > +50) { isDelete = true; }
}

void EnemyBullet::LandingPlayer(const CollisionInfo& info)
{

}


void EnemyBullet::Update()
{
	// 衝突時演出
	if (isLanding) {
		isDelete = true;
		LandingAfter();
	}

	// 基底クラスの初期化処理
	if (!isLanding) {
		// プレイヤーバレッドクラス独自の更新処理
		Move();
		Object3d::Update();
	}
}

void EnemyBullet::Draw()
{
	// 基底クラスの初期化処理
	if (!isLanding) {
		Object3d::Draw();
	}

	// エネミーバレッド独自の描画処理


}

void EnemyBullet::OnCollision(const CollisionInfo& info)
{
	// エネミーとの衝突時
	if (info.collider->GetObjectTag() == "Player") {
		if (!isLanding) {
			isLanding = true;
			LandingPlayer(info);
		}
	}

}

void EnemyBullet::LandingAfter()
{
	// コライダーを削除
	if (collider) {
		CollisionManager::GetInstance()->RemoveCollider(collider);
		safe_delete(collider);
	}

	// エフェクト終了までのカウント
	effectCount = 0;

	// 消滅フラグ管理
	if (effectCount == 0) {
		isDelete = true;
	}
}
