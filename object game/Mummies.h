#ifndef _MUMMIES_H
#define _MUMMIES_H
#include "Ninja.h"
#include "Knife.h"
#include "Enemy.h"

class Mummies :public Enemy
{
	float time;
	int countframe;
	Weapon *knife;
public:
	Weapon* GetWeapon() { return knife; }
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	Mummies(int id, int type, int x, int y, int direction, int leftX, int rightX, int distance);
	~Mummies();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};
#endif // !_MUMMIES_H
