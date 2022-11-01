#include "Enemy.h"
#include "ParticleManager.h"
#include "CollisionManager.h"
#include "SphereCollider.h"

#include "DebugText.h"
#include "SafeDelete.h"

using namespace DirectX;

Enemy* Enemy::Create(Model* model)
{
	// 3Dオブジェクトのインスタンスを生成
	Enemy* enemy = new Enemy();
	if (enemy == nullptr) {
		return nullptr;
	}

	// 初期化処理
	if (!enemy->Initialize()) {
		delete enemy;
		assert(0);
	}

	if (model) {
		enemy->SetModel(model);
	}

	return enemy;
}

bool Enemy::Initialize()
{
	// 基底クラスの初期化処理
	Object3d::Initialize();

	// エネミークラス独自の初期化処理

	SpriteCommon::GetInstance()->LoadTexture(20, L"Resources/HPBar/EnemyHPBar.png");
	SpriteCommon::GetInstance()->LoadTexture(21, L"Resources/HPBar/EnemyHP.png");
	hpBarSprite.reset(Sprite::Create(20));
	hpSprite.reset(Sprite::Create(21));
	startHPSize = hpSprite->GetSize();
	startHPSize.x *= 2.5f;
	startHPSize.y *= 2.5f;
	nowHPSize = startHPSize;
	hpSprite->SetSize(startHPSize);
	hpBarSprite->SetSize(startHPSize);




	// サイズの設定
	float size = 2.0f;
	SetScale({ size, size, size });

	// コライダーの設定
	SetCollider(new SphereCollider(XMLoadFloat3(&position), size));
	collider->SetObjectTag("Enemy");

	return true;
}

void Enemy::Shot()
{

}

void Enemy::Move()
{

}

void Enemy::Defeat()
{
	isAlive = false;
	collisionMan->RemoveCollider(collider);
	safe_delete(collider);


	isDefeat = true;
}

void Enemy::Update()
{
	// エネミークラス独自の更新処理
	if (hitPoint <= 0) {
		if (!isDefeat) {
			Defeat();
		}
		defeatEffectTime--;
		if (defeatEffectTime <= 0) {
			isDelete = true;
		}
	}

	// 基底クラスの更新処理
	if (isAlive) {
		Object3d::Update();
	}
}

void Enemy::Draw()
{
	// エネミークラス独自の描画処理


	// 生存フラグが経っている場合
	if (isAlive) {
		// 基底クラスの描画処理
		Object3d::Draw();
	}
}

void Enemy::SpriteDraw()
{
	// HP描画処理
	hpBarSprite->Draw();
	hpSprite->Draw();
}

void Enemy::OnCollision(const CollisionInfo& info)
{
	// プレイヤーの通常弾が当たった時
	if (info.collider->GetObjectTag() == "PlayerBullet") {
		hitPoint -= 0.1f;
	}


	nowHPSize.x = startHPSize.x * hitPoint;
	hpSprite->SetSize(nowHPSize);
}
