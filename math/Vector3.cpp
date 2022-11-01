#include "Vector3.h"

// �R���X�g���N�^
Vector3::Vector3() : DirectX::XMFLOAT3{ 0,0,0 }
{

}

Vector3::Vector3(DirectX::XMFLOAT3 xm) : DirectX::XMFLOAT3{ xm.x,xm.y,xm.z }
{

}

Vector3::Vector3(float x, float y, float z) : DirectX::XMFLOAT3{ x,y,z }
{

}

// �����o�֐�
float Vector3::length() const
{
	return (float)sqrt(
		this->x * this->x +
		this->y * this->y +
		this->z * this->z);
}

Vector3& Vector3::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= length();
	}
	return *this;
}

float Vector3::dot(const Vector3& v) const
{
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector3 Vector3::cross(const Vector3& v) const
{
	return Vector3(
		this->y * v.z - this->z * v.y,
		this->z * v.x - this->x * v.z,
		this->x * v.y - this->y * v.x);
}

// �P�����Z�q
Vector3 Vector3::operator+() const
{
	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

// ������Z�q
Vector3& Vector3::operator+=(const Vector3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

Vector3& Vector3::operator*=(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	return *this;
}

Vector3& Vector3::operator/=(float s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
	return *this;
}

Vector3& Vector3::operator=(const DirectX::XMFLOAT3& xm)
{
	this->x = xm.x;
	this->y = xm.y;
	this->z = xm.z;
	return *this;
}

Vector3& Vector3::operator+=(const DirectX::XMFLOAT3& xm)
{
	this->x += xm.x;
	this->y += xm.y;
	this->z += xm.z;
	return *this;
}

Vector3& Vector3::operator-=(const DirectX::XMFLOAT3& xm)
{
	this->x -= xm.x;
	this->y -= xm.y;
	this->z -= xm.z;
	return *this;
}

Vector3& Vector3::operator=(const DirectX::XMFLOAT2& xm)
{
	this->x = xm.x;
	this->y = xm.y;
	this->z = 0;
	return *this;
}

// Vector3 �N���X�ɑ����Ȃ��֐��Q
// �񍀉��Z�q
const Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp += v2;
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp -= v2;
}

const Vector3 operator+(const DirectX::XMFLOAT3& xm, const Vector3& v1)
{
	Vector3 temp(v1);
	return temp += xm;
}

const Vector3 operator-(const DirectX::XMFLOAT3& xm, const Vector3& v1)
{
	Vector3 temp(v1);
	return temp -= xm;
}

const Vector3 operator*(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp *= s;
}

const Vector3 operator*(float s, const Vector3& v)
{
	return v * s;
}

const Vector3 operator/(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp /= s;
}

// ���`�⊮ (�ꎟ���)
const Vector3 lerp(const Vector3& start, const Vector3& end, const float t)
{
	return start * (1.0f - t) + end * t;
}

// �C�[�Y�C�� (�񎟕��)
const Vector3 easeIn(const Vector3& start, const Vector3& end, const float t)
{
	float y = t * t;
	return start * (1.0f - y) + end * y;
}

// �C�[�Y�A�E�g (�񎟕��)
const Vector3 easeOut(const Vector3& start, const Vector3& end, const float t)
{
	float y = t * (2 - t);
	return start * (1.0f - y) + end * y;
}

// �C�[�Y�C���A�E�g (�񎟕��)
const Vector3 easeInOut(const Vector3& start, const Vector3& end, const float t)
{
	float y = (t * t) * (3.0f - 2.0f * t);
	return start * (1.0f - y) + end * y;
}

// �X�v���C���Ȑ�
Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t)
{
	// ��Ԃ���ׂ��_�̐�
	size_t n = points.size() - 2;

	if (startIndex > n) { return points[n]; }	// Pn�̒l��Ԃ�
	if (startIndex < 1) { return points[1]; }	// P1�̒l��Ԃ�

	// p0�`p3 �̐���_���擾���� �� p1 �` p2��Ԃ�����
	Vector3 p0 = points[startIndex - 1];
	Vector3 p1 = points[startIndex];
	Vector3 p2 = points[startIndex + 1];
	Vector3 p3 = points[startIndex + 2];


	// Catmull-Rom �̎��ɂ����
	Vector3 position = 0.5f * (2 * p1 + (-p0 + p2) * t +
		(2 * p0 - 5 * p1 + 4 * p2 - p3) * t * t +
		(-p0 + 3 * p1 - 3 * p2 + p3) * t * t * t);

	return position;
}