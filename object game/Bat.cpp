#include "Bat.h"


Bat::Bat(int id, int type, int x, int y, int direction,int leftX,int rightX, int distance) :Enemy::Enemy(id, type, x, y, direction, leftX, rightX, distance)
{
	this->AddAnimation(30);
	vx = WALKING_SPEED;
	InitVx = vx;
}
Bat::~Bat()
{
}

void Bat::Render()
{
	int lientuc = 0;
	animations[BAT_ANI]->Render(position.x, position.y, lientuc, this->direction, xx, yy, w, h);
	//RenderBoundingBox();
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{ 
	GameObject::Update(dt);
	position.x += dx;
	position.y = sin(position.x * 8) * 6 + 50;

	if (position.x >= rightX) { position.x = rightX; direction = -1; vx = -vx; }
	if (position.x <= leftX) { position.x = leftX; direction = 1; vx = -vx; }
}

void Bat::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + BAT_W;
	b = t + BAT_H;
}