#pragma once
#include "Object3d.h"
#include "Timer.h"

/// <summary>
/// �G�l�~�[�o���b�h�N���X
/// </summary>
class EnemyBullet : public Object3d
{
public: // �ÓI�����o�ϐ�
	/// <summary>
	/// �v���C���[����
	/// </summary>
	/// <returns>3D�I�u�W�F�N�g</returns>
	static EnemyBullet* Create(Model* model = nullptr);

private: // �����o�ϐ�
	/// <summary>
	/// ����������
	/// </summary>
	bool Initialize()override;

	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// ���e��̏���
	/// </summary>
	void LandingAfter();

public: // �����o�ϐ�
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update()override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw()override;

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	/// <param name="info">�Փˏ��</param>
	void OnCollision(const CollisionInfo& info)override;

	/// <summary>
	/// �ˌ��t���O�̎擾
	/// </summary>
	/// <returns>�ˌ��t���O</returns>
	const bool& GetIsShot() { return isShot; }

	/// <summary>
	/// �ˌ��t���O�̐ݒ�
	/// </summary>
	/// <param name="isShot">�ˌ��t���O</param>
	void SetIsShot(const bool& isShot) { this->isShot = isShot; }

	/// <summary>
	/// ���e�t���O�̎擾
	/// </summary>
	/// <returns>���e�t���O</returns>
	const bool& GetIsLanding() { return isLanding; }

	/// <summary>
	/// ���e�t���O�̐ݒ�
	/// </summary>
	/// <param name="isShot">���e�t���O</param>
	void SetIsLanding(const bool& isLanding) { this->isLanding = isLanding; }

	/// <summary>
	/// ���Ńt���O�̎擾
	/// </summary>
	/// <returns>���Ńt���O</returns>
	const bool& GetIsDelete() { return isDelete; }

	/// <summary>
	/// ���Ńt���O�̐ݒ�
	/// </summary>
	/// <param name="isShot">���Ńt���O</param>
	void SetIsDelete(const bool& isDelete) { this->isDelete = isDelete; }

	/// <summary>
	/// �����̎擾
	/// </summary>
	/// <returns>����</returns>
	const float& GetDistance() { return distance; }

	/// <summary>
	/// �����̐ݒ�
	/// </summary>
	/// <param name="isShot">����</param>
	void SetDistance(const float& distance) { this->distance = distance; }

private: // �����o�ϐ�
	// �X�s�[�h
	float count = 0.0f;
	// �ŏI���W
	XMFLOAT3 endPosition;
	// ���˃t���O
	bool isShot = false;
	// ���e�t���O
	bool isLanding = false;
	// ���Ńt���O
	bool isDelete = false;
	// ���ł܂ł̋���
	float distance = 0.0f;
	// �^�C�}�[
	std::unique_ptr<Timer> timer;
};