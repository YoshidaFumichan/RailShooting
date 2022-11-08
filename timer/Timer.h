#pragma once
#include <Windows.h>

/// <summary>
/// カウント用変数
/// </summary>
class Timer
{
public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化処理
	/// </summary>
	static inline void StaticInitialize() { appCount = GetTickCount64(); }

	/// <summary>
	/// アプリ開始から現在までのカウントを取得(ミリ秒)
	/// </summary>
	/// <returns>アプリ開始から現在までのカウント</returns>
	static inline const ULONG64& GetAppCount() { return GetTickCount64() - appCount; }

	/// <summary>
	/// アプリ開始から現在までの秒数を取得
	/// </summary>
	/// <returns>アプリ開始から現在までの秒数</returns>
	static inline const float& GetAppTime() { return (float)GetAppCount() / 1000; }

private: // 静的メンバ変数
	// アプリ開始時のカウント
	static ULONG64 appCount;

public: // メンバ関数
	/// <summary>
	/// カウント開始
	/// </summary>
	inline void CountStart() { count = GetTickCount64(); }

	/// <summary>
	/// カウント開始から現在までのカウントを取得(ミリ秒)
	/// </summary>
	/// <returns>カウント開始から現在までのカウント</returns>
	inline const ULONG64& GetCount() { return GetTickCount64() - count; }

	/// <summary>
	/// カウント開始から現在までの秒数を取得
	/// </summary>
	/// <returns>カウント開始から現在までの秒数</returns>
	inline const float& GetTime() { return (float)GetCount() / 1000; }

	/// <summary>
	/// カウント開始から現在までの秒数と指定した秒数を割った値を取得
	/// </summary>
	/// <returns>カウント開始から現在までの秒数と指定した秒数を割った値</returns>
	inline const float& GetRatio(const float& time) { 
		float result = GetTime() / time;
		if (result >= 1.0f) {
			return 1.0f;
		}
		return  GetTime() / time;
	}

private: // メンバ変数
	// カウント
	ULONG64 count;

};