#include "GreenSniper.h"

GreenSniper::GreenSniper(int id, int type, int x, int y, int direction, int leftX, int rightX, int distance) :Enemy::Enemy(id, type, x, y, direction, leftX, rightX, distance)
{
	this->AddAnimation(110);
	this->AddAnimation(111);
	time = 0.0f;
	bullet = new Bullet(x, y, direction,0);
	countFrame = -1;
}


void GreenSniper::Render()
{
	int lientuc = 0;
	int ani = GREENSNIPER_ANI;
	if (countFrame != -1)
	{
		ani = GREENSNIPER_ANI_ATTACK;
		countFrame++;
		if (countFrame > 4) countFrame = -1; //render liên tục 4 frame để thấy bắn tia lửa
	}
	animations[ani]->Render(position.x, position.y, lientuc, this->direction, xx, yy, w, h);
	bullet->Render();
	//RenderBoundingBox();
}

void GreenSniper::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Xử lý va chạm gạch
	GameObject::Update(dt);
	vy -= GRAVITY;
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


	time = time + dt;

	//chưa tới thời điểm bắn ra đạn mới
	if (time < 1500)
		bullet->Update(dt);

	//xóa đạn cũ đi, bắn đạn mới
	if (time > 1500) {
		time = 0;
		delete bullet;
		bullet = new Bullet(position.x, position.y, direction,0);
		bullet->Update(dt);
		countFrame++;
	}
	//hướng phụ thuộc vào hướng của ninja
	if (this->position.x > Ninja::GetInstance()->GetPosition().x)
		direction = -1;
	else direction = 1;
}

void GreenSniper::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + GREENSNIPER_W;
	b = t + GREENSNIPER_H;
}

GreenSniper::~GreenSniper()
{
}