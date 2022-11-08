#include "EnemyBullet.h"
#include "Vector3.h"
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
		model->SetAmbient({ 1,0,0 });
	}

	return bullet;
}

bool EnemyBullet::Initialize()
{
	// 基底クラスの初期化処理
	Object3d::Initialize();

	// タイマー
	timer.reset(new Timer);
	timer->CountStart();

	// プレイヤーバレッドクラス独自の初期化処理
	SetScale({ 0.5f, 0.5f, 0.5f, });


	// コライダーの設定
	SetCollider(new SphereCollider(XMVECTOR({}), 0.4f));
	collider->SetObjectTag("EnemyBullet");

	return true;
}

void EnemyBullet::Move()
{
	count += 0.005f;

	// 移動処理
	position = easeOut({ 0,0,0 }, endPosition, timer->GetRatio(1.5f));

	// 敵に当たったら消滅フラグを立てる
	if (1.0f <= timer->GetRatio(1.5f)) { isDelete = true; }
}

void EnemyBullet::Update()
{
	if (isShot) {
		// ラジアンを取得
		float radian = rotation.y * DirectX::XM_PI / 180;
		endPosition.x = sin(radian) * (distance + 5);
		endPosition.z = cos(radian) * (distance + 5);
		isShot = false;
	}

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
}

void EnemyBullet::OnCollision(const CollisionInfo& info)
{
	// エネミーとの衝突時
	if (info.collider->GetObjectTag() == "Player") {
		if (!isLanding) {
			isLanding = true;
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

	isDelete = true;
}