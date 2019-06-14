#ifndef _BUTTERFLY_H_
#define _BUTTERFLY_H_
#include "Container.h"

class Butterfly :public Container
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	Butterfly(int id, int type, int x, int y, int direction, int itemtype);
	~Butterfly();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};
#endif // !_BUTTERFLY_H_

