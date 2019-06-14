#include "Container.h"

Container::Container(int id, int type, int x, int y, int direction, int itemtype)
{
	this->createdItem = 0;
	this->IsContainer = true;
	this->id = id;
	this->type = (Type)type;
	this->position = D3DXVECTOR3(x, y, 0);
	this->direction = direction;
	this->itemtype = (EItem)itemtype;
	this->initdirection = direction;
	this->initposition = position;
}

void Container::SetActive(int x)
{
	{
		GameObject::SetActive(x);
		if (this->die && createdItem == 0)
		{
			item = new Item(itemtype, position.x, position.y);
			Items::GetInstance()->AddItem(item);
			createdItem = 1;
		}
	}
}

Container::~Container()
{
}