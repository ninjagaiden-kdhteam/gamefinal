#include "Sprite.h"
#include "Ninja.h"
#include "debug.h"


Sprite::Sprite()
{

}

Sprite::Sprite(LPDIRECT3DTEXTURE9 tex)
{
	this->texture = tex;
	D3DXCreateSprite(Graphic::GetInstance()->GetDevice(), &spriteHandle);
}

Sprite::Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, float xx, float yy)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
	this->dx = xx;
	this->dy = yy;
	D3DXCreateSprite(Graphic::GetInstance()->GetDevice(), &spriteHandle);
}

void Sprite::RenderNotTransForm(float x, float y)
{
	if (spriteHandle && texture)
	{
		spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);
		RECT rect;
		rect.top = top;
		rect.left = left;
		rect.bottom = bottom;
		rect.right = right;
		spriteHandle->Draw(texture, &rect, NULL, &D3DXVECTOR3(x, y, 0), D3DCOLOR_XRGB(255, 255, 255));
		spriteHandle->End();
	}
}

//backframe=1: đang vẽ background,=0: ngược lại
void Sprite::Render(float x, float y, float dx, float dy, int direction, int backFrame,int alpha)
{
	if (spriteHandle && texture)
	{
		spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);

		if (backFrame != -1)
		{
			this->Render(x, y, texture, backFrame * SIZE_TILE_SET, 0, backFrame * SIZE_TILE_SET + SIZE_TILE_SET, 0+SIZE_TILE_SET, direction, dx, dy, backFrame,alpha);
		}
		else this->Render(x, y, texture, left, top, right, bottom, direction, dx, dy, backFrame,alpha);

		spriteHandle->End();
	}
}

void Sprite::Render(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int direction, int xx, int yy, int backFrame,int alpha)
{
	y += yy; //luôn cộng cho độ xê dịch theo trục y
	if (direction <= 0) //độ xê dịch theo trục x thì khi nào direction=trái mới cộng, vì lật hình qua trái cần điều chỉnh
	{
		x += xx;
	}

	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	D3DXVECTOR3 pos(x, y, 0);


	if (backFrame < 0)
	{
		pos = Camera::GetInstance()->Transform(D3DXVECTOR3(x, y, 0));
		D3DXMATRIX oldTransform;
		spriteHandle->GetTransform(&oldTransform);//Lấy ma trận cũ
		D3DXMATRIX newTransform;
		D3DXVECTOR2 center = D3DXVECTOR2(pos.x + (right - left) / 2, pos.y + (bottom - top) / 2);//Lấy tâm của sprite
		D3DXVECTOR2 rotate = D3DXVECTOR2(direction > 0 ? 1 : -1, 1);//Ma trận xoay chiều
		D3DXMatrixTransformation2D(&newTransform, &center, 0.0f, &rotate, NULL, 0.0f, NULL);//Tiến hành transform
		D3DXMATRIX finalTransform = newTransform * oldTransform;
		spriteHandle->SetTransform(&finalTransform);

		if (alpha== NHAY_MOTMAU)
			spriteHandle->Draw(texture, &r, NULL, &pos, D3DCOLOR_ARGB(64, 255, 255, 255)); //nháy khi ninja bị tấn công
		else 
			if (alpha == GODMODE)
				spriteHandle->Draw(texture, &r, NULL, &pos, D3DCOLOR_XRGB(255, 255, 0)); //đổi màu vẽ ninja khi bật godmode
			else
			spriteHandle->Draw(texture, &r, NULL, &pos, D3DCOLOR_XRGB(255, 255, 255)); //vẽ bình thường
	
		spriteHandle->SetTransform(&oldTransform);
	}
	else 
	{
		if (alpha == KHONG_NHAY)
			spriteHandle->Draw(texture, &r, NULL, &pos, D3DCOLOR_XRGB(255, 255, 255)); //vẽ background bình thường
		else
			spriteHandle->Draw(texture, &r, NULL, &pos, D3DCOLOR_ARGB(alpha, 0, 255, 255));	//background nháy khi ninja chơi thua	
	}
	return;
}

Sprite::~Sprite()
{
}
