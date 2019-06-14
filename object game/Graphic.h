#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Graphic
{
private:
	static Graphic * __instance;
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3D9 d3d;
	D3DPRESENT_PARAMETERS d3dpp;
	LPD3DXFONT font;
	LPD3DXFONT font1;
	HRESULT result;
	bool fullscreen;
	int width;
	int heigt;
	D3DCOLOR color;
	LPD3DXSPRITE spriteHandler;
public:
	~Graphic();
	Graphic();
	void Initialize(HWND);
	static Graphic * GetInstance();
	void Clear();
	void Begin();
	void End();
	void Present();
	void DrawMessage(int left, int top, int right, int bottom, D3DCOLOR color, LPCWSTR msg);
	void DrawMessage1(int left, int top, int right, int bottom, D3DCOLOR color, LPCWSTR msg);
	LPD3DXSPRITE GetSpriteHandler() { return spriteHandler; }

	LPDIRECT3DDEVICE9 GetDevice() { return d3ddv; }
};

