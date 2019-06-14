#include "WindmillStar.h"
#include "debug.h"

WindmillStar::WindmillStar()
{
	this->type = WINDMILLSTAR;
	this->AddAnimation(160);
	vx = WALKING_SPEED;
	vy = 0;
	//vị trí khởi tạo khi chưa được phóng ra
	position.x = -1;
	position.y = -1;
	isLeftNinja = false; //chưa rời khỏi ninja
}

//tính lại hệ số cho phương trình bay y=ax+b của windmillstar
void WindmillStar::CaculateAB(float xninja, float yninja)
{
	float x1 = this->position.x;
	float y1 = this->position.y;
	float x2 = Ninja::GetInstance()->GetPosition().x;//xninja;
	float y2 = Ninja::GetInstance()->GetPosition().y;// yninja;
	this->a = (y1 - y2) / (x1 - x2);
	this->b = y1 - (this->a)*x1;
}

void WindmillStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	position.x += dx;
	position.y = a*this->position.x + b; //y=ax+b
}

//check xem có đụng ninja thì biến mất
bool WindmillStar::collisionWithNinja()
{
	if (isLeftNinja == false) return false;
	if (this->checkAABB(Ninja::GetInstance())) return true;
	return false;
}

void WindmillStar::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + WINDMILLSTAR_W;
	b = t + WINDMILLSTAR_H;
}

bool WindmillStar::checkState(float xNinja, float yNinja, int ninjaAni, int ninjaDirection, int ninjaFrame, DWORD dt)
{
	//nếu mới được phóng ra
	if (position.x == -1)
	{
		//set hướng và vị trí dựa vào ninja
		this->direction = ninjaDirection;
		position.x = xNinja + 15;
		position.y = yNinja;

		if (ninjaDirection > 0)
		{
			vx = WALKING_SPEED;
			change = xNinja + 60; //thay đổi biên
		}
		else
		{
			vx = -WALKING_SPEED;
			position.x = xNinja - 15;
			change = xNinja - 70;//thay đổi biên
		}
		CaculateAB(xNinja, yNinja); //tính hệ số cho pt bay: y=ax+b
	}
	this->Update(dt); //update vị trí

	//nếu ra ngoài camera hoặc va chạm với ninja thì biến mất
	if (!this->IsInCamera() || collisionWithNinja())
	{
		position.x = -1;
		position.y = -1;
		this->IsActive = 0;
		isLeftNinja = false;
		Ninja::GetInstance()->setCreateStar(0);
		return false;
	}

	//check xem đã bay tới biên chưa
	if (this->direction > 0)
	{
		if (position.x >= change)
		{
			isLeftNinja = true;
			CaculateAB(xNinja, yNinja);
			this->vx = -WALKING_SPEED;
			change = this->position.x - (position.x - xNinja) * 2;
			this->direction = 0;
		}

	}
	else
	{
		if (position.x <= change)
		{
			isLeftNinja = true;
			CaculateAB(xNinja, yNinja);
			this->vx = WALKING_SPEED;
			change = this->position.x + (xNinja - position.x) * 2;
			this->direction = 1;
		}
	}
	return true;
}

void WindmillStar::Render(float xNinja, float yNinja, int ninjaAni, int ninjaDirection, int ninjaFrame, DWORD dt)
{
	if (this->IsActive == 0) return; //nếu đang bị tắt active thì thoát
	int frameLienTuc = 0;
	//nếu check update, vị trí, trạng thái ok thì mới render
	if (checkState(xNinja, yNinja, ninjaAni, ninjaDirection, ninjaFrame, dt))
		this->animations[WINDMILLSTAR_ANI]->Render(position.x, position.y, frameLienTuc, ninjaDirection, xx, yy, w, h);
	//RenderBoundingBox();
}

void WindmillStar::collisionEnemies(vector<LPGAMEOBJECT> *enemies)
{
	for (int i = 0; i < enemies->size(); i++)
	{
		if (this->checkAABB(enemies->at(i)))
		{
			if (enemies->at(i)->GetIsContainer()== false)
			{
				if (AllowSound)
				Sound::GetInstance()->Play(chemtrungquai);

				int frame = 0; //animation nổ bình thường
							   //vị trí nổ = vị trí quái bị chém chết
				float xExplode = enemies->at(i)->GetPosition().x;
				float yExplode = enemies->at(i)->GetPosition().y;
				//nếu không đang nổ và quái là boss
				if (Explosion::GetInstance()->getExploding() == false && enemies->at(i)->GetType() == BOSS)
				{
					//xê dịch vụ nổ cho vừa với boss (chính giữa boss)
					xExplode += 115;
					yExplode += 60;
					enemies->at(i)->DecreaseHP(1); //trừ HP
				}
				//nếu chém chết boss
				if (enemies->at(i)->GetType() == BOSS && enemies->at(i)->getHP() == 0)
				{
					if (AllowSound)
					Sound::GetInstance()->Play(bossdie);
					frame = 1;//animation nổ cho boss
				}
				Explosion::GetInstance()->SetExplosion(xExplode, yExplode, frame);
				Ninja::GetInstance()->IncreaseScore(100); //chém trúng quái, tăng điểm ninja thêm 100

			}
			else
				enemies->at(i)->die = true;//chém trúng container

			enemies->at(i)->SetActive(0);//tắt active quái=chết
		}

	}
}

WindmillStar::~WindmillStar()
{
}