#ifndef __ITEMS_H__
#define __ITEMS_H__
#include "Item.h"


class Items
{
private:
	Items();
	vector<Item*> items;
public:
	static Items* __Instance;
	static Items* GetInstance();
	void AddItem(Item* item);
	vector<Item*> GetAllItems();
	void Clear();
	~Items();
};
#endif // !__ITEMS_H__

