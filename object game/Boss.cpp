#include "Boss.h"
#include "debug.h"
#include <cmath>
#define BOSS_JUMP_SPEED_Y		0.35f
#define BOSS_SPEED 0.15f
Boss::Boss()
{
	this->HP = 16;
	this->type = BOSS;
	position.x = 0;
	position.y = 0;
	direction = -1;
	vx = -BOSS_SPEED;
	vy = -0.14f;
	this->AddAnimation(250);
	this->AddAnimation(251);
	this->state = State::JUMP;
	isStopping = 0;
	atLeft=0;
	atRight = 0;
	countShoot = 0;
	bullets.clear();

}

void Boss::updateBullet(DWORD dt)
{
	if (bullets.size() == 0) return;
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Update(dt);
}

Boss::~Boss(){}

void Boss::startStopping()
{
	if (atLeft == 1 && countShoot % 3 == 0) //nếu bắt đầu từ biên trái và di chuyển qua lại đúng 3 lần thì bắn đạn
	{
		deleteBullet(); //xóa hết đạn cũ
		//tạo đạn mới
		Bullet* b1 = new Bullet(211, 86, -1, 1);
		Bullet* b2 = new Bullet(190, 66, -1, 1);
		Bullet* b3 = new Bullet(170, 46, -1, 1);
		bullets.push_back(b1);
		bullets.push_back(b2);
		bullets.push_back(b3);
	}
	else
		if (atRight == 1 && countShoot % 3 == 0)
		{
			deleteBullet();
			Bullet* b1 = new Bullet(37, 86, 1, 1);
			Bullet* b2 = new Bullet(57, 66, 1, 1);
			Bullet* b3 = new Bullet(77, 46, 1, 1);
			bullets.push_back(b1);
			bullets.push_back(b2);
			bullets.push_back(b3);
		}

	countShoot++; //tăng biến đếm mỗi lần tới biên
	isStopping = 1; //tới biên là dừng 1 khoảng time
	start_stopping = GetTickCount();
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT> *bricks)
{
	this->state = JUMP;
	if (HP == 0) return;
	updateBullet(dt); //update vị trí cho đạn
	if (isStopping == 1) //dừng lại ở mỗi bên 1 chút
	{
		this->state = IDLE;
		if (GetTickCount() - start_stopping >= TIME_STOP)
		{
			isStopping = 0;
			start_stopping = 0;
		}
		else return;
	}
	GameObject::Update(dt);
	position.x += dx;
	position.y = sqrt(abs(90 * 90 - position.x*position.x)); //phương trình nửa đường tròn

	if (position.x >=88) //88 là bán kính đường tròn (90) xấp xỉ
	{
		direction = -1;
		vx = -BOSS_SPEED;
		if(atLeft==1) startStopping();
		atRight = 1; //đánh dấu đã qua biên phải
		atLeft = 0; //bỏ đánh dấu biên trái
	}
	if (position.x <= -88)
	{
		
		direction = 1;
		vx = BOSS_SPEED;
		if(atRight==1) startStopping();
		atLeft = 1;
		atRight = 0;
	}
	
}
void Boss::Render()
{
	int lientuc = 0;
	int ani;
	if (this->state == State::IDLE) ani = 0;
	else ani = 1;

	animations[ani]->Render(position.x+110, position.y+70, lientuc, this->direction, xx, yy, w, h);
	if (bullets.size() != 0)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->Render();
		}
	}
	
	//RenderBoundingBox();
}
void Boss::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	D3DXVECTOR3 p = position;
	p.x += 110;
	p.y += 70;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + BOSS_W;
	b = t + BOSS_H;
}
