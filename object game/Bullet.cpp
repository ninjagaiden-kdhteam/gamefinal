#include "Bullet.h"
#define BULLET_SPEED 0.2
Bullet::Bullet()
{
	type = BULLET;
	this->AddAnimation(100);
	this->AddAnimation(101);
}

Bullet::Bullet(float x, float y, int direction, int frameAni)
{
	ani = frameAni;
	this->AddAnimation(100);
	this->AddAnimation(101);
	this->type = BULLET;
	this->position = D3DXVECTOR3(x, y, 0);
	this->direction = direction;
	this->w = 8;
	this->h = 3;
	if (direction > 0) vx = 0.2f;
	else vx = -0.2f;
	if (frameAni == 1)
	{
		if (direction > 0) vx = 0.1f;
		else vx = -0.1f;
	}
	this->SetActive(1);
}

Bullet::~Bullet()
{
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (this->IsInCamera() == false) this->SetActive(0);
	if (this->IsActive == 0) return;
	GameObject::Update(dt);
	position.x += dx;
	position.y += dy;
}

void Bullet::Render()
{
	if (this->IsActive == 0) return;
	int isHitting = 0;
	animations[ani]->Render(position.x, position.y, isHitting, direction, xx, yy, w, h, -1);
	//RenderBoundingBox();
}

void Bullet::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + BULLET_W;
	b = t + BULLET_H;
}