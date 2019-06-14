#ifndef _SOLDIER_H
#define _SOLDIER_H
#include "Enemy.h"
#include "Bullet.h"

class SoldierGreen :public Enemy
{
	Bullet* bullet;
	float time;
	int countFrame;
public:
	Bullet* GetBullet() { return bullet; }
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	SoldierGreen(int id, int type, int x, int y, int direction, int leftX, int rightX,int distance);
	~SoldierGreen();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};
#endif