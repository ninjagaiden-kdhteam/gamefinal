#pragma once
#include "GameObject.h"
#include "Items.h"

//container là đối tượng chứa các item
class Container :public GameObject
{
protected:
	EItem itemtype;//loại item mà container chứa
	Item* item;//item sẽ tạo khi container bị chém
	int createdItem;//đã tạo item hay chưa
public:
	Container(int id, int type, int x, int y, int direction, int itemtype);
	void SetActive(int x);//set active khi container bị chém
	~Container();
};