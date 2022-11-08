#pragma once
#include <Windows.h>

/// <summary>
/// �J�E���g�p�ϐ�
/// </summary>
class Timer
{
public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI����������
	/// </summary>
	static inline void StaticInitialize() { appCount = GetTickCount64(); }

	/// <summary>
	/// �A�v���J�n���猻�݂܂ł̃J�E���g���擾(�~���b)
	/// </summary>
	/// <returns>�A�v���J�n���猻�݂܂ł̃J�E���g</returns>
	static inline const ULONG64& GetAppCount() { return GetTickCount64() - appCount; }

	/// <summary>
	/// �A�v���J�n���猻�݂܂ł̕b�����擾
	/// </summary>
	/// <returns>�A�v���J�n���猻�݂܂ł̕b��</returns>
	static inline const float& GetAppTime() { return (float)GetAppCount() / 1000; }

private: // �ÓI�����o�ϐ�
	// �A�v���J�n���̃J�E���g
	static ULONG64 appCount;

public: // �����o�֐�
	/// <summary>
	/// �J�E���g�J�n
	/// </summary>
	inline void CountStart() { count = GetTickCount64(); }

	/// <summary>
	/// �J�E���g�J�n���猻�݂܂ł̃J�E���g���擾(�~���b)
	/// </summary>
	/// <returns>�J�E���g�J�n���猻�݂܂ł̃J�E���g</returns>
	inline const ULONG64& GetCount() { return GetTickCount64() - count; }

	/// <summary>
	/// �J�E���g�J�n���猻�݂܂ł̕b�����擾
	/// </summary>
	/// <returns>�J�E���g�J�n���猻�݂܂ł̕b��</returns>
	inline const float& GetTime() { return (float)GetCount() / 1000; }

	/// <summary>
	/// �J�E���g�J�n���猻�݂܂ł̕b���Ǝw�肵���b�����������l���擾
	/// </summary>
	/// <returns>�J�E���g�J�n���猻�݂܂ł̕b���Ǝw�肵���b�����������l</returns>
	inline const float& GetRatio(const float& time) { 
		float result = GetTime() / time;
		if (result >= 1.0f) {
			return 1.0f;
		}
		return  GetTime() / time;
	}

private: // �����o�ϐ�
	// �J�E���g
	ULONG64 count;

};