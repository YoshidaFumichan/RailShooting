#pragma once
#include "Object3d.h"
#include "Sprite.h"

#include "EnemyBullet.h"

/// <summary>
/// �G�l�~�[�N���X
/// </summary>
class Enemy : public Object3d
{
public: // �ÓI�����o�֐�
	/// <summary>
	/// �v���C���[����
	/// </summary>
	/// <returns>3D�I�u�W�F�N�g</returns>
	static Enemy* Create(Model* model = nullptr);

private: // �����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	bool Initialize()override;

	/// <summary>
	/// �e�̔��ˏ���
	/// </summary>
	void Shot();

	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// ���j���̉��o
	/// </summary>
	void Defeat();

public: // �����o�֐�
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update()override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw()override;

	/// <summary>
	/// �X�v���C�g�`�揈��
	/// </summary>
	void SpriteDraw();

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	/// <param name="info">�Փˏ��</param>
	void OnCollision(const CollisionInfo& info)override;

	/// <summary>
	/// �q�b�g�|�C���g���擾
	/// </summary>
	/// <returns>�q�b�g�|�C���g</returns>
	const USHORT& GetHitPoint() { return hitPoint; }

	/// <summary>
	/// �����t���O���擾
	/// </summary>
	/// <returns>�����t���O</returns>
	const bool& GetIsAlive() { return isAlive; }

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
	/// �q�b�g�|�C���g��ݒ�
	/// </summary>
	/// <returns>�q�b�g�|�C���g</returns>
	void SetHitPoint(const float& hitPoint) { this->hitPoint = hitPoint; }

	/// <summary>
	/// �����t���O��ݒ�
	/// </summary>
	/// <returns>�����t���O</returns>
	void SetIsAlive(const bool& isAlive) { this->isAlive = isAlive; }

	/// <summary>
	/// �^�[�Q�b�g
	/// </summary>
	/// <param name="targetPosition">�^�[�Q�b�g</param>
	void SetTarget(const XMFLOAT3* targetRot) { this->targetRot = targetRot; }

private: // �����o�ϐ�
	// �^�[�Q�b�g
	const XMFLOAT3* targetRot;
	// �o���b�h�N���X
	EnemyBullet* bullet = nullptr;
	// HP�o�[�p�X�v���C�g
	std::unique_ptr<Sprite> hpBarSprite;
	std::unique_ptr<Sprite> hpSprite;
	// HP�X�v���C�g�̑傫��
	XMFLOAT2 startHPSize;
	XMFLOAT2 nowHPSize;
	// �o���b�h�̃f�B���C
	USHORT bulletDelay = 60;
	// �q�b�g�|�C���g
	float hitPoint = 1.0f;
	// �����t���O
	bool isAlive = true;
	// ���Ńt���O
	bool isDelete = false;
	// ���j���o�t���O
	bool isDefeat = false;
	// ���j���o����
	SHORT defeatEffectTime = 180;
};