#include "Sword.h"
#include "debug.h"

Sword::Sword()
{
	this->type = SWORD;
	this->AddAnimation(90);
}

Sword::Sword(float x, float y, int direction)
{
	this->type = SWORD;
	this->AddAnimation(90);
	this->direction = direction;
	position = D3DXVECTOR3(x, y, 0);
}

void Sword::SetPositionSword(float xNinja, float yNinja, int ninjaAni, int ninjaDirection, int ninjaFrame)
{
	//set vị trí kiếm dựa vào trạng thái đánh+vị trí+hướng của ninja
	switch (ninjaAni)
	{
	case NINJA_ANI_STAND_HIT:
		if (ninjaDirection > 0)
		{
			switch (ninjaFrame)
			{
			case 0:
				position.x = xNinja + 20;
				position.y = yNinja - 6;
				break;
			case 1:
				position.x = xNinja + 20;
				position.y = yNinja - 6;
				break;
			case 2:
				position.x = xNinja + 21;
				position.y = yNinja - 3;
				break;
			default:
				position.x = xNinja + 20;
				position.y = yNinja - 6;
				break;
			}
		}
		else
		{
			switch (ninjaFrame)
			{
			case 0:
				position.x = xNinja - 22;
				position.y = yNinja - 7;
				break;
			case 1:
				position.x = xNinja -22;
				position.y = yNinja - 7;
				break;
			case 2:
				position.x = xNinja -12;
				position.y = yNinja - 4;
				break;
			default:
				position.x = xNinja - 22;
				position.y = yNinja - 7;
				break;
			}
		}
		break;
	case NINJA_ANI_SIT_HIT:
		if (ninjaDirection > 0)
		{
			switch (ninjaFrame)
			{
			case 0:
				position.x = xNinja + 20;
				position.y = yNinja - 12;
				break;
			case 1:
				position.x = xNinja + 20;
				position.y = yNinja - 12;
				break;
			case 2:
				position.x = xNinja + 21;
				position.y = yNinja - 9;
				break;
			default:
				position.x = xNinja + 20;
				position.y = yNinja - 12;
				break;
			}
		}
		else
		{
			switch (ninjaFrame)
			{
			case 0:
				position.x = xNinja - 22;
				position.y = yNinja - 12;
				break;
			case 1:
				position.x = xNinja - 22;
				position.y = yNinja - 12;
				break;
			case 2:
				position.x = xNinja - 12;
				position.y = yNinja - 9;
				break;
			default:
				position.x = xNinja - 22;
				position.y = yNinja - 12;
				break;
			}
		}
		break;
	default:
		position.x = xNinja;
		position.y = yNinja;
		break;
	}
	
	this->direction = ninjaDirection;
}

void Sword::Render(float xNinja, float yNinja, int ninjaAni, int ninjaDirection, int ninjaFrame)
{

	int frameLienTuc = 0;
	animations[SWORD_ANI]->Render(position.x, position.y, frameLienTuc, direction, xx, yy, w, h, -1,false,ninjaFrame,false);
	
	//RenderBoundingBox();
}

void Sword::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y-3;
	r = l + SWORD_W;
	b = t + SWORD_H;
}

void Sword::collisionEnemies(vector<LPGAMEOBJECT> *enemies)
{
	for (int i = 0; i < enemies->size(); i++)
	{
		if (this->checkAABB(enemies->at(i)))
		{
			if (enemies->at(i)->GetIsContainer() == false) //nếu là quái
			{
				if(AllowSound)
				Sound::GetInstance()->Play(chemtrungquai);

				int frame = 0; 
				//vị trí nổ = vị trí quái bị chém chết
				float xExplode = enemies->at(i)->GetPosition().x;
				float yExplode = enemies->at(i)->GetPosition().y;
				//nếu không đang nổ và quái là boss
				if (Explosion::GetInstance()->getExploding()==false &&  enemies->at(i)->GetType() == BOSS)
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
				Explosion::GetInstance()->SetExplosion(xExplode, yExplode,frame);
				Ninja::GetInstance()->IncreaseScore(100); //chém trúng quái, tăng điểm ninja thêm 100
			}
			else
			{
				//là container
				enemies->at(i)->die = true;
			}	

			enemies->at(i)->SetActive(0);//tắt active=chết
		}
			
	}
}


void Sword::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

Sword::~Sword()
{
}