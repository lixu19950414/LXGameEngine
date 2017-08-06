#ifndef GAME_H
#define GAME_H

class Game
{
public:
	Game();
	static Game* getInstance();
	bool start();
	bool loop();
	~Game();
};

#endif

