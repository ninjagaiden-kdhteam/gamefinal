#include "ThrowingStar.h"

ThrowingStar::ThrowingStar()
{
	this->type = THROWINGSTAR;
	this->AddAnimation(150);
	vx = WALKING_SPEED;
	vy = 0;
	this->IsActive = 0;
	//vị trí khởi tạo khi chưa được ném
	position.x = -1;
	position.y = -1;
}

void ThrowingStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	position.x += dx;
	position.y += dy;
}

void ThrowingStar::Render(float xNinja, float yNinja, int ninjaAni, int ninjaDirection, int ninjaFrame,DWORD dt)
{
	int frameLienTuc = 0;
	//nếu mới được ném ra
	if (position.x == -1)
	{
		//vị trí theo vị trí ninja hiện tại
		position.x = xNinja + 15;
		position.y = yNinja - 8;
		if(ninjaDirection>0) vx = 0.15f;
		else vx = -0.15f;
	}
	this->Update(dt); //update vị trí
	//nếu ngoài camera thì biến mất
	if (!this->IsInCamera())
	{
		position.x = -1;
		position.y = -1;
		this->IsActive = 0;
		Ninja::GetInstance()->setCreateStar(0);
	}
	this->animations[THROWINGSTAR_ANI]->Render(position.x, position.y, frameLienTuc, ninjaDirection, xx, yy, w, h);
	//RenderBoundingBox();
}

void ThrowingStar::collisionEnemies(vector<LPGAMEOBJECT> *enemies)
{
	for (int i = 0; i < enemies->size(); i++)
	{
		if (this->checkAABB(enemies->at(i)))
		{
			if (enemies->at(i)->GetIsContainer() == false)
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

void ThrowingStar::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;
	r = l + THROWINGSTAR_W;
	b = t + THROWINGSTAR_H;
}

ThrowingStar::~ThrowingStar()
{

}