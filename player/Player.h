#pragma once
#include "Object3d.h"
#include "Sprite.h"
#include "PlayerBullet.h"
#include "Vector3.h"

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player : public Object3d
{
public: // �ÓI�����o�֐�
	/// <summary>
	/// �v���C���[����
	/// </summary>
	/// <returns>3D�I�u�W�F�N�g</returns>
	static Player* Create(Model* model = nullptr);

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
	/// �J�������W���X�V
	/// </summary>
	void UpdateCameraPosition();

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

private: // �����o�ϐ�
	// HP�o�[�p�X�v���C�g
	std::unique_ptr<Sprite> hpBarSprite;
	std::unique_ptr<Sprite> hpSprite;
	// HP�X�v���C�g�̑傫��
	XMFLOAT2 startHPSize = {};
	XMFLOAT2 nowHPSize = {};
	// �q�b�g�|�C���g
	float hitPoint = 1.0f;
	// �G�l�~�[�Ƃ̋���
	float distance = 20.0;
	// �ړ����x
	float speed = 0.5f;
	// �e�ۃN���X�z��
	PlayerBullet* bullets[30];
	// �J�������W
	XMFLOAT3 cameraEye;
	// �^�[�Q�b�g�̍��W
	XMFLOAT3 targetPosition = { 0,1,0 };
	// �����t���O
	bool isAlive = true;
	// �o���b�h�̃f�B���C
	USHORT bulletDelay = 60;

};