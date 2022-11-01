#pragma once

#include <Windows.h>

/// <summary>
/// WindoswAPI
/// </summary>
class WinApp
{
public: // �ÓI�����o�ϐ�
	// �E�B���h�E�T�C�Y
	static const int window_width = 1280;	// ����
	static const int window_height = 720;	// �c��
	static const wchar_t windowClassName[];

public: // �ÓI�����o�֐�
	/// <summary>
	/// �E�B���h�E�v���V�[�W��
	/// </summary>
	/// <param name="hwnd">�E�B���h�E�n���h��</param>
	/// <param name="msg">���b�Z�[�W�ԍ�</param>
	/// <param name="wparam">���b�Z�[�W���1</param>
	/// <param name="lparam">���b�Z�[�W���2</param>
	/// <returns>����</returns>
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // �����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	/// <summary>
	/// ���b�Z�[�W�̏���
	/// </summary>
	/// <returns>�I�����ǂ���</returns>
	bool ProcessMessage();

	/// <summary>
	/// �n���h���E�B���h�E�̎擾
	/// </summary>
	/// <returns>�n���h���E�B���h�E</returns>
	HWND GetHwnd() { return hwnd; }

	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	HINSTANCE GetHInstance() { return w.hInstance; }

private: // �����o�֐�
	// �E�B���h�E�Y�N���X
	WNDCLASSEX w{};
	// �n���h���E�B���h�E
	HWND hwnd;
};