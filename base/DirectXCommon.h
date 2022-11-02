#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <chrono>

#include "WinApp.h"

/// <summary>
/// DirectX���
/// </summary>
class DirectXCommon
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// �`��O����
	/// </summary>
	void PreDraw();

	/// <summary>
	/// �`��㏈��
	/// </summary>
	void PostDraw();

	/// <summary>
	/// �f�o�C�X�̎擾
	/// </summary>
	/// <returns>�f�o�C�X</returns>
	ID3D12Device* GetDevice() { return dev.Get(); }

	/// <summary>
	/// �R�}���h���X�g�̎擾
	/// </summary>
	/// <returns>�R�}���h���X�g</returns>
	ID3D12GraphicsCommandList* GetCommandList() { return cmdList.Get(); }

private: // �����o�ϐ�
	// WindowsAPI
	WinApp* winApp = nullptr;
	// �L�^���� (FPS�Œ�p)
	std::chrono::steady_clock::time_point reference;
	// DirectX3D�֘A
	// �f�o�C�X
	ComPtr<ID3D12Device> dev;
	// DXGI�t�@�N�g��
	ComPtr<IDXGIFactory6> dxgiFactory;
	// �R�}���h�A���P�[�^
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	// �R�}���h���X�g
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	// �R�}���h�L���[
	ComPtr<ID3D12CommandQueue> cmdQueue;
	// �X���b�v�`�F�[��
	ComPtr<IDXGISwapChain4> swapchain;
	// �����_�[�^�[�Q�b�g�r���[�q�[�v
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	// 
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	// �o�b�N�o�b�t�@
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	// 
	ComPtr<ID3D12Resource> depthBuffer;
	// �t�F���X
	ComPtr<ID3D12Fence> fence;
	// �t�F���X�̐�
	UINT64 fenceVal = 0;

private: // �����o�֐�
	/// <summary>
	/// FPS�Œ菉����
	/// </summary>
	void InitializeFixFps();

	/// <summary>
	/// �f�o�C�X�̏�����
	/// </summary>
	/// <returns>����</returns>
	bool InitializeDevice();

	/// <summary>
	/// �R�}���h�֘A�̏�����
	/// </summary>
	/// <returns>����</returns>
	bool InitializeCommand();

	/// <summary>
	/// �X���b�v�`�F�[���̏�����
	/// </summary>
	/// <returns>����</returns>
	bool InitializeSwapchain();

	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[�̏�����
	/// </summary>
	/// <returns>����</returns>
	bool InitializeRenderTargetView();

	/// <summary>
	/// �[�x�o�b�t�@�̏�����
	/// </summary>
	/// <returns>����</returns>
	bool InitializeDepthBuffer();

	/// <summary>
	/// �t�F���X�̏�����
	/// </summary>
	/// <returns>����</returns>
	bool InitializeFence();

	/// <summary>
	/// FPS�Œ�X�V
	/// </summary>
	void UpdateFixFPS();
};