#pragma once
#include "Weapon.h"
class Knife :public Weapon
{
public:
	void Render(float x, float y,int direction,DWORD dt);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	Knife();
	~Knife();
};

