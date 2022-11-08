#pragma once
#include <DirectXMath.h>
#include <vector>

class Vector3 :public DirectX::XMFLOAT3
{
public:
	/*
	float x;	// x����
	float y;	// y����
	float z;	// z����
	 */
public:
	// �R���X�g���N�^
	Vector3();								// ��x�N�g���Ƃ���
	Vector3(DirectX::XMFLOAT3 xm);			// XMFLOAT3����擾����
	Vector3(float x, float y, float z);		// x����, y����, z���� ���w�肵�Ă̐���

	// �����o�֐�
	float length() const;					// �m���}��(����)�����߂�
	Vector3& normalize();					// ���K������
	float dot(const Vector3& v) const;		// ���ς����߂�
	Vector3 cross(const Vector3& v) const;	// �O�ς����߂�

	// �P�����Z�q�I�[�o�[���[�h
	Vector3 operator+() const;
	Vector3 operator-() const;

	// ������Z�q�I�[�o�[���[�h
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
	Vector3& operator=(const DirectX::XMFLOAT3& xm);
	Vector3& operator+=(const DirectX::XMFLOAT3& xm);
	Vector3& operator-=(const DirectX::XMFLOAT3& xm);
};

// 2�����Z�q�I�[�o�[���[�h
// �������Ȉ���(�����̌^�Ə���)�̃p�^�[���ɑΉ����邽�߁A�ȉ��̂悤�ɏ������Ă���
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator+(const DirectX::XMFLOAT3& xm, const Vector3& v1);
const Vector3 operator-(const DirectX::XMFLOAT3& xm, const Vector3& v1);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);

// �⊮�֐�
// ���`�⊮(1���֐��⊮)
const Vector3& lerp(const Vector3& start, const Vector3& end, const float& t);
// �C�[�Y�C��(2���֐��⊮)
const Vector3& easeIn(const Vector3& start, const Vector3& end, const float& t);
// �C�[�Y�A�E�g(2���֐��⊮)
const Vector3& easeOut(const Vector3& start, const Vector3& end, const float& t);
// �C�[�Y�C���A�E�g(2���֐��⊮)
const Vector3& easeInOut(const Vector3& start, const Vector3& end, const float& t);
// �X�v���C�g���(3���֐����)
// n + 2���̓_���g���āAP1�`Pn�̊Ԃ��A�X�v���C����Ԃ���
// (P0) - P1 - P2 - �c Pn - (Pn+1)
Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t);