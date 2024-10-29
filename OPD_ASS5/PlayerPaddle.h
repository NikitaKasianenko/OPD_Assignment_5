#pragma once
#include "SFML/Graphics.hpp"

class Game;

class PlayerPaddle
{
private:
	Game* game;
public:
	PlayerPaddle(Game* g,float s);
	float speed;
	sf::RectangleShape paddle_shape;
	void move_paddle(int param);
	void setSpeed(float s);
	
};

