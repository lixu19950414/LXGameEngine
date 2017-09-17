#ifndef LABEL_H
#define LABEL_H

#include "Node.h"
#include "LabelSprite.h"
#include <string>
#include <vector>

class Label :
	public Node
{
public:
	Label();
	virtual ~Label();
	bool initWithFont(const std::string& fontName, int fontSize, const std::string& s);
	void visit(glm::mat4& parentTransform) override;
	void setContentSize(GLfloat width, GLfloat height) override;
	void setAnchorPoint(GLfloat x, GLfloat y) override;

	void setOpacity(GLubyte opacity) override;
	void setColor(GLubyte r, GLubyte g, GLubyte b);
	void setOutlineColor(GLubyte r, GLubyte g, GLubyte b);

	void setString(const std::string& s);
	void setFontName(const std::string& s);
	void setFontSize(int fontSize);
	void setOutlineSize(int outlineSize);

	inline const std::string& getString() {return _currentString; };
private:
	void setupSprites();
	void createSprites();
	void refreshSpritesPos();
	
	void releaseCurrentSprites();

	int _fontSize;
	int _fontOutlineSize;
	bool _needRecreateSprites;
	bool _needRefreshSpritesPos;
	GLubyte _fontOpacity;
	GLubyte _fontColor[3];
	GLubyte _fontOutlineColor[3];
	std::string _currentString;
	std::string _fontName;
	std::vector<LabelSprite*> _sprites;
	std::vector<LabelSprite*> _outlineSprites;
};

#endif
