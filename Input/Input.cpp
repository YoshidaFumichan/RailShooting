﻿#include "Input.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")

Input* Input::GetInstance()
{
	static Input instance;

	return &instance;
}

bool Input::Initialize(WinApp* win)
{
	// NULL検出
	assert(win);
	assert(!dinput);

	HRESULT result = S_FALSE;

	// DirectInputのインスタンス生成
	result = DirectInput8Create(win->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// キーボードデバイス生成
	result = dinput->CreateDevice(GUID_SysKeyboard, &devKeyboard, NULL);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// マウスデバイス生成
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// 入力データ形式のセット
	result = devKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// 排他制御レベルのセット
	result = devKeyboard->SetCooperativeLevel(win->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// 入力データ形式のセット
	result = devMouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// 排他制御レベルのセット
	result = devMouse->SetCooperativeLevel(win->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	return true;
}

void Input::Update()
{
	HRESULT result = S_FALSE;

	{	// キーボード
		result = devKeyboard->Acquire();	// キーボード動作開始

		// 前回のキー入力を保存
		memcpy(keyPre, key, sizeof(key));

		// キーの入力
		result = devKeyboard->GetDeviceState(sizeof(key), key);
	}

	{	// マウス
		result = devMouse->Acquire();	// マウス動作開始

		// 前回の入力を保存
		mouseStatePre = mouseState;

		// マウスの入力
		result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);
	}
}

bool Input::PushKey(BYTE keyNumber)
{
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	// 指定キーを押していればtrueを返す
	if (key[keyNumber]) {
		return true;
	}

	// そうでなければfalseを返す
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	// 前回キー情報で指定キーを押していなく今回キー情報で指定キーを押していればtrueを返す
	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}

	// そうでなければfalseを返す
	return false;
}

bool Input::PushMouseLeft()
{
	// 0でなければ押している
	if (mouseState.rgbButtons[0]) {
		return true;
	}

	// 押していない
	return false;
}

bool Input::PushMouseRight()
{
	// 0でなければ押している
	if (mouseState.rgbButtons[2]) {
		return true;
	}

	// 押していない
	return false;
}

bool Input::PushMouseMiddle()
{
	// 0でなければ押している
	if (mouseState.rgbButtons[2]) {
		return true;
	}

	// 押していない
	return false;
}

bool Input::TriggerMouseLeft()
{
	// 前回が0で、今回が0でなければトリガー
	if (!mouseStatePre.rgbButtons[0] && mouseState.rgbButtons[0]) {
		return true;
	}

	// トリガーでない
	return false;
}

bool Input::TriggerMouseRight()
{
	// 前回が0で、今回が0でなければトリガー
	if (!mouseStatePre.rgbButtons[1] && mouseState.rgbButtons[1]) {
		return true;
	}

	// トリガーでない
	return false;
}

bool Input::TriggerMouseMiddle()
{
	// 前回が0で、今回が0でなければトリガー
	if (!mouseStatePre.rgbButtons[2] && mouseState.rgbButtons[2]) {
		return true;
	}

	// トリガーでない
	return false;
}

const Input::MouseMove& Input::GetMouseMove()
{
	MouseMove tmp;
	tmp.lX = mouseState.lX;
	tmp.lY = mouseState.lY;
	tmp.lZ = mouseState.lZ;
	return tmp;
}
