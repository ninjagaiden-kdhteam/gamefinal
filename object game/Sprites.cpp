#include "Sprites.h"
Sprites * Sprites::__instance = NULL;

Sprites * Sprites::GetInstance()
{
	if (__instance == NULL) __instance = new Sprites();
	return __instance;
}



void Sprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, float xx, float yy)
{
	LPSPRITE s = new Sprite(id, left, top, right, bottom, tex, xx, yy);
	sprites[id] = s;
}

LPSPRITE Sprites::Get(int id)
{
	return sprites[id];
}
