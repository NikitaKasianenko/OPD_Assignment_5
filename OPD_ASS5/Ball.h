#pragma once
#include "SFML/Graphics.hpp"

class Game;

class Ball
{
private:
	Game* game;
public:

	Ball(Game* g);
	sf::RectangleShape shape;
	sf::Vector2i direction;
	void move();

};

