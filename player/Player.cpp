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
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Player* player = new Player();
	if (player == nullptr) {
		return nullptr;
	}

	// ������
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
	// ���N���X�̏���������
	Object3d::Initialize();

	// �v���C���[�N���X�Ǝ��̏���������

	// �v���C���[���W��������
	float radian = rotation.y * XM_PI / 180;
	position.x = sin(radian) * distance;
	position.z = cos(radian) * distance;

	// �J�������W��������
	cameraEye = position;
	cameraEye.y += 1.5f;
	camera->SetEye(cameraEye);
	camera->SetTarget(targetPosition);

	// �R���C�_�[
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
				bullet->SetParentCollider(collider);
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
		// ���ړ�
		if (input->PushKey(DIK_LEFT)) { rotation.y += speed; }
		if (input->PushKey(DIK_RIGHT)) { rotation.y -= speed; }
		// �c�ړ�
		if (input->PushKey(DIK_UP) && distance > 20) { distance -= 0.1; speed += 0.005f; }
		if (input->PushKey(DIK_DOWN) && distance < 25) { distance += 0.1; speed -= 0.005f; }

		// ���W�A���ɕϊ�
		float radian = rotation.y * XM_PI / 180;

		// ��]���������W��ݒ�
		position.x = sin(radian) * distance;
		position.z = cos(radian) * distance;

		// �J�����̈ړ�����
		UpdateCameraPosition();
	}
}

void Player::UpdateCameraPosition()
{
	// �J�������W���X�V
	cameraEye.x = position.x;
	cameraEye.z = position.z;

	// �J�����Ƀv���C���[�̍��W��ݒ�
	camera->SetEye(cameraEye);
	// �J�����̒����_��ݒ�
	camera->SetTarget(targetPosition);
}

void Player::Update()
{
	// 1�b�ԃf�B���C�̃J�E���g
	if (bulletDelay > 0) { bulletDelay -= 1; }

	// �e�𔭎�
	if (Input::GetInstance()->TriggerKey(DIK_SPACE))
	{
		// �e�̔��ˏ���
		Shot();
	}

	// �v���C���[�N���X�Ǝ��̍X�V����
	Move();

	// �e�̏���
	for (auto& bullet : bullets) {
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

	if (isAlive) {
		// ���N���X�̍X�V����
		Object3d::Update();
	}
}

void Player::Draw()
{
	// �e�̕`�揈��
	for (auto& bullet : bullets) {
		if (bullet) { bullet->Draw(); }
	}

	if (isAlive) {
		// ���N���X�̕`�揈��
		Object3d::Draw();
	}
}

void Player::OnCollision(const CollisionInfo& info)
{
	// �G�l�~�[�̒e�ɓ���������
	if (info.collider->GetObjectTag() == "EnemyBulled") {
		hitPoint -= 1;
	}


}