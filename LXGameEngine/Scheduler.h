#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Timer.h"

class Scheduler
{
public:
	Scheduler();
	static Scheduler* getInstance();
	~Scheduler();

	void update(float deltaTime);
	std::vector<Timer*>& getTimersWithPriorityZero() { return _timersWithPriorityZero; };
	std::vector<Timer*>& getTimersWithPriorityGreaterThanZero() { return _timersWithPriorityGreaterThanZero; };
	std::vector<Timer*>& getTimersWithPriorityLessThanZero() { return _timersWithPriorityLessThanZero; };
	void addTimerToSchedule(Timer* timer);

private:
	std::vector<Timer*> _timersWithPriorityZero;
	std::vector<Timer*> _timersWithPriorityGreaterThanZero;
	std::vector<Timer*> _timersWithPriorityLessThanZero;
};

#endif

