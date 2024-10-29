#include "Game.h"
#include "PlayerPaddle.h"
#include "EnemyPaddle.h"
#include "Ball.h"



void Game::initVariables()
{

	if (this->fps == 60) {
		this->paddleSpeed = 4.8f;
		this->ballSpeed = 7.2f;
		this->resetBallSpeedX = 4.8f;
		this->resetBallSpeedY = 2.4f;


	}
	else if (this->fps == 144) {
		this->paddleSpeed = 2.f;
		this->ballSpeed = 3.f;
		this->resetBallSpeedX = 2.f;
		this->resetBallSpeedY = 1.f;

	}


	if (!this->enemyPaddle) {
		this->enemyPaddle = new EnemyPaddle(this, paddleSpeed);
	
	}
	this->enemyPaddle->direction.x = 0;
	this->enemyPaddle->direction.y = 0;


	if (!this->playerPaddle) {
		this->playerPaddle = new PlayerPaddle(this, paddleSpeed);

	}


	if (!this->ball) {
		this->ball = new Ball(this);
	}

	this->ball->direction.x = 0.f;
	this->ball->direction.y = 0.f;


	this->lastTouch = true;

	playerPaddle->setSpeed(paddleSpeed);
	enemyPaddle->setSpeed(paddleSpeed);
}

void Game::InitWindow()
{

	if (this->window) {
		delete this->window;
	}
	

	if (!fullscreen) {
		this->videoMode.height = 728;
		this->videoMode.width = 1024;
	}

	if (fullscreen) {
		this->videoMode = videoMode.getDesktopMode();
	}

	

	this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(fps);
}

void Game::InitEnemies()

{
	this->enemyPaddle->paddle_shape.setSize(sf::Vector2f(50.f, 150.f));
	this->enemyPaddle->paddle_shape.setPosition(videoMode.width- enemyPaddle->paddle_shape.getSize().x, (videoMode.height/2.f- enemyPaddle->paddle_shape.getSize().y/2.f));
	this->enemyPaddle->paddle_shape.setFillColor(sf::Color::Cyan);
	this->enemyPaddle->paddle_shape.setOutlineColor(sf::Color::Green);
	this->enemyPaddle->paddle_shape.setOutlineThickness(1.f);

}

void Game::InitPaddle()
{
	this->playerPaddle->paddle_shape.setPosition(0.f, (videoMode.height / 2.f - enemyPaddle->paddle_shape.getSize().y/ 2.f));
	this->playerPaddle->paddle_shape.setSize(sf::Vector2f(50.f, 150.f));
	this->playerPaddle->paddle_shape.setFillColor(sf::Color::Cyan);
	this->playerPaddle->paddle_shape.setOutlineColor(sf::Color::Green);
	this->playerPaddle->paddle_shape.setOutlineThickness(1.f);
}

void Game::InitBall()
{
	this->ball->shape.setSize(sf::Vector2f(35.f, 35.f));
	this->ball->shape.setPosition(playerPaddle->paddle_shape.getPosition().x + playerPaddle->paddle_shape.getSize().x + 20.f, playerPaddle->paddle_shape.getPosition().y - ball->shape.getSize().x / 2.f + playerPaddle->paddle_shape.getSize().y / 2.f);
	this->ball->shape.setFillColor(sf::Color::Cyan);
	this->ball->shape.setOutlineColor(sf::Color::Green);
	this->ball->shape.setOutlineThickness(1.f);




}

void Game::InitScore()
{	
	if (!font.loadFromFile("arial.ttf")) {
		// Handle error
	}
	score[0].setFont(font);
	score[0].setFillColor(sf::Color::Green);
	score[0].setString("0");
	score[0].setPosition(sf::Vector2f(videoMode.width / 4, videoMode.height / 10));

	score[1].setFont(font);
	score[1].setFillColor(sf::Color::Green);
	score[1].setString("0");
	score[1].setPosition(sf::Vector2f(videoMode.width *3 / 4, videoMode.height / 10));
}

void Game::InitMenu()
{
	delete this->Menu;
	this->Menu = new MainMenu(window->getSize().x, window->getSize().y);

}

//constructor / deconstructor
Game::Game()
{
	this->initVariables();
	this->InitWindow();
	this->InitMenu();
	this->InitEnemies();
	this->InitPaddle();
	this->InitBall();
	this->InitScore();
}

Game::~Game()
{
	delete this->window;
	delete this->enemyPaddle;
	delete this->playerPaddle;
	delete this->ball;
}

//accessors

const bool Game::running() const
{
	return this->window->isOpen();
}

sf::VideoMode Game::getVideoMode()
{
	return videoMode;
}

sf::Vector2f Game::getBallPositoin()
{
	return ball->shape.getPosition();
}

sf::Vector2f Game::getBallSize()
{
	return ball->shape.getSize();
}

sf::Vector2f Game::getBallDirection()
{
	return sf::Vector2f(ball->direction.x,ball->direction.y);
}

sf::RenderWindow& Game::getWindow()
{
	return *window;
}


//functions

