#include "PlayerBullet.h"

#include "CollisionManager.h"
#include "SphereCollider.h"
#include "ParticleManager.h"
#include "SafeDelete.h"

using namespace DirectX;

PlayerBullet* PlayerBullet::Create(Model* model)
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	PlayerBullet* bullet = new PlayerBullet();
	if (bullet == nullptr) {
		return nullptr;
	}

	// ����������
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
	// ���N���X�̏���������
	Object3d::Initialize();

	// �v���C���[�o���b�h�N���X�Ǝ��̏���������

	// �R���C�_�[�̐ݒ�
	SetCollider(new SphereCollider(XMVECTOR({}), 0.4f));

	collider->SetObjectTag("PlayerBullet");

	return true;
}

void PlayerBullet::Move()
{
	distance -= speed;

	// ���W�A���ɕϊ�
	float radian = rotation.y * DirectX::XM_PI / 180;

	position.x = sin(radian) * distance;
	position.z = cos(radian) * distance;

	// �G�ɓ�����������Ńt���O�𗧂Ă�
	if (distance < -50) { isDelete = true; }
}


void PlayerBullet::Update()
{
	// �Փˎ����o
	if (isLanding) {
		LandingAfter();
	}

	// ���N���X�̏���������
	if (!isLanding) {
		// �v���C���[�o���b�h�N���X�Ǝ��̍X�V����
		Move();
		Object3d::Update();
	}
}

void PlayerBullet::Draw()
{
	// ���N���X�̏���������
	if (!isLanding) {
		Object3d::Draw();
	}

	// �G�l�~�[�N���X�Ǝ��̕`�揈��


}

void PlayerBullet::OnCollision(const CollisionInfo& info)
{
	// �G�l�~�[�Ƃ̏Փˎ�
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
	// ���e���̃G�t�F�N�g����
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
	// �R���C�_�[���폜
	if (collider) {
		CollisionManager::GetInstance()->RemoveCollider(collider);
		safe_delete(collider);
	}

	// �G�t�F�N�g�I���܂ł̃J�E���g
	effectCount--;

	// ���Ńt���O�Ǘ�
	if (effectCount == 0) {
		isDelete = true;
	}
}
