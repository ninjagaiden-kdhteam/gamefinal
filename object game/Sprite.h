#pragma once
#include "Graphic.h"
#include "Camera.h"
#include "GameDefinitions.h"
class Sprite
{
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE spriteHandle; 
	int top, bottom, left, right; //tọa độ hình chữ nhật của sprite trong texture chứa nó
	int id; 
	float dx, dy; //độ xê dịch vị trí so với frame trước
public:

	Sprite();
	Sprite(LPDIRECT3DTEXTURE9 tex);
	Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, float xx, float yy);
	float GetWidth() { return right - left; }
	float GetHeight() { return bottom - top; }
	float GetDy() { return dy; }
	float GetDx() { return dx; }
	//vẽ sprite lên màn hình không transform vị trí
	void RenderNotTransForm(float x, float y);
	void Render(float x, float y, float dx, float dy, int direction, int backFrame,int alpha=KHONG_NHAY);
	void Render(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int direction, int xx, int yy, int backFrame,int alpha);
	~Sprite();
};

typedef Sprite* LPSPRITE;