#pragma once
#include "Object3d.h"

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
	/// �G�l�~�[�ɒ��e���̏���
	/// </summary>
	void LandingPlayer(const CollisionInfo& info);

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
	const USHORT& GetDistance() { return distance; }

	/// <summary>
	/// �����̐ݒ�
	/// </summary>
	/// <param name="isShot">����</param>
	void SetDistance(const USHORT& distance) { this->distance = distance; }

private: // �����o�ϐ�
	// ���˃t���O
	bool isShot = false;
	// ���e�t���O
	bool isLanding = false;
	// ���Ńt���O
	bool isDelete = false;
	// �X�s�[�h
	float speed = 0.2f;
	// ���ł܂ł̋���
	float distance = 0.0f;
	// �G�t�F�N�g�̏I���܂ł̎���
	USHORT effectCount = 0;
};