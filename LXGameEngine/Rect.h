#ifndef RECT_H
#define RECT_H

class Rect
{
public:
	Rect();
	Rect(glm::vec2 origin, glm::vec2 size);
	Rect(GLfloat oriX, GLfloat oriY, GLfloat sizeX, GLfloat sizeY);

	inline void setOrigin(glm::vec2 origin) { _origin = origin; };
	inline void setOrigin(GLfloat oriX, GLfloat oriY) { _origin = glm::vec2(oriX, oriY); };
	inline glm::vec2 getOrigin() { return _origin; };

	inline void setSize(glm::vec2 size) { _size = size; };
	inline void setSize(GLfloat sizeX, GLfloat sizeY) { _size = glm::vec2(sizeX, sizeY); };
	inline glm::vec2 getSize() { return _size; };

	bool containPoint(glm::vec2 point);
	bool containPoint(GLfloat x, GLfloat y);

	~Rect();
private:
	glm::vec2 _origin;
	glm::vec2 _size;
};

typedef Rect AABB;

#endif
