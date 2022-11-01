#include "Enemy.h"
#include "ParticleManager.h"
#include "CollisionManager.h"
#include "SphereCollider.h"

#include "DebugText.h"
#include "SafeDelete.h"

using namespace DirectX;

Enemy* Enemy::Create(Model* model)
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Enemy* enemy = new Enemy();
	if (enemy == nullptr) {
		return nullptr;
	}

	// ����������
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
	// ���N���X�̏���������
	Object3d::Initialize();

	// �G�l�~�[�N���X�Ǝ��̏���������

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




	// �T�C�Y�̐ݒ�
	float size = 2.0f;
	SetScale({ size, size, size });

	// �R���C�_�[�̐ݒ�
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
	// �G�l�~�[�N���X�Ǝ��̍X�V����
	if (hitPoint <= 0) {
		if (!isDefeat) {
			Defeat();
		}
		defeatEffectTime--;
		if (defeatEffectTime <= 0) {
			isDelete = true;
		}
	}

	// ���N���X�̍X�V����
	if (isAlive) {
		Object3d::Update();
	}
}

void Enemy::Draw()
{
	// �G�l�~�[�N���X�Ǝ��̕`�揈��


	// �����t���O���o���Ă���ꍇ
	if (isAlive) {
		// ���N���X�̕`�揈��
		Object3d::Draw();
	}
}

void Enemy::SpriteDraw()
{
	// HP�`�揈��
	hpBarSprite->Draw();
	hpSprite->Draw();
}

void Enemy::OnCollision(const CollisionInfo& info)
{
	// �v���C���[�̒ʏ�e������������
	if (info.collider->GetObjectTag() == "PlayerBullet") {
		hitPoint -= 0.1f;
	}


	nowHPSize.x = startHPSize.x * hitPoint;
	hpSprite->SetSize(nowHPSize);
}
