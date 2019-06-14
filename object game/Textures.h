#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Graphic.h"
#include <unordered_map>

using namespace std;

class Textures
{
	static Textures * __instance;
	unordered_map<int, LPDIRECT3DTEXTURE9> textures;
public:
	Textures();
	//Thêm một texture vào cơ sở dữ liệu
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	void Clear();
	//Lấy một texture từ csdl
	LPDIRECT3DTEXTURE9 Get(unsigned int i);
	static Textures * GetInstance();
};

