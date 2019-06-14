#ifndef __SWORD_H__
#define __SWORD_H__
#include "Weapon.h"
#include "Explosion.h"
#include "Ninja.h"

class Ninja;

class Sword :public Weapon
{
public:
	Sword();
	Sword(float x, float y, int direction);
	void Render(float xNinja, float yNinja, int ninjaAni, int ninjaDirection, int ninjaFrame);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetPositionSword(float xNinja, float yNinja, int ninjaAni,int ninjaDirection,int ninjaFrame);
	void collisionEnemies(vector<LPGAMEOBJECT> *enemies);
	~Sword();
};
#endif // !__SWORD_H__