#include "Cell.h"

Cell::Cell()
{
}

Cell::Cell(int id)
{
	this->id = id;
}

void Cell::AddObject(int id, LPGAMEOBJECT value)
{
	listObj[id] = value;
}

map<int, LPGAMEOBJECT> Cell::GetListObject()
{
	return this->listObj;
}


void Cell::Remove(int id)
{
	listObj.erase(id);
}

Cell::~Cell()
{
	listObj.clear();
}