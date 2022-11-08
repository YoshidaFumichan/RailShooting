#include "Vector2.h"

// コンストラクタ
Vector2::Vector2() : DirectX::XMFLOAT2{ 0,0, }
{

}

Vector2::Vector2(DirectX::XMFLOAT2 xm) : DirectX::XMFLOAT2{ xm.x,xm.y }
{

}

Vector2::Vector2(float x, float y) : DirectX::XMFLOAT2{ x,y, }
{

}

// メンバ関数
float Vector2::length() const
{
	return (float)sqrt(
		this->x * this->x +
		this->y * this->y);
}

Vector2& Vector2::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= length();
	}
	return *this;
}

float Vector2::dot(const Vector2& v) const
{
	return this->x * v.x + this->y * v.y;
}

float Vector2::cross(const Vector2& v) const
{
	return this->x * v.y - this->y * v.x;
}

// 単項演算子
Vector2 Vector2::operator+() const
{
	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

// 代入演算子
Vector2& Vector2::operator+=(const Vector2& v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector2& Vector2::operator*=(float s)
{
	this->x *= s;
	this->y *= s;
	return *this;
}

Vector2& Vector2::operator/=(float s)
{
	this->x /= s;
	this->y /= s;
	return *this;
}

Vector2& Vector2::operator=(const DirectX::XMFLOAT3& xm)
{
	this->x = xm.x;
	this->y = xm.y;
	return *this;
}

Vector2& Vector2::operator+=(const DirectX::XMFLOAT3& xm)
{
	this->x += xm.x;
	this->y += xm.y;
	return *this;
}

Vector2& Vector2::operator-=(const DirectX::XMFLOAT3& xm)
{
	this->x -= xm.x;
	this->y -= xm.y;
	return *this;
}

Vector2& Vector2::operator=(const DirectX::XMFLOAT2& xm)
{
	this->x = xm.x;
	this->y = xm.y;
	return *this;
}

// Vector2 クラスに属さない関数群
// 二項演算子
const Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	Vector2 temp(v1);
	return temp += v2;
}

const Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	Vector2 temp(v1);
	return temp -= v2;
}

const Vector2 operator+(const DirectX::XMFLOAT2& xm, const Vector2& v1)
{
	Vector2 temp(v1);
	return temp += xm;
}

const Vector2 operator-(const DirectX::XMFLOAT2& xm, const Vector2& v1)
{
	Vector2 temp(v1);
	return temp -= xm;
}

const Vector2 operator*(const Vector2& v, float s)
{
	Vector2 temp(v);
	return temp *= s;
}

const Vector2 operator*(float s, const Vector2& v)
{
	return v * s;
}

const Vector2 operator/(const Vector2& v, float s)
{
	Vector2 temp(v);
	return temp /= s;
}

const Vector2& lerp(const Vector2& start, const Vector2& end, const float& t)
{
	return start * (1.0f - t) + end * t;
}

// イーズイン (二次補間)
const Vector2& easeIn(const Vector2& start, const Vector2& end, const float& t)
{
	float y = t * t;
	return start * (1.0f - y) + end * y;
}

// イーズアウト (二次補間)
const Vector2& easeOut(const Vector2& start, const Vector2& end, const float& t)
{
	float y = t * (2 - t);
	return start * (1.0f - y) + end * y;
}

// イーズインアウト (二次補間)
const Vector2& easeInOut(const Vector2& start, const Vector2& end, const float& t)
{
	float y = (t * t) * (3.0f - 2.0f * t);
	return start * (1.0f - y) + end * y;
}
