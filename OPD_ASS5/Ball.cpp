#include "Ball.h"
#include "Game.h"

Ball::Ball(Game* g) : game(g)
{
}

void Ball::move()
{
	shape.move(direction.x, direction.y);
}
