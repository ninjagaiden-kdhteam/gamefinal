#ifndef __BULLET_H__
#define __BULLET_H__
#include "GameObject.h"

class Bullet :public GameObject
{
	int ani;
public:
	Bullet();
	Bullet(float x, float y, int direction,int frameAni);
	~Bullet();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
};
#endif // !__BULLET_H__