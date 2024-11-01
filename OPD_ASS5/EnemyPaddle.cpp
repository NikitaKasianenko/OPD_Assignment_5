#include "EnemyPaddle.h"
#include "Game.h"

EnemyPaddle::EnemyPaddle(Game* g, float s) : game(g), speed(s) {
	direction.x = 0.f;
	direction.y = 0.f;
}

void EnemyPaddle::move_paddle(int param, int dir)
{
	if (param == 0) {

		if (game->getBallPositoin().x >= game->getVideoMode().width / 5.f) {
			int kef = game->getFullscrenMode() ? 5 : 10;
			

			sf::Vector2f ballPos = game->getBallPositoin();
			sf::Vector2f ballDir = game->getBallDirection();
			float EnemyCenter = paddle_shape.getPosition().y + paddle_shape.getSize().y / 2.f;
			float ballXPercent = (100.0f - (ballPos.x / game->getVideoMode().width) * 90.0f) / kef;

			if (ballXPercent < 1) {
				ballXPercent = 1;
			}

			std::cout << ballXPercent << std::endl;
			float futurePos = ballPos.y + ballDir.y * game->getBallSize().x * ballXPercent  / game->getBallDirection().x;;

			if (futurePos < 0 ) {
				futurePos = -futurePos * ballXPercent;
			}
			if (futurePos > game->getVideoMode().height) {
				futurePos = futurePos / ballXPercent;
			}
			game->setBallPos(game->getBallPositoin().x, futurePos);
			
			float moveTo = futurePos - EnemyCenter;
			if (std::abs(moveTo) > 25.f) {
				if (moveTo < 0) {
					direction.y = -speed;

				}
				else {
					direction.y = speed;
				}
			}
			else {
				direction.y = 0.f;
			}
		}
		else {
			direction.y = 0.f;
		}

		if (paddle_shape.getPosition().y + paddle_shape.getSize().y + direction.y < game->getVideoMode().height && paddle_shape.getPosition().y  + direction.y> 0.f) {
			paddle_shape.move(0.f, direction.y);

		}
	}
	if (param == 1) {

		if (dir == 0) { // Move down
			if (paddle_shape.getPosition().y + paddle_shape.getSize().y < game->getVideoMode().height) {
				paddle_shape.move(0.f, speed);
			}
		}

		if (dir == 1) { // Move up
			if (paddle_shape.getPosition().y > 0.f) {
				paddle_shape.move(0.f, -speed);
			}
		}
	}

}

void EnemyPaddle::setSpeed(float s)
{
	speed = s;
}
