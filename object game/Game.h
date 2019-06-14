#pragma once
#include "StageManager.h"
#include "GameDefinitions.h"
#include "Input.h"



class Game
{
private:
	static Game * __instance;
	Textures * textures;
	Sprites * sprites;
	Animations * animations;
	StageManager *stageManager;
	Input* input;
public:
	static Game * GetInstance();
	void Initialize(HWND, int, int);
	void LoadResources();
	void Run();
	void Update(DWORD dt);
	void Render();
	~Game();
};

