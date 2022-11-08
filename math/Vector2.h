#pragma once
#include <DirectXMath.h>
#include <vector>

class Vector2 :public DirectX::XMFLOAT2
{
public:
	/*
	float x;	// x成分
	float y;	// y成分
	 */
public:
	// コンストラクタ
	Vector2();								// 零ベクトルとする
	Vector2(DirectX::XMFLOAT2 xm);			// XMFLOAT3から取得する
	Vector2(float x, float y);		// x成分, y成分, z成分 を指定しての成分

	// メンバ関数
	float length() const;					// ノルマの(長さ)を求める
	Vector2& normalize();					// 正規化する
	float dot(const Vector2& v) const;		// 内積を求める
	float cross(const Vector2& v) const;	// 外積を求める

	// 単頂演算子オーバーロード
	Vector2 operator+() const;
	Vector2 operator-() const;

	// 代入演算子オーバーロード
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
	Vector2& operator=(const DirectX::XMFLOAT3& xm);
	Vector2& operator+=(const DirectX::XMFLOAT3& xm);
	Vector2& operator-=(const DirectX::XMFLOAT3& xm);
	Vector2& operator=(const DirectX::XMFLOAT2& xm);
};

// 2項演算子オーバーロード
// ※いろんな引数(引数の型と順序)のパターンに対応するため、以下のように準備している
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator+(const DirectX::XMFLOAT2& xm, const Vector2& v1);
const Vector2 operator-(const DirectX::XMFLOAT2& xm, const Vector2& v1);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);

// 補完関数
// 線形補完(1次関数補完)
const Vector2& lerp(const Vector2& start, const Vector2& end, const float& t);
// イーズイン(2次関数補完)
const Vector2& easeIn(const Vector2& start, const Vector2& end, const float& t);
// イーズアウト(2次関数補完)
const Vector2& easeOut(const Vector2& start, const Vector2& end, const float& t);
// イーズインアウト(2次関数補完)
const Vector2& easeInOut(const Vector2& start, const Vector2& end, const float& t);