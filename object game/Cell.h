#ifndef __CELL_H__
#define __CELL_H__
#include <map>
#include <vector>
#include "GameObject.h"


using namespace std;

class Cell
{
	int id;
	map<int, LPGAMEOBJECT> listObj;
public:
	Cell();
	Cell(int id);
	void AddObject(int id, LPGAMEOBJECT value);
	map<int, LPGAMEOBJECT> GetListObject();
	void Remove(int id);
	~Cell();
};
typedef Cell* LPCELL;
#endif // !__CELL_H__