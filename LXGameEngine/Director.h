#ifndef DIRECTOR_H
#define DIRECOTR_H

class Director
{
public:
	static Director* getInstance();

	Director();
	~Director();

	bool mainLoop();
	bool start();
	
};

#endif
