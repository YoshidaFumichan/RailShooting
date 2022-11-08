#include "Enemy.h"
#include "ParticleManager.h"
#include "CollisionManager.h"
#include "SphereCollider.h"

#include "DebugText.h"
#include "SafeDelete.h"

#include <time.h>
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
	// 乱数の初期化
	srand(time(NULL));

	// 基底クラスの初期化処理
	Object3d::Initialize();

	// エネミークラス独自の初期化処理

	SpriteCommon::GetInstance()->LoadTexture(20, L"Resources/HPBar/parts_Bar.png");
	SpriteCommon::GetInstance()->LoadTexture(21, L"Resources/HPBar/parts_Hp_F.png");
	hpBarSprite.reset(Sprite::Create(20));
	hpSprite.reset(Sprite::Create(21));
	hpSprite->SetPosition({ 145.0f, 55.0f });
	startHPSize = hpSprite->GetSize();
	nowHPSize = startHPSize;

	bulletCount = new Timer;

	// サイズの設定
	float size = 3.0f;
	SetScale({ size, size, size });

	// コライダーの設定
	SetCollider(new SphereCollider(XMLoadFloat3(&position), size));
	collider->SetObjectTag("Enemy");

	return true;
}

void Enemy::Shot()
{
	// 攻撃の種類を乱数で変換
	if (!isShot) {
		attackNum = rand() % AttackType::END;
		isShot = true;
	}
	if (isShot) {

	}


	if (!bullet) {
		if (isShot) {
			bulletCount->CountStart();
			isShot = false;
		}
		else
		{
			if (bulletCount->GetRatio(2.0f) == 1.0f) {
				isShot = true;
				bullet = EnemyBullet::Create(Model::CreateFromOBJ("cube"));
				bullet->SetRotation(target->GetRotation());
				bullet->SetDistance(30.0f);
				bullet->SetIsShot(true);
				isMoveEnd = false;
			}
		}
	}
}

void Enemy::Move()
{
	// 弾が発射されたなく移動フラグと移動終了フラグがFALSEなら
	if (!isShot && !isMove && !isMoveEnd) {
		// 初期角度と終了角度を取得
		startMoveRotation = GetRotation();
		endMoveRotation = target->GetRotation();
		// 移動フラグをTRUEに
		isMove = true;
	}

	// 移動フラグがTRUEで移動終了フラグがFALSEなら
	if (isMove && !isMoveEnd) {
		// 角度を変更
		SetRotation(lerp(startMoveRotation, endMoveRotation, bulletCount->GetRatio(2.0f)));
		// 現在の角度が終了角度に到達しているなら
		if (bulletCount->GetRatio(2.0f) == 1.0f) {
			// 移動フラグをFALSE,移動完了フラグをTRUE
			isMoveEnd = true;
			isMove = false;
		}
	}
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

	// 移動処理
	Move();

	// 基底クラスの更新処理
	if (isAlive) {
		Shot();
		Object3d::Update();
	}

	if (bullet) {
		// 弾の更新処理
		bullet->Update();
		// 消滅フラグが立ってたら
		if (bullet->GetIsDelete()) {
			// デリート
			safe_delete(bullet);
		}
	}
}

void Enemy::Draw()
{
	// エネミークラス独自の描画処理
	if (bullet) {
		bullet->Draw();
	}

	// 生存フラグが経っている場合
	if (isAlive) {
		// 基底クラスの描画処理
		Object3d::Draw();
	}
}

void Enemy::SpriteDraw()
{
	if (isAlive) {
		// HP描画処理
		hpSprite->Draw();
		hpBarSprite->Draw();

		if (bullet) {
			float angle = bullet->GetRotation().y;
			char str[100];
			sprintf_s(str, "Enemy = %f", angle);
			DebugText::GetInstance()->Print(str, { 0,50 });
		}
	}
}

void Enemy::OnCollision(const CollisionInfo& info)
{
	// プレイヤーの通常弾が当たった時
	if (info.collider->GetObjectTag() == "PlayerBullet") {
		hitPoint -= 0.05f;
	}
	nowHPSize.x = startHPSize.x * hitPoint;
	hpSprite->SetSize(nowHPSize);
}
