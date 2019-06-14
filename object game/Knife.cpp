#include "Knife.h"

void Knife::Render(float xMum, float yMum, int direction,DWORD dt)
{
	if (IsActive== 0) return; //nếu đang ko được ném, thoát
	if (position.x == -1) //mới được ném ra
	{
		//vị trí+hướng knife= mummies 
		position.x = xMum;
		position.y = yMum;
		this->direction = direction;
		if (direction > 0) vx = WALKING_SPEED/2;
		else vx = -WALKING_SPEED/2;
		vy = JUMP_SPEED_Y/2;
	}
	Update(dt); //update trước khi render
	if (IsActive == 0) return; //kiểm tra lại biến cờ
	int frameLienTuc = 0;
	animations[KNIFE_ANI]->Render(position.x, position.y, frameLienTuc, direction, xx, yy, w, h);
	//RenderBoundingBox();
}

void Knife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (IsGamePause) return;
	GameObject::Update(dt); //update dx,dy
	vy-= GRAVITY; //rơi theo trọng lực
	position.x += dx;
	position.y += dy;
	if (position.y <= 24) //nếu đã bị rớt xuống đất
	{
		IsActive = 0;//trở về đánh dấu chưa được ném
		position.x = -1; //set lại vị trí chưa được ném
	}
}

Knife::Knife()
{
	IsActive = 0;//hiện tại dao chưa được mummies ném ra
	position.x = -1; //vị trí khởi tạo, đánh dấu chưa được ném ra
	this->type = KNIFE;
	this->AddAnimation(170);
}

Knife::~Knife()
{
}

void Knife::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + KNIFE_W;
	b = t + KNIFE_H;
}