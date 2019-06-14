#include "Graphic.h"
Graphic * Graphic::__instance = NULL;

Graphic::Graphic()
{
	d3d = NULL;
	d3ddv = NULL;
	font = NULL;
	fullscreen = false;;
}


Graphic::~Graphic()
{
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

void Graphic::Initialize(HWND hWnd)
{
	color = D3DCOLOR_XRGB(0, 0, 0);
	d3d = Direct3DCreate9(D3D_SDK_VERSION);


	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));


	if (fullscreen) // Neu fullscreen
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;// 24-bit color
	else
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8; // Su dung thiet lap cua desktop
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.Windowed = (!fullscreen);

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	//Tạo font
	D3DXCreateFont(d3ddv,
		35,
		0,
		FW_BOLD,
		0,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH || FF_DONTCARE,
		TEXT("Jokerman"), &font);

	D3DXCreateFont(d3ddv,
		17,
		0,
		FW_BOLD,
		0,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH || FF_DONTCARE,
		TEXT("Arial"), &font1);
	D3DXCreateSprite(d3ddv, &spriteHandler);
}

Graphic * Graphic::GetInstance()
{
	if (__instance == NULL) __instance = new Graphic();
	return __instance;
}

void Graphic::Clear()
{
	// 2nd param is set to NULL so that it clears the entire back buffer
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void Graphic::Begin()
{
	d3ddv->BeginScene();
}

void Graphic::End()
{
	d3ddv->EndScene();
}

void Graphic::Present()
{
	// Present our scene to the window
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void Graphic::DrawMessage(int left, int top, int right, int bottom, D3DCOLOR color, LPCWSTR msg)
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
	font->DrawTextW(NULL, msg, -1, &rect, 0, color);
}
void Graphic::DrawMessage1(int left, int top, int right, int bottom, D3DCOLOR color, LPCWSTR msg)
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
	font1->DrawTextW(NULL, msg, -1, &rect, 0, color);
}

