#pragma once
#include "Enemy.h"
class Dog :
	public Enemy
{
public:
	Dog(int id, int type, int x, int y, int direction, int leftX, int rightX, int distance);
	~Dog();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};

