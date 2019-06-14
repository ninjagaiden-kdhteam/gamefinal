#pragma once
#include "Graphic.h"
#include "Camera.h"
#include "GameDefinitions.h"
class Sprite
{
	LPDIRECT3DTEXTURE9 texture; //texture chứa sprite
	LPD3DXSPRITE spriteHandle; //dùng để vẽ
	int top, bottom, left, right; //tọa độ hình chữ nhật của sprite trong texture chứa nó
	int id; //id của sprite
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
	//vẽ sprite có transform, alpha là biến dùng để check và đổi màu trong hệ màu(khi ninja bị tấn công hoặc chết=> đổi màu vẽ)
	void Render(float x, float y, float dx, float dy, int direction, int backFrame,int alpha=KHONG_NHAY);
	void Render(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int direction, int xx, int yy, int backFrame,int alpha);
	~Sprite();
};

typedef Sprite* LPSPRITE;