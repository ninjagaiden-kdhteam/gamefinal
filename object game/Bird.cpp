#include "Bird.h"
#include "debug.h"
#include <cmath>


Bird::Bird(int id, int type, int x, int y, int direction,int leftX,int rightX, int distance) :Enemy::Enemy(id, type, x, y, direction, leftX, rightX, distance)
{
	this->AddAnimation(50);
	if (direction > 0) vx = BIRD_SPEED;
	else vx = -BIRD_SPEED;
	a = 0;
	b = -9999;
	isInNinja = 0;
	InitVx = vx;
}

void Bird::CaculateAB(float xx, float yy)
{
	float x1 = this->position.x;
	float y1 = this->position.y;
	float x2 = xx;
	float y2 = yy;
	this->a = (y1 - y2) / (x1 - x2);
	this->b = y1 - (this->a)*x1;
	change = xx;
}

void Bird::CaculateABwithNinja()
{
	

	float x1 = this->position.x;
	float y1 = this->position.y;
	float x2 = Ninja::GetInstance()->GetPosition().x;
	float y2 = Ninja::GetInstance()->GetPosition().y-20;
	if (abs(x1 - x2) < 50)
	{
		if (vx<0)
		{
			x2 -= 70;
			y2 = y1;// -= 20;
		}
		else 
		{
			x2 += 70;
			y2 = y1;//-= 20;
		}
	}
	this->a = (y1 - y2) / (x1 - x2);
	this->b = y1 - (this->a)*x1;
	change = x2;
	if (position.x > Ninja::GetInstance()->GetPosition().x)
	{
		vx = -BIRD_SPEED;
	}
	else vx = BIRD_SPEED;
}

void Bird::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt);
	if (a == 0 && b == -9999) CaculateABwithNinja();
	position.x += dx;
	position.y = this->a*position.x + this->b+10;
	//Nếu va chạm ninja thì tính lại phương trình bay
	/*if (isInNinja == 0 && checkAABB(Ninja::GetInstance()))
	{
		isInNinja = 1;
		if (vx > 0)
		{
			CaculateAB(position.x + 60, position.y);
			change = position.x + 60;
		}
		else
		{
			CaculateAB(position.x - 60, position.y);
			change = position.x - 60;
		}

	}*/

	if (vx > 0)
	{
		//Nếu chạm biên phải
		if (position.x >= change)
		{
			//và va chạm ninja
			if (checkAABB(Ninja::GetInstance()) == true)
			{
				vx = BIRD_SPEED; //vẫn bay về trái
				CaculateAB(position.x + 70, position.y);
			}
			else//nếu không va chạm
			{
				//vx = -NINJA_WALKING_SPEED;
				CaculateABwithNinja();
			}
		}
	}
	else
	{
		//Nếu chạm biên trái
		if (position.x <= change)
		{
			//và va chạm ninja
			if (checkAABB(Ninja::GetInstance()) == true)
			{
				vx = -BIRD_SPEED; //vẫn bay về trái
				CaculateAB(position.x -(float)70, position.y);
			}
			else//nếu không va chạm
			{
				//vx = NINJA_WALKING_SPEED;
				CaculateABwithNinja();
			}
		}
	}

	if (position.x > Ninja::GetInstance()->GetPosition().x)
		direction = -1;
	else direction = 1;

	if (position.x >= rightX) { position.x = rightX; direction = -1; vx = -vx; }
	if (position.x <= leftX) { position.x = leftX; direction = 1; vx = -vx; }

}
void Bird::Render()
{
	int lientuc = 0;
	animations[BIRD_ANI]->Render(position.x, position.y, lientuc, this->direction, xx, yy, w, h);
	//RenderBoundingBox();
}

void Bird::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + BIRD_W;
	b = t + BIRD_H;
}
Bird::~Bird()
{

}

void Bird::SetActive(int x)
{
	GameObject::SetActive(x);
	if (x != 0) return;
	a = 0;
	b = -9999;
	
}