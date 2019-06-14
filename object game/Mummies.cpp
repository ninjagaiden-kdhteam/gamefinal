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
		position.x += min_tx * dx + nx * 0.2f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		position.y += min_ty * dy - ny * 0.2f;

		if (nx != 0) {
			direction = -direction;
			vx = -vx;
		}
		if (ny != 0) vy = 0;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	if (position.x > rightX) { position.x = rightX; direction=-1; vx = -vx; }
	if (position.x < leftX) { position.x = leftX; direction=1; vx = -vx; }
	time += dt;
	//direction thay đổi dựa vào direction của ninja
	if (this->position.x > Ninja::GetInstance()->GetPosition().x)
		direction = -1;
	else direction = 1;

}

void Mummies::Render()
{
	int ani = MUMMIES_ANI_WALKING; //ban đầu là trạng thái đi

	if (time > 1000) //cách 1s là chuyển sang trạng thái attack
	{
		time = 0;
		ani = MUMMIES_ANI_ATTACK;
		countframe++; //countFrame từ 0->1
	}

	if (countframe > 0 && countframe < 6) //nếu đang acttack và số frame đã render vẫn chưa vượt quá số frame attack
	{
		ani = MUMMIES_ANI_ATTACK;
		countframe++; //tăng frame
	}
	else
	{
		ani = MUMMIES_ANI_WALKING; //về lại render trạng thái đi bình thường
		countframe = 0;//tắt cờ attack
	}

	int lientuc = 0;
	animations[ani]->Render(position.x, position.y, lientuc, this->direction, xx, yy, w, h);

	//render cho knife
	Knife *kni = dynamic_cast<Knife *>(knife);
	if (ani == MUMMIES_ANI_ATTACK) kni->SetActive(1);// kni->setOnce();
	kni->Render(position.x,position.y,direction,this->dt);
	//RenderBoundingBox();
}
Mummies::Mummies(int id, int type, int x, int y, int direction, int leftX, int rightX,int distance) :Enemy::Enemy(id, type, x, y, direction, leftX, rightX, distance)
{
	this->AddAnimation(80);//animation đi
	this->AddAnimation(81);//animation attack
	this->vx = 0.03;// MUMMIES_WALKING;
	this->state = State::WALKING;
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