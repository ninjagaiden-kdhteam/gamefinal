#pragma once
#include "GameObject.h"
#include "debug.h"

class Wall : public GameObject
{
	int min;
	int max;
	int canClimb;
public:
	Wall() {}
	Wall(float l, float t, float r, float b,int mi, int ma,int climb)
	{
		type =WALL;
		position.x = l;
		position.y = t;
		w = r;
		h = b;
		min = mi;
		max = ma;
		canClimb = climb;
	}
	int getMinClimb() { return min; }
	int getMaxClimb() { return max; }
	int getCanClimb() { return canClimb; }
	void Render()
	{
		//RenderBoundingBox();
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)
	{}
};