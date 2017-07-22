#ifndef SPRITE_H
#define SPRITE_H

#include "Node.h"
#include "PolygonInfo.h"

class Sprite : public Node
{
public:
	Sprite();
	virtual ~Sprite();
	//virtual void draw() override;
	//virtual void fillPolygonInfo();
private:
	V3F_C4B_T2F _lb;
	V3F_C4B_T2F _lt;
	V3F_C4B_T2F _rb;
	V3F_C4B_T2F _rt;
	PolygonInfo _polyInfo;
};

#endif

