#include "Textures.h"
Textures * Textures::__instance = NULL;

Textures::Textures()
{
}

void Textures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		OutputDebugString(L"Error");
		return;
	}

	LPDIRECT3DTEXTURE9 texture = NULL;
	Graphic * gp = Graphic::GetInstance();
	result = D3DXCreateTextureFromFileEx(
		Graphic::GetInstance()->GetDevice(),								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		return;
	}

	textures[id] = texture;

}

void Textures::Clear()
{
	textures.clear();
}

LPDIRECT3DTEXTURE9 Textures::Get(unsigned int i)
{
	return textures[i];
}

Textures * Textures::GetInstance()
{
	if (__instance == NULL) __instance = new Textures();
	return __instance;
}
