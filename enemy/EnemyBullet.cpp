#include "EnemyBullet.h"
#include "Vector3.h"
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
		model->SetAmbient({ 1,0,0 });
	}

	return bullet;
}

bool EnemyBullet::Initialize()
{
	// ���N���X�̏���������
	Object3d::Initialize();

	// �^�C�}�[
	timer.reset(new Timer);
	timer->CountStart();

	// �v���C���[�o���b�h�N���X�Ǝ��̏���������
	SetScale({ 0.5f, 0.5f, 0.5f, });


	// �R���C�_�[�̐ݒ�
	SetCollider(new SphereCollider(XMVECTOR({}), 0.4f));
	collider->SetObjectTag("EnemyBullet");

	return true;
}

void EnemyBullet::Move()
{
	count += 0.005f;

	// �ړ�����
	position = easeOut({ 0,0,0 }, endPosition, timer->GetRatio(1.5f));

	// �G�ɓ�����������Ńt���O�𗧂Ă�
	if (1.0f <= timer->GetRatio(1.5f)) { isDelete = true; }
}

void EnemyBullet::Update()
{
	if (isShot) {
		// ���W�A�����擾
		float radian = rotation.y * DirectX::XM_PI / 180;
		endPosition.x = sin(radian) * (distance + 5);
		endPosition.z = cos(radian) * (distance + 5);
		isShot = false;
	}

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
}

void EnemyBullet::OnCollision(const CollisionInfo& info)
{
	// �G�l�~�[�Ƃ̏Փˎ�
	if (info.collider->GetObjectTag() == "Player") {
		if (!isLanding) {
			isLanding = true;
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

	isDelete = true;
}