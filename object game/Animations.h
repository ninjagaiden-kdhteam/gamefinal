#pragma once
#include "Animation.h"
#include <unordered_map>

using namespace std;
class Animations
{
	static Animations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Clean();

	static Animations * GetInstance();
};
