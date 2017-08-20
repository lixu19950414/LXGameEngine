#ifndef TIMER_H
#define TIMER_H

#include "Ref.h"

class Timer:public Ref  
{
public:
	Timer(float interval, int leftTimes, std::function<void(float)> func, int priority = 0);
	~Timer();
	inline int getUniqueID() { return _id; };
	inline bool getIsActive() { return _active; };
	inline void setDead() { _active = false; };
	inline int getPriority() { return _priority; };
	inline std::function<void(float)> getTimerFunc() { return _timerFunc; };
	
	void update(float dt);

	void dump();

protected:
	int _id;
	bool _active;
	int _priority;
	std::function<void(float)> _timerFunc;
	int _leftTimes;
	float _interval;
	float _experiencedTime;
};

#endif
