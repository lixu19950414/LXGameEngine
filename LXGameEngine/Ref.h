#ifndef REF_H
#define REF_H

class Ref
{
public:
	Ref();
	virtual ~Ref();
	inline void retain() { ++_refCount; };
	void release();
	void autoRelease();
	inline int getReferenceCount() { return _refCount; };

private:
	int _refCount;
};

#endif

