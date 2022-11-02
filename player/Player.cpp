#include "Player.h"
#include "WinApp.h"
#include "Input.h"
#include "Vector3.h"

#include "SphereCollider.h"
#include "SafeDelete.h"

#include <Math.h>

using namespace DirectX;

Player* Player::Create(Model* model)
{
	// 3Dオブジェクトのインスタンスを生成
	Player* player = new Player();
	if (player == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!player->Initialize()) {
		delete player;
		assert(0);
	}

	if (model) {
		player->SetModel(model);
	}

	return player;
}

bool Player::Initialize()
{
	// 基底クラスの初期化処理
	Object3d::Initialize();

	// プレイヤークラス独自の初期化処理

	// HPスプライトの設定
	SpriteCommon::GetInstance()->LoadTexture(10, L"Resources/HPBar/EnemyHPBar.png");
	SpriteCommon::GetInstance()->LoadTexture(11, L"Resources/HPBar/EnemyHP.png");
	hpBarSprite.reset(Sprite::Create(10));
	hpSprite.reset(Sprite::Create(11));
	startHPSize = hpSprite->GetSize();
	startHPSize.x *= 2.5f;
	startHPSize.y *= 2.5f;
	nowHPSize = startHPSize;
	hpSprite->SetSize(startHPSize);
	hpBarSprite->SetSize(startHPSize);


	// プレイヤー座標を初期化
	float radian = rotation.y * XM_PI / 180;
	position.x = sin(radian) * distance;
	position.z = cos(radian) * distance;

	// カメラ座標を初期化
	cameraEye = position;
	cameraEye.y += 1.5f;
	camera->SetEye(cameraEye);
	camera->SetTarget(targetPosition);

	// コライダー
	SetCollider(new SphereCollider);
	collider->SetObjectTag("Player");

	return true;
}

void Player::Shot()
{
	if (bulletDelay <= 0)
	{
		for (auto& bullet : bullets) {
			if (!bullet) {
				bullet = PlayerBullet::Create(Model::CreateFromOBJ("sphere"));
				bullet->SetScale({ 0.5f,0.5f, 0.5f });
				bullet->SetPosition(position);
				bullet->SetRotation(rotation);
				bullet->SetDistance(distance);
				bulletDelay = 30;
				break;
			}
		}
	}
}

void Player::Move()
{
	Input* input = Input::GetInstance();

	if (input->PushKey(DIK_LEFT) || input->PushKey(DIK_RIGHT) ||
		input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN))
	{
		// 横移動
		if (input->PushKey(DIK_LEFT)) { rotation.y += speed; }
		if (input->PushKey(DIK_RIGHT)) { rotation.y -= speed; }
		// 縦移動
		if (input->PushKey(DIK_UP) && distance > 20) { distance -= 0.2; speed += 0.01f; }
		if (input->PushKey(DIK_DOWN) && distance < 25) { distance += 0.2; speed -= 0.01f; }

		// ラジアンに変換
		float radian = rotation.y * XM_PI / 180;

		// 回転座せた座標を設定
		position.x = sin(radian) * distance;
		position.z = cos(radian) * distance;

		// カメラの移動処理
		UpdateCameraPosition();
	}
}

void Player::UpdateCameraPosition()
{
	// カメラ座標を更新
	cameraEye.x = position.x;
	cameraEye.z = position.z;

	// カメラにプレイヤーの座標を設定
	camera->SetEye(cameraEye);
	// カメラの注視点を設定
	camera->SetTarget(targetPosition);
}

void Player::Update()
{
	// 1秒間ディレイのカウント
	if (bulletDelay > 0) { bulletDelay -= 1; }

	// 弾を発射
	if (Input::GetInstance()->TriggerKey(DIK_SPACE))
	{
		// 弾の発射処理
		Shot();
	}

	// プレイヤークラス独自の更新処理
	Move();

	// 弾の処理
	for (auto& bullet : bullets) {
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

	hpSprite->Update();
	hpBarSprite->Update();

	if (isAlive) {
		// 基底クラスの更新処理
		Object3d::Update();
	}
}

void Player::Draw()
{
	// 弾の描画処理
	for (auto& bullet : bullets) {
		if (bullet) { bullet->Draw(); }
	}


	if (isAlive) {
		// 基底クラスの描画処理
		Object3d::Draw();
	}
}

void Player::SpriteDraw()
{
	// HP描画処理
	hpBarSprite->Draw();
	hpSprite->Draw();
}

void Player::OnCollision(const CollisionInfo& info)
{
	// エネミーの弾に当たった時
	if (info.collider->GetObjectTag() == "EnemyBulled") {
		
		hitPoint -= 0.1f;
	}
}