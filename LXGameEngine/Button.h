#ifndef BUTTON_H
#define BUTTON_H

#include "Sprite.h"
class Button :
	public Sprite
{
public:
	Button();
	~Button();

	bool onTouchBegin(int x, int y) override;
	void onTouchMove(int x, int y) override;
	void onTouchEnd(int x, int y) override;
	inline void setCallback(std::function<void(int x, int y)> callback) { _callback = callback; };
protected:
	std::function<void(int x, int y)> _callback;
	glm::vec2 _clickPos;
};

#endif
