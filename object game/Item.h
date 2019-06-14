#ifndef __ITEM_H__
#define __ITEM_H__

#define TIME_DISPLAY 2500
#include "GameObject.h"
class Item :public GameObject
{
protected:
	EItem itemtype;//loại item
	int timeDisplayed;//thời gian đã tồn tại, >2500 thì bị biến mất
public:
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);//xử lý đụng độ gạch
	Item(int itemtype,float x,float y);//x,  y vị trí được tạo ra, lấy luôn vị trí container
	void GetBoundingBox(float & l, float & t, float & r, float & b);
	void setDie();//set một số thông số cho item để item biến mất
	EItem getItemType() { return itemtype; }
	~Item();
};
#endif // !__ITEM_H__

