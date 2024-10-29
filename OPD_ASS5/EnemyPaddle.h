#pragma once
#include "SFML/Graphics.hpp"

class Game;

class EnemyPaddle
{
private:
	Game* game;

public:
	EnemyPaddle(Game* g, float s);
	float speed;
	sf::RectangleShape paddle_shape;
	void move_paddle(int param,int dir);
	sf::Vector2i direction;
	void setSpeed(float s);

};




