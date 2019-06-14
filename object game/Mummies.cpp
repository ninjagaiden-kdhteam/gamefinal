#include "Mummies.h"
#include "debug.h"
void Mummies::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
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
		position.x += min_tx * dx + nx * 0.2f;
		position.y += min_ty * dy - ny * 0.2f;

		if (nx != 0) {
			direction = -direction;
			vx = -vx;
		}
		if (ny != 0) vy = 0;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	if (position.x >= rightX) { position.x = rightX; direction=-1; vx = -vx; }
	if (position.x <= leftX) { position.x = leftX; direction=1; vx = -vx; }
	time += dt;
	
	if (this->position.x > Ninja::GetInstance()->GetPosition().x)
		direction = -1;
	else direction = 1;

}

void Mummies::Render()
{
	int ani = MUMMIES_ANI_WALKING; 

	if (time > 1000)
	{
		time = 0;
		ani = MUMMIES_ANI_ATTACK;
		countframe++; 
	}

	if (countframe > 0 && countframe < 6)
	{
		ani = MUMMIES_ANI_ATTACK;
		countframe++;
	}
	else
	{
		ani = MUMMIES_ANI_WALKING;
		countframe = 0;
	}

	int lientuc = 0;
	animations[ani]->Render(position.x, position.y, lientuc, this->direction, xx, yy, w, h);

	
	Knife *kni = dynamic_cast<Knife *>(knife);
	if (ani == MUMMIES_ANI_ATTACK) kni->SetActive(1);
	kni->Render(position.x,position.y,direction,this->dt);
}
Mummies::Mummies(int id, int type, int x, int y, int direction, int leftX, int rightX,int distance) :Enemy::Enemy(id, type, x, y, direction, leftX, rightX, distance)
{
	this->AddAnimation(80);
	this->AddAnimation(81);
	this->vx = 0.03;
	knife = new Knife();
	time = 0;
	countframe = 0;
	InitVx = vx;
}
void Mummies::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + MUMMIES_W;
	b = t + MUMMIES_H;
}
Mummies::~Mummies()
{

}