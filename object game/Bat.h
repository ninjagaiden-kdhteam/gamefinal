#pragma once
#include "Enemy.h"
#include "Ninja.h"
class Bat :public Enemy
{
public:
	Bat(int id, int type, int x, int y, int direction,int leftX,int rightX,int distance);
	~Bat();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects=NULL);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};
