#pragma once
#include "Weapon.h"
#include "Explosion.h"
#include "Ninja.h"

class Ninja;
class Explosion;
class ThrowingStar :public Weapon
{

public:
	ThrowingStar();
	~ThrowingStar();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(float xNinja, float yNinja, int ninjaAni, int ninjaDirection, int ninjaFrame,DWORD dt);
	void collisionEnemies(vector<LPGAMEOBJECT> *enemies);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};



