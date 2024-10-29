#include "PlayerPaddle.h"
#include "Game.h"

void PlayerPaddle::move_paddle(int param)
{
	if (param == 0) { // Move down
		if (paddle_shape.getPosition().y + paddle_shape.getSize().y < game->getVideoMode().height) {
			paddle_shape.move(0.f, speed);
		}
	}

	if (param == 1) { // Move up
		if (paddle_shape.getPosition().y > 0.f) {
			paddle_shape.move(0.f, -speed);
		}
	}

}

void PlayerPaddle::setSpeed(float s)
{
	speed = s;
}

PlayerPaddle::PlayerPaddle(Game* g,float s) : game(g), speed(s){}
