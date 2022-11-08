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
	// �����̏�����
	srand(time(NULL));

	// ���N���X�̏���������
	Object3d::Initialize();

	// �G�l�~�[�N���X�Ǝ��̏���������

	SpriteCommon::GetInstance()->LoadTexture(20, L"Resources/HPBar/parts_Bar.png");
	SpriteCommon::GetInstance()->LoadTexture(21, L"Resources/HPBar/parts_Hp_F.png");
	hpBarSprite.reset(Sprite::Create(20));
	hpSprite.reset(Sprite::Create(21));
	hpSprite->SetPosition({ 145.0f, 55.0f });
	startHPSize = hpSprite->GetSize();
	nowHPSize = startHPSize;

	bulletCount = new Timer;

	// �T�C�Y�̐ݒ�
	float size = 3.0f;
	SetScale({ size, size, size });

	// �R���C�_�[�̐ݒ�
	SetCollider(new SphereCollider(XMLoadFloat3(&position), size));
	collider->SetObjectTag("Enemy");

	return true;
}

void Enemy::Shot()
{
	// �U���̎�ނ𗐐��ŕϊ�
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
	// �e�����˂��ꂽ�Ȃ��ړ��t���O�ƈړ��I���t���O��FALSE�Ȃ�
	if (!isShot && !isMove && !isMoveEnd) {
		// �����p�x�ƏI���p�x���擾
		startMoveRotation = GetRotation();
		endMoveRotation = target->GetRotation();
		// �ړ��t���O��TRUE��
		isMove = true;
	}

	// �ړ��t���O��TRUE�ňړ��I���t���O��FALSE�Ȃ�
	if (isMove && !isMoveEnd) {
		// �p�x��ύX
		SetRotation(lerp(startMoveRotation, endMoveRotation, bulletCount->GetRatio(2.0f)));
		// ���݂̊p�x���I���p�x�ɓ��B���Ă���Ȃ�
		if (bulletCount->GetRatio(2.0f) == 1.0f) {
			// �ړ��t���O��FALSE,�ړ������t���O��TRUE
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

	// �ړ�����
	Move();

	// ���N���X�̍X�V����
	if (isAlive) {
		Shot();
		Object3d::Update();
	}

	if (bullet) {
		// �e�̍X�V����
		bullet->Update();
		// ���Ńt���O�������Ă���
		if (bullet->GetIsDelete()) {
			// �f���[�g
			safe_delete(bullet);
		}
	}
}

void Enemy::Draw()
{
	// �G�l�~�[�N���X�Ǝ��̕`�揈��
	if (bullet) {
		bullet->Draw();
	}

	// �����t���O���o���Ă���ꍇ
	if (isAlive) {
		// ���N���X�̕`�揈��
		Object3d::Draw();
	}
}

void Enemy::SpriteDraw()
{
	if (isAlive) {
		// HP�`�揈��
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
	// �v���C���[�̒ʏ�e������������
	if (info.collider->GetObjectTag() == "PlayerBullet") {
		hitPoint -= 0.05f;
	}
	nowHPSize.x = startHPSize.x * hitPoint;
	hpSprite->SetSize(nowHPSize);
}
