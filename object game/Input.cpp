#include "Input.h"

Input* Input::__Instance = NULL;

int Input::InitDirectInput()
{
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&dinput,
		NULL);

	if (result != DI_OK)
		return 0;

	result = dinput->CreateDevice(GUID_SysKeyboard, &dkeyboard, NULL);

	if (result != DI_OK)
		return 0;

	return 1;
}

int Input::InitKeyboard(HWND hwnd)
{
	HRESULT result = dkeyboard->SetDataFormat(&c_dfDIKeyboard);

	if (result != DI_OK)
		return 0;

	result = dkeyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	if (result != DI_OK)
		return 0;

	result = dkeyboard->Acquire();

	if (result != DI_OK)
		return 0;

	return 1;
}

void Input::PollKeyboard()
{
	for (int i = 0; i < 256; i++)
		keysBuffer[i] = keys[i];

	HRESULT hr = dkeyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
	//kiểm tra nếu mất acquire thì acquire lại
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = dkeyboard->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else
				return;
		}
		else
		{
			DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}
}

int Input::isKeyDown(int key)
{
	return (keys[key] & 0x80);
}

int Input::isKeyRelease(int key)
{
	return (!isKeyDown(key) && (keysBuffer[key] & 0x80));
}

int Input::isKeyPress(int key)
{
	return (isKeyDown(key) && !(keysBuffer[key] & 0x80));
}

void Input::KillKeyboard()
{
	if (dkeyboard != NULL)
	{
		dkeyboard->Unacquire();
		dkeyboard->Release();
		dkeyboard = NULL;
	}
}

Input * Input::GetInstance()
{
	if (__Instance == NULL) __Instance = new Input();
	return __Instance;
}
