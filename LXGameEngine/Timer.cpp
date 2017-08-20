#include "stdafx.h"
#include "Timer.h"


int g_nTimerID = 1;

Timer::Timer(float interval, int leftTimes, std::function<void(float)> func, int priority):
	_interval(interval),
	_leftTimes(leftTimes),
	_timerFunc(func),
	_priority(priority),
	_active(true),
	_experiencedTime(0.0f)
{
	++g_nTimerID;
	_id = g_nTimerID;
}

Timer::~Timer()
{
	
}

void Timer::update(float dt)
{
	if (!_active) {
		return;
	}
	_experiencedTime += dt;
	if (_experiencedTime >= _interval) {
		_timerFunc(_experiencedTime);
		--_leftTimes;
		_experiencedTime -= _interval;
		if (_leftTimes == 0) {
			_active = false;
		}
	}
}

void Timer::dump()
{
	LX_LOG("Timer::_id: %d\n", _id);
	LX_LOG("Timer::_active: %d\n", _active);
	LX_LOG("Timer::_priority: %d\n", _priority);
	LX_LOG("Timer::_refcount: %d\n", getReferenceCount());
}