void Game::checkCollision()
{

	if (ball->shape.getGlobalBounds().intersects(enemyPaddle->paddle_shape.getGlobalBounds()) && lastTouch) {
		//ballSpeed *= 1.002f;
		float paddleCentre = enemyPaddle->paddle_shape.getPosition().y + enemyPaddle->paddle_shape.getSize().y / 2.f;
		float ballCentre = ball->shape.getPosition().y + ball->shape.getSize().y / 2.f;

		float diff = ballCentre - paddleCentre;
		diff = (diff / (playerPaddle->paddle_shape.getSize().y / 2.f));
		ball->direction.x = -ballSpeed;
		ball->direction.y = -diff * (ball->direction.x);
		lastTouch = false;

	}

	if (ball->shape.getGlobalBounds().intersects(playerPaddle->paddle_shape.getGlobalBounds()) && !lastTouch) {
		//ballSpeed *= 1.002f;
		float paddleCentre = playerPaddle->paddle_shape.getPosition().y + playerPaddle->paddle_shape.getSize().y / 2.f;
		float ballCentre = ball->shape.getPosition().y + ball->shape.getSize().y / 2.f;

		float diff = ballCentre - paddleCentre;
		diff = (diff / (playerPaddle->paddle_shape.getSize().y / 2.f));
		ball->direction.x = ballSpeed;
		ball->direction.y = diff * (ball->direction.x);
		lastTouch = true;
	}

	if (ball->shape.getPosition().y <= 0 || ball->shape.getPosition().y + ball->shape.getSize().y >= videoMode.height) {
		ball->direction.y = -ball->direction.y;

	}

	/*if (ball.getPosition().x < -100) {
		resetBall(0);
	}*/



}

void Game::win()
{
	if (ball->shape.getPosition().x < -5) {
		points.y++;  // Enemy player score
		std::cout << "Points: " << points.x << " : " << points.y << std::endl;
		if (points.y == 5) {
			
		}
		resetBall(1);
	}
	if (ball->shape.getPosition().x > videoMode.width + 5) {
		points.x++;  // Player score
		std::cout << "Points: " << points.x << " : " << points.y << std::endl;
		resetBall(0);
	}


}


void Game::resetBall(int param)
{
	if (param == 1) {
		ball->shape.setPosition(videoMode.width / 2.f, 10.f);
		ball->direction.x = -resetBallSpeedX;
		ball-> direction.y = -resetBallSpeedY;
	}

	if (param == 0) {
		ball->shape.setPosition(videoMode.width / 2.f, 10.f);
		ball->direction.x = resetBallSpeedX;
		ball->direction.y = resetBallSpeedY;
	}
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::KeyPressed:
                switch (this->ev.key.code) {
                    case sf::Keyboard::W:
                        Menu->MoveUp();
                        break;
                    case sf::Keyboard::S:
                        Menu->MoveDown();
                        break;
                    case sf::Keyboard::Return:
						mainMenu();
                        break;
                    case sf::Keyboard::Escape:
                        window->close();
                        break;
                }
                break;
            case sf::Event::Closed:
                window->close();
                break;
        }
    }
}

void Game::mainMenu()
{
	switch (Menu->getPressedItem()) {
	case 0:
		std::cout << "Play button has been pressed" << std::endl;
		play = true;
		break;
	case 1:
		Menu->togglePlayer();
		twoPlayers = !twoPlayers;
		break;
	case 2:
		Menu->cycleFPS();
		fps = (Menu->getFPSSetting() == 0 ? 60 : 144);
		InitWindow();
		initVariables();
		break;
	case 3:
		Menu->toggleFullscreen();
		fullscreen = Menu->isFullscreen();
		InitWindow();
		InitPaddle();
		InitBall();
		InitEnemies();
		InitScore();
		Menu->updateMenu(videoMode.width, videoMode.height);
		break;
	case 4:
		window->close();
		break;
	}
}




void Game::updateEnemies()
{
	if (!twoPlayers) {
		enemyPaddle->move_paddle(0,0);

	}
}

void Game::updatePaddle()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerPaddle->move_paddle(0);
		if (!start) {
			ball->direction.x = ballSpeed;
		}
		start = true;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		playerPaddle->move_paddle(1);
		if (!start) {
			ball->direction.x = ballSpeed;
		}
		start = true;

	}

	if (twoPlayers) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			enemyPaddle->move_paddle(1,1);
			if (!start) {
				ball->direction.x = ballSpeed;
			}
			start = true;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			enemyPaddle->move_paddle(1,0);
			if (!start) {
				ball->direction.x = ballSpeed;
			}
			start = true;
		}

	}

}

void Game::updateBall()
{
	ball->move();
	checkCollision();

}

void Game::updateScore()
{
	score[0].setString(std::to_string(points.x));
	score[1].setString(std::to_string(points.y));
}


void Game::update()
{
	this->pollEvents();
	if (play) {
		this->updateEnemies();
		this->updateBall();
		this->updatePaddle();
		this->updateScore();
		this->win();
	}
		


}

void Game::render()
{
	// clear old frame
	// render objects
	//display frame in window
	// renders the game objects


	// clear old frame

	this->window->clear();

	//draw game objects
	if (play) {
		this->renderEnemies();
		this->window->draw(playerPaddle->paddle_shape);
		this->window->draw(ball->shape);
		for (auto& h: score) {
			this->window->draw(h);
		}
	}

	//display new frame

	if (!play) {
		Menu->draw(*window);
	}

	this->window->display();
}

void Game::renderEnemies()
{
		this->window->draw(enemyPaddle->paddle_shape);

}


