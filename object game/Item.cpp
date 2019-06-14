#include "Item.h"

void Item::Render()
{
	int isHitting = 0;
	int ani = itemtype;
	this->animations[ani]->Render(position.x, position.y, isHitting, direction, xx, yy, w, h);	
	//RenderBoundingBox();
}

void Item::setDie()
{
	this->die = true;
	this->IsActive = 0;
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->IsInCamera() == false)
	{
		setDie();
		return;
	}
	GameObject::Update(dt);
	vy -= GRAVITY;


	//Xử lý va chạm gạch

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

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	timeDisplayed += dt;
	if (timeDisplayed > TIME_DISPLAY)
		setDie();
}

Item::Item(int itemtype,float x,float y)
{
	if (this->die == true) return;
	timeDisplayed = 0;
	this->die = false;
	this->IsActive = 1;
	this->position = D3DXVECTOR3(x, y, 0);
	vx = 0;
	vy = 0;
	this->itemtype = (EItem)itemtype;
	this->AddAnimation(180);//BONUSPOINTBLUE
	this->AddAnimation(181);//BONUSPOINTRED
	this->AddAnimation(191);//SPIRITPOINTSRED
	this->AddAnimation(190);//SPIRITPOINTSBLUE
	this->AddAnimation(200);//TIMEFREEZE
	this->AddAnimation(210);//HEALTH
	this->AddAnimation(240);//FLAMES
	this->AddAnimation(220);//THROWINGSTAR
	this->AddAnimation(230);//WINDMILLSTAR
}

Item::~Item()
{
}

void Item::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + ITEM_W;
	b = t + ITEM_H;
}
