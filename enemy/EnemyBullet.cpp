#include "EnemyBullet.h"

#include "CollisionManager.h"
#include "SphereCollider.h"
#include "ParticleManager.h"
#include "SafeDelete.h"

using namespace DirectX;

EnemyBullet* EnemyBullet::Create(Model* model)
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	EnemyBullet* bullet = new EnemyBullet();
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

bool EnemyBullet::Initialize()
{
	// ���N���X�̏���������
	Object3d::Initialize();

	// �v���C���[�o���b�h�N���X�Ǝ��̏���������
	
	SetScale({ 0.5f, 0.5f, 0.5f, });


	// �R���C�_�[�̐ݒ�
	SetCollider(new SphereCollider(XMVECTOR({}), 0.4f));

	collider->SetObjectTag("EnemyBullet");

	return true;
}

void EnemyBullet::Move()
{
	distance += speed;

	// ���W�A���ɕϊ�
	float radian = rotation.y * DirectX::XM_PI / 180;

	position.x = sin(radian) * distance;
	position.z = cos(radian) * distance;

	// �G�ɓ�����������Ńt���O�𗧂Ă�
	if (distance > +50) { isDelete = true; }
}

void EnemyBullet::LandingPlayer(const CollisionInfo& info)
{

}


void EnemyBullet::Update()
{
	// �Փˎ����o
	if (isLanding) {
		isDelete = true;
		LandingAfter();
	}

	// ���N���X�̏���������
	if (!isLanding) {
		// �v���C���[�o���b�h�N���X�Ǝ��̍X�V����
		Move();
		Object3d::Update();
	}
}

void EnemyBullet::Draw()
{
	// ���N���X�̏���������
	if (!isLanding) {
		Object3d::Draw();
	}

	// �G�l�~�[�o���b�h�Ǝ��̕`�揈��


}

void EnemyBullet::OnCollision(const CollisionInfo& info)
{
	// �G�l�~�[�Ƃ̏Փˎ�
	if (info.collider->GetObjectTag() == "Player") {
		if (!isLanding) {
			isLanding = true;
			LandingPlayer(info);
		}
	}

}

void EnemyBullet::LandingAfter()
{
	// �R���C�_�[���폜
	if (collider) {
		CollisionManager::GetInstance()->RemoveCollider(collider);
		safe_delete(collider);
	}

	// �G�t�F�N�g�I���܂ł̃J�E���g
	effectCount = 0;

	// ���Ńt���O�Ǘ�
	if (effectCount == 0) {
		isDelete = true;
	}
}
