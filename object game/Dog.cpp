#include "Dog.h"

void Dog::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt);
	vy -= GRAVITY;


	//***********************************************************************

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		position.x += dx;
		position.y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// block 
		position.x += min_tx * dx + nx * 0.2f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		position.y += min_ty * dy - ny * 0.2f;

		//if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	if (position.x > rightX-1) { position.x = rightX; direction = -1; vx = -vx; }
	if (position.x < leftX+1) { position.x = leftX; direction = 1; vx = -vx; }
	if (position.y < 0)
	{
		IsActive = 0;
		position = initposition;
	}
}
void Dog::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + DOG_W;
	b = t + DOG_H;
}
void Dog::Render()
{
	int lientuc = 0;
	animations[DOG_ANI]->Render(position.x, position.y, lientuc, this->direction, xx, yy, w, h);
	//RenderBoundingBox();
}


Dog::Dog(int id, int type, int x, int y, int direction, int leftX, int rightX,int distance) :Enemy::Enemy(id, type, x, y, direction, leftX, rightX, distance)
{
	this->AddAnimation(40);
	this->vx = DOG_WALKING;
	if (direction < 0) vx *= -1;
	InitVx = vx;
}

Dog::~Dog()
{
}