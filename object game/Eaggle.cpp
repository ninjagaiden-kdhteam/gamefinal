#include "Eaggle.h"


Eaggle::Eaggle(int id, int type, int x, int y, int direction,int itemtype) :Container::Container(id, type, x, y, direction, itemtype)
{
	this->AddAnimation(130);
}

void Eaggle::Render()
{
	int lientuc = 0;
	animations[EAGGLE_ANI]->Render(position.x, position.y, lientuc, this->direction, xx, yy, w, h);
	//RenderBoundingBox();
}

void Eaggle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//không cần update, mấy con này đứng yên
}

void Eaggle::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + EAGGLE_W;
	b = t + EAGGLE_H;
}

Eaggle::~Eaggle()
{
}
