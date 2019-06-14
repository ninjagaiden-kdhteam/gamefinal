#include "Time.h"
Time* Time::__Instance=NULL;
Time* Time::GetInstance()
{
	if (__Instance == NULL)__Instance = new Time();
	return __Instance;
}
Time::Time()
{
	time = 150;
	timetroiqua = 0;
	IsPause = false;
}
Time::~Time()
{

}
void Time::Pause()
{
	IsPause = true;
}
void Time::UnPause()
{
	IsPause = false;
}
void Time::Update(DWORD dt)
{
	if (!IsPause) timetroiqua += dt;
	if (timetroiqua >= 1000)
	{
		timetroiqua = 0;
		time--;
		if (time <= 0) time = 0;
	}
	if (time <= 10 && time > 0 && AllowSound)
		Sound::GetInstance()->Play(hetgio);
}
void Time::Reset()
{
	time = 150;
}
int Time::GetTime()
{
	return this->time;
}