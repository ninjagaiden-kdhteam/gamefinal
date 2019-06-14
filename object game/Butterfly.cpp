#include "Butterfly.h"
void Butterfly::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//không cần update, mấy con này đứng yên
}
void Butterfly::Render()
{
	int lientuc = 0;
	if (IsTimeFreeze)
		animations[BUTTERFLY_ANI]->Render(position.x, position.y, lientuc, this->direction, xx, yy, w, h, -1, 0, -1, false);
	else
		animations[BUTTERFLY_ANI]->Render(position.x, position.y, lientuc, this->direction, xx, yy, w, h);
	//RenderBoundingBox();
}

Butterfly::Butterfly(int id, int type, int x, int y, int direction, int itemtype) :Container::Container(id, type, x, y, direction, itemtype)
{
	this->AddAnimation(60);
}
void Butterfly::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + BUTTERFLY_W;
	b = t + BUTTERFLY_H;
}
Butterfly::~Butterfly()
{

}