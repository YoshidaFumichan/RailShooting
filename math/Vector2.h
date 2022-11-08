#pragma once
#include <DirectXMath.h>
#include <vector>

class Vector2 :public DirectX::XMFLOAT2
{
public:
	/*
	float x;	// x����
	float y;	// y����
	 */
public:
	// �R���X�g���N�^
	Vector2();								// ��x�N�g���Ƃ���
	Vector2(DirectX::XMFLOAT2 xm);			// XMFLOAT3����擾����
	Vector2(float x, float y);		// x����, y����, z���� ���w�肵�Ă̐���

	// �����o�֐�
	float length() const;					// �m���}��(����)�����߂�
	Vector2& normalize();					// ���K������
	float dot(const Vector2& v) const;		// ���ς����߂�
	float cross(const Vector2& v) const;	// �O�ς����߂�

	// �P�����Z�q�I�[�o�[���[�h
	Vector2 operator+() const;
	Vector2 operator-() const;

	// ������Z�q�I�[�o�[���[�h
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
	Vector2& operator=(const DirectX::XMFLOAT3& xm);
	Vector2& operator+=(const DirectX::XMFLOAT3& xm);
	Vector2& operator-=(const DirectX::XMFLOAT3& xm);
	Vector2& operator=(const DirectX::XMFLOAT2& xm);
};

// 2�����Z�q�I�[�o�[���[�h
// �������Ȉ���(�����̌^�Ə���)�̃p�^�[���ɑΉ����邽�߁A�ȉ��̂悤�ɏ������Ă���
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator+(const DirectX::XMFLOAT2& xm, const Vector2& v1);
const Vector2 operator-(const DirectX::XMFLOAT2& xm, const Vector2& v1);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);

// �⊮�֐�
// ���`�⊮(1���֐��⊮)
const Vector2& lerp(const Vector2& start, const Vector2& end, const float& t);
// �C�[�Y�C��(2���֐��⊮)
const Vector2& easeIn(const Vector2& start, const Vector2& end, const float& t);
// �C�[�Y�A�E�g(2���֐��⊮)
const Vector2& easeOut(const Vector2& start, const Vector2& end, const float& t);
// �C�[�Y�C���A�E�g(2���֐��⊮)
const Vector2& easeInOut(const Vector2& start, const Vector2& end, const float& t);