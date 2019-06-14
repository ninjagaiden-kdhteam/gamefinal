#pragma once
#ifndef _LINH_H_
#define _LINH_H_
#include "Enemy.h"
class SoldierYellow :public Enemy
{
public:
	SoldierYellow(int id, int type, int x, int y, int direction, int leftX, int rightX,int distance);
	~SoldierYellow();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};
#endif // !_LINH_H_
