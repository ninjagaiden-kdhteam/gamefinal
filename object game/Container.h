#pragma once
#include "GameObject.h"
#include "Items.h"


class Container :public GameObject
{
protected:
	EItem itemtype;
	Item* item;
	int createdItem;
public:
	Container(int id, int type, int x, int y, int direction, int itemtype);
	void SetActive(int x);//set active khi container bị chém
	~Container();
};