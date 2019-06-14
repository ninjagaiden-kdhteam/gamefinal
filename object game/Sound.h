#ifndef __SOUND_H__
#define __SOUND_H__

#include "Graphic.h"
#include "dsutil.h"
#include "GameDefinitions.h"
#include <map>



class Sound
{
private:
	map<ESound, CSound* > listSound; //lưu danh sách âm thanh

public:
	static Sound * __Instance;
	static Sound * GetInstance();


	CSoundManager *dsound;

	void Init();
	Sound();

	void AddSound(ESound type, LPTSTR filename);
	void Play(ESound type, bool isLoop = false);
	void Stop(ESound type);
	void LoadSound();

	bool isPlaying(ESound type);

	void StopAll();

};

#endif