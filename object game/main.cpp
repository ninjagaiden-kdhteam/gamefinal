#include <windows.h>
#include "Game.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT);
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wcx;

	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WinProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);

	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = CLASS_NAME;
	wcx.hIconSm = NULL;

	if (RegisterClassEx(&wcx) == 0)
		return false;

	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	HWND hWnd;

	hWnd = CreateWindow(
		CLASS_NAME,
		GAME_TITLE,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GAME_WIDTH,
		GAME_HEIGHT,
		(HWND)NULL,
		(HMENU)NULL,
		hInstance,
		(LPVOID)NULL);

	hwndGlobal = hWnd;

	if (!hWnd)
		return 0;
	if (!FULLSCREEN)
	{
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		MoveWindow(hWnd,
			0,
			0,
			GAME_WIDTH + (GAME_WIDTH - clientRect.right),
			GAME_HEIGHT + (GAME_HEIGHT - clientRect.bottom),
			TRUE);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//SetWindowPos(hWnd, 0, 0, 0, GAME_WIDTH * 2, GAME_HEIGHT * 2+200, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	//Window message loop

	MSG msg;
	Game * game =Game::GetInstance();

	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / FRAMES_PER_SECOND;
	game->Initialize(hWnd, GAME_WIDTH, GAME_HEIGHT);
	while (true)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			break;
		}

		else

		{
			DWORD now = GetTickCount();

			// dt: the time between (beginning of last frame) and now
			// this frame: the frame we are about to render
			DWORD dt = now - frameStart;

			if (dt >= tickPerFrame)
			{
				frameStart = now;
				game->Update(dt);
				game->Run();
			}
			else
				Sleep(tickPerFrame - dt);
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_SYSKEYDOWN:
		if (lParam & 0x20000000)
			return 0;
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

