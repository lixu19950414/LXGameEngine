#ifndef POLYGONINFO_H
#define POLYGONINFO_H


struct V3F_C4B_T2F {
	V3F_C4B_T2F();
	bool setVertices(GLfloat x, GLfloat y, GLfloat z);
	bool setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	GLubyte* getColor();
	bool setUV(GLfloat u, GLfloat v);
	GLfloat _vertices[3];
	GLubyte _color[4];
	GLfloat _uv[2];
};

class PolygonInfo
{
public:
	PolygonInfo();
	~PolygonInfo();
	void clear();
	inline void pushVert(V3F_C4B_T2F vert) { _verts.push_back(vert); };
	inline void pushIndices(GLint index) { _indices.push_back(index); };
	inline int getVertsCount() { return _verts.size(); };
	inline int getIndicesCount() { return _indices.size(); };
	inline GLvoid* getVerts() { return &_verts[0]; };
	inline GLvoid* getIndices() { return &_indices[0]; };
private:
	std::vector<V3F_C4B_T2F> _verts;
	std::vector<GLuint> _indices;
};

#endif