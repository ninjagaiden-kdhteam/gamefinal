#pragma once
#include "GameObject.h"
#include "Bullet.h"
#define BOSS_W 34
#define BOSS_H 48
#define TIME_STOP 800
class Boss : public GameObject
{
	DWORD start_stopping;
	int isStopping;
	int atLeft;
	int atRight;
	vector<Bullet *> bullets;
	int countShoot;
public:
	Boss();
	~Boss();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void startStopping();
	void deleteBullet()
	{
		bullets.clear();
	/*	for (int i = 0; i < bullets.size(); i++)
			delete bullets[i];*/
	}
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetActive(int x)
	{
		IsActive = x;
		if (x == 0)
		{
			//direction = initdirection;
		}
	}
	void updateBullet(DWORD dt);
	vector<Bullet*> getBullets()
	{
		vector<Bullet*> list;
		list.clear();
		for (int i = 0; i < bullets.size(); i++)
			if (bullets[i]->GetActive() == 1)
				list.push_back(bullets[i]);
		return list;
	}
};