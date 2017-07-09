#include "Ref.h"
#include "stdafx.h"
#include "AutoReleasePool.h"


Ref::Ref() :
_refCount(1)
{

}


Ref::~Ref()
{
}

void Ref::release()
{
	--_refCount;
	if (_refCount == 0)
	{
		delete this;
	}
}

void Ref::autoRelease()
{
	AutoReleasePool::getInstance()->addObject(this);
}
;
