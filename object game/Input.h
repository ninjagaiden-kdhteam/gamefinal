#pragma once
#include <dinput.h>
#include "debug.h"

class Input {
private:
	static Input* __Instance;
	LPDIRECTINPUT8 dinput=NULL;
	LPDIRECTINPUTDEVICE8 dkeyboard=NULL;

	char keys[256];
	char keysBuffer[256];
public:
	//Khởi tạo DI
	int InitDirectInput();
	//Khởi tạo bàn phím
	int InitKeyboard(HWND);
	//Lưu trạng thái của bàn phím
	void PollKeyboard();

	//Sự kiện Nhấn phím
	int isKeyDown(int key);
	//Sự kiện Nhả phím
	int isKeyRelease(int key);
	//Nhấn và nhả ngay lập tức
	int isKeyPress(int key);

	void KillKeyboard();
	static Input* GetInstance();
};
