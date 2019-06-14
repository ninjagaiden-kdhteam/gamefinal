#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Ninja.h"
class GreenSniper :public Enemy
{
	Bullet* bullet;
	float time;
	int countFrame;
public:
	Bullet* GetBullet() { return bullet; }
	GreenSniper(int id, int type, int x, int y, int direction, int leftX, int rightX, int distance);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	~GreenSniper();
};