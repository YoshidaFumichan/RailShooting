#pragma once
#include <DirectXMath.h>
#include <vector>

class Vector3 :public DirectX::XMFLOAT3
{
public:
	/*
	float x;	// x成分
	float y;	// y成分
	float z;	// z成分
	 */
public:
	// コンストラクタ
	Vector3();								// 零ベクトルとする
	Vector3(DirectX::XMFLOAT3 xm);			// XMFLOAT3から取得する
	Vector3(float x, float y, float z);		// x成分, y成分, z成分 を指定しての成分

	// メンバ関数
	float length() const;					// ノルマの(長さ)を求める
	Vector3& normalize();					// 正規化する
	float dot(const Vector3& v) const;		// 内積を求める
	Vector3 cross(const Vector3& v) const;	// 外積を求める

	// 単頂演算子オーバーロード
	Vector3 operator+() const;
	Vector3 operator-() const;

	// 代入演算子オーバーロード
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
	Vector3& operator=(const DirectX::XMFLOAT3& xm);
	Vector3& operator+=(const DirectX::XMFLOAT3& xm);
	Vector3& operator-=(const DirectX::XMFLOAT3& xm);
};

// 2項演算子オーバーロード
// ※いろんな引数(引数の型と順序)のパターンに対応するため、以下のように準備している
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator+(const DirectX::XMFLOAT3& xm, const Vector3& v1);
const Vector3 operator-(const DirectX::XMFLOAT3& xm, const Vector3& v1);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);

// 補完関数
// 線形補完(1次関数補完)
const Vector3& lerp(const Vector3& start, const Vector3& end, const float& t);
// イーズイン(2次関数補完)
const Vector3& easeIn(const Vector3& start, const Vector3& end, const float& t);
// イーズアウト(2次関数補完)
const Vector3& easeOut(const Vector3& start, const Vector3& end, const float& t);
// イーズインアウト(2次関数補完)
const Vector3& easeInOut(const Vector3& start, const Vector3& end, const float& t);
// スプライト補間(3次関数補間)
// n + 2個分の点を使って、P1～Pnの間を、スプライン補間する
// (P0) - P1 - P2 - … Pn - (Pn+1)
Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t);