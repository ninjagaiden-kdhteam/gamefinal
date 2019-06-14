#include "Items.h"

Items* Items::__Instance = NULL;

Items::Items()
{
	
}
Items* Items::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Items();

	return __Instance;
}

void Items::AddItem(Item* item)
{
	items.push_back(item);
}
vector<Item*> Items::GetAllItems()
{
	vector<Item*> newitems;
	newitems.clear();
	for (auto x : items)
		if (x->GetActive() == 1)//item chưa bị biến mất thì mới lấy
			newitems.push_back(x);
	return newitems;
}

void Items::Clear()
{
	items.clear();
}

Items::~Items()
{

}