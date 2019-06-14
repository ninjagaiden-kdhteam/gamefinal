#ifndef __CELL_H__
#define __CELL_H__
#include <map>
#include <vector>
#include "GameObject.h"


using namespace std;

class Cell
{
	int id;
	map<int, LPGAMEOBJECT> listObj;//danh sách đối tượng nằm trong cell
public:
	Cell();
	Cell(int id);
	void AddObject(int id, LPGAMEOBJECT value);//thêm đối tượng vào cell
	map<int, LPGAMEOBJECT> GetListObject();//lấy danh sách đối tượng thuộc cell
	void Remove(int id);//xóa đối tượng khỏi cell
	~Cell();
};
typedef Cell* LPCELL;
#endif // !__CELL_H__