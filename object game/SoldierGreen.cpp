#include "SoldierGreen.h"
void SoldierGreen::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt);
	vy -=GRAVITY;


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

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	if (position.x >= rightX) { position.x = rightX; direction = 0; vx = -vx; }
	if (position.x <= leftX) { position.x = leftX; direction = 1; vx = -vx; }
	time = time + dt;

	//chưa đến thời điểm bắn ra đạn mới
	if (time < 1500)
		bullet->Update(dt);

	//bắn ra đạn mới
	if (time > 1500) {
		time = 0;
		delete bullet;
		bullet = new Bullet(position.x, position.y - 8, direction,0);
		bullet->Update(dt);
		countFrame++;
	}
	
}

void SoldierGreen::Render()
{
	int lientuc = 0;
	int ani = SOLDIERGREEN_ANI_WALKING;
	if (countFrame != -1)
	{
		ani = SOLDIERGREEN_ANI_ATTACK;
		countFrame++;
		if (countFrame > 4) countFrame = -1; //đếm cho tới đủ 4 frame attack
	}
		
	animations[ani]->Render(position.x, position.y, lientuc, this->direction, xx, yy, w, h);

	//RenderBoundingBox();
	bullet->Render(); //render cho đạn của nó
}
SoldierGreen::SoldierGreen(int id, int type, int x, int y, int direction, int leftX, int rightX,int distance) :Enemy::Enemy(id, type, x, y, direction, leftX, rightX, distance)
{
	time = 0.0f;
	bullet = new Bullet(x, y - 8, direction,0);
	this->AddAnimation(70);
	this->AddAnimation(71);
	this->vx = SOLDIER_GREEN_WALKING;
	if (direction < 0) vx *= -1;
	countFrame = -1;
	InitVx = vx;
}
void SoldierGreen::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + SOLDIERGREEN_W;
	b = t + SOLDIERGREEN_H;
}
SoldierGreen::~SoldierGreen()
{

}