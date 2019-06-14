#ifndef __ITEMS_H__
#define __ITEMS_H__
#include "Item.h"

//class này để lưu danh sách các item đã xuất hiện
class Items
{
private:
	Items();
	vector<Item*> items;//danh sách item
public:
	static Items* __Instance;
	static Items* GetInstance();
	void AddItem(Item* item);
	vector<Item*> GetAllItems();
	void Clear();//xóa items
	~Items();
};
#endif // !__ITEMS_H__

