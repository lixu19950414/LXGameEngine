#include "stdafx.h"
#include "Scheduler.h"


Scheduler* g_pScheduler = nullptr;

Scheduler::Scheduler()
{
}

Scheduler * Scheduler::getInstance()
{
	if (g_pScheduler == nullptr) {
		g_pScheduler = new (std::nothrow) Scheduler();
	}
	return g_pScheduler;
}

void Scheduler::update(float deltaTime)
{
	std::vector<Timer*> excutes;
	auto it = _timersWithPriorityLessThanZero.begin();
	while (it != _timersWithPriorityLessThanZero.end()) {
		if ((*it)->getIsActive() && (*it)->getReferenceCount() != 1) {
			assert((*it)->getReferenceCount() > 1);
			excutes.push_back(*it);
			++it;
		}
		else {
			(*it)->release();
			it = _timersWithPriorityLessThanZero.erase(it);
		}
	}

	it = _timersWithPriorityZero.begin();
	while (it != _timersWithPriorityZero.end()) {
		if ((*it)->getIsActive() && (*it)->getReferenceCount() != 1) {
			assert((*it)->getReferenceCount() > 1);
			excutes.push_back(*it);
			++it;
		}
		else {
			(*it)->release();
			it = _timersWithPriorityZero.erase(it);
		}
	}
	
	it = _timersWithPriorityGreaterThanZero.begin();
	while (it != _timersWithPriorityGreaterThanZero.end()) {
		if ((*it)->getIsActive() && (*it)->getReferenceCount() != 1) {
			assert((*it)->getReferenceCount() > 1);
			excutes.push_back(*it);
			++it;
		}
		else {
			(*it)->release();
			it = _timersWithPriorityGreaterThanZero.erase(it);
		}
	}

	for (auto it : excutes) {
		it->update(deltaTime);
	}
}

void Scheduler::addTimerToSchedule(Timer * timer)
{
	assert(timer->getReferenceCount() == 1);
	timer->retain();
	int priority = timer->getPriority();
	if (priority == 0) {
		_timersWithPriorityZero.push_back(timer);
	}
	else if(priority > 0) {
		_timersWithPriorityGreaterThanZero.push_back(timer);
	}
	else {
		_timersWithPriorityLessThanZero.push_back(timer);
	}
}


Scheduler::~Scheduler()
{
	auto lessThanZero = getTimersWithPriorityLessThanZero();
	for (auto it = lessThanZero.begin(); it != lessThanZero.end(); ++it) {
		(*it)->release();
		it = lessThanZero.erase(it);
	}

	auto equalZero = getTimersWithPriorityZero();
	for (auto it = equalZero.begin(); it != equalZero.end(); ++it) {
		(*it)->release();
		it = equalZero.erase(it);
	}

	auto greaterThanZero = getTimersWithPriorityGreaterThanZero();
	for (auto it = greaterThanZero.begin(); it != greaterThanZero.end(); ++it) {
		(*it)->release();
		it = greaterThanZero.erase(it);
	}
}
