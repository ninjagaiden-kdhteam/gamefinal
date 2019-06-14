#include "Explosion.h"
#define INIT_POS -1000
Explosion* Explosion::__Instance = NULL;

Explosion* Explosion::GetInstance()
{
	if (__Instance == NULL) __Instance = new Explosion();
	return __Instance;
}

Explosion::Explosion()
{
	exploding = false;
	this->AddAnimation(140);
	this->AddAnimation(260);
	position.x = INIT_POS;
	position.y = INIT_POS;
	direction = 1;
	ani = 0;
	time = 0;
}

void Explosion::EndExplosion()
{
	exploding = false;
	position.x = INIT_POS;
	position.y = INIT_POS;
	time = 0;
}

void Explosion::SetExplosion(float x, float y,int frame)
{
	if (exploding == true) return;
	ani = frame;
	position.x = x;
	position.y = y;
	exploding = true;
	if (frame == 1)
	{
		Sound::GetInstance()->Stop(background1);
		Sound::GetInstance()->Stop(background2);
		time = GetTickCount();
	}
}

void Explosion::Render()
{
	if (exploding == false) return;
	int isExploding = 1;//check frame cuối chưa
	if (IsTimeFreeze)
		animations[ani]->Render(position.x, position.y, isExploding, direction, xx, yy, w, h, -1, 0, -1, false);
	else
		animations[ani]->Render(position.x, position.y, isExploding, direction, xx, yy, w, h);
	if (time != 0)
	{
		if (GetTickCount() - time < TIME_EXPLOSION)
		{
			return;
		}
	}
	if (isExploding == 0 && time != 0)
	{
		Sound::GetInstance()->Stop(bossdie);
	}
	if (isExploding == 0) EndExplosion();
}