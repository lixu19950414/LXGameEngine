#include "stdafx.h"
#include "PolygonInfo.h"


PolygonInfo::PolygonInfo()
{
}


PolygonInfo::~PolygonInfo()
{
	clear();
}

void PolygonInfo::clear()
{
	_verts.clear();
	_indices.clear();
}

V3F_C4B_T2F::V3F_C4B_T2F()
{
	memset(this, 0, sizeof(V3F_C4B_T2F));
}

bool V3F_C4B_T2F::setVertices(GLfloat x, GLfloat y, GLfloat z)
{
	_vertices[0] = x;
	_vertices[1] = y;
	_vertices[2] = z;
	return true;
}

bool V3F_C4B_T2F::setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	_color[0] = r;
	_color[1] = g;
	_color[2] = b;
	_color[3] = a;
	return true;
}

bool V3F_C4B_T2F::setUV(GLfloat u, GLfloat v)
{
	_uv[0] = u;
	_uv[1] = v;
	return true;
}
