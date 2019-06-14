#pragma once
#include "GameObject.h"
#include "debug.h"

class Brick : public GameObject
{

public:
	Brick() {}
	Brick(float l, float t, float r, float b)
	{
		type = BRICK;
		position.x = l;
		position.y = t;
		w = r;
		h = b;
	}

	void Render()
	{
		//RenderBoundingBox();
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)
	{}
};