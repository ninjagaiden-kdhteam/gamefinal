#ifndef __EAGGLE_H__
#define __EAGGLE_H__
#include "Container.h"

class Eaggle :public Container
{
public:
	Eaggle(int id, int type, int x, int y, int direction, int itemtype);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	~Eaggle();
};
#endif // !__EAGGLE_H__

