#ifndef AUTORELEASEPOOL_H
#define AUTORELEASEPOOL_H

#include "Ref.h"
#include <vector>

class AutoReleasePool
{
public:
	static AutoReleasePool* getInstance();
	AutoReleasePool();
	~AutoReleasePool();
	void addObject(Ref* obj);
	void executeClear();
private:
	std::vector<Ref*> _objToRelease;
};

#endif

