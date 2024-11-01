#include "Game.h"
#include "PlayerPaddle.h"
#include "EnemyPaddle.h"
#include "Ball.h"



void Game::initVariables ()
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
	defaulBallSpeed = ballSpeed;
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

	

	if (!fullscreen) {
		this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);

	}
	if (fullscreen) {
		this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Fullscreen);
	}
	this->window->setFramerateLimit(fps);
}

void Game::InitEnemies()

{

	if (this->enemyPaddle) {
		delete this->enemyPaddle;
	}

	this->enemyPaddle = new EnemyPaddle(this, paddleSpeed);
	
	this->enemyPaddle->direction.x = 0;
	this->enemyPaddle->direction.y = 0;
	this->enemyPaddle->paddle_shape.setSize(sf::Vector2f(50.f, 150.f));
	this->enemyPaddle->paddle_shape.setPosition(videoMode.width- enemyPaddle->paddle_shape.getSize().x, (videoMode.height/2.f- enemyPaddle->paddle_shape.getSize().y/2.f));
	this->enemyPaddle->paddle_shape.setFillColor(sf::Color::Cyan);
	this->enemyPaddle->paddle_shape.setOutlineColor(sf::Color::Green);
	this->enemyPaddle->paddle_shape.setOutlineThickness(1.f);

}

void Game::InitPaddle()
{


	if (this->playerPaddle) {
		delete this->playerPaddle;
	}

	this->playerPaddle = new PlayerPaddle(this, paddleSpeed);

	this->playerPaddle->paddle_shape.setPosition(0.f, (videoMode.height / 2.f - enemyPaddle->paddle_shape.getSize().y/ 2.f));
	this->playerPaddle->paddle_shape.setSize(sf::Vector2f(50.f, 150.f));
	this->playerPaddle->paddle_shape.setFillColor(sf::Color::Cyan);
	this->playerPaddle->paddle_shape.setOutlineColor(sf::Color::Green);
	this->playerPaddle->paddle_shape.setOutlineThickness(1.f);
}

void Game::InitBall()
{
	if (this->ball) {
		delete this->ball;
	}

	this->ball = new Ball(this);

	debugBall = new Ball(this);

	this->ball->shape.setSize(sf::Vector2f(35.f, 35.f));
	this->ball->shape.setPosition(playerPaddle->paddle_shape.getPosition().x + playerPaddle->paddle_shape.getSize().x + 20.f, playerPaddle->paddle_shape.getPosition().y - ball->shape.getSize().x / 2.f + playerPaddle->paddle_shape.getSize().y / 2.f);
	this->ball->shape.setFillColor(sf::Color::Cyan);
	this->ball->shape.setOutlineColor(sf::Color::Green);
	this->ball->shape.setOutlineThickness(1.f);

	this->debugBall->shape.setSize(sf::Vector2f(35.f, 35.f));
	this->debugBall->shape.setPosition(playerPaddle->paddle_shape.getPosition().x + playerPaddle->paddle_shape.getSize().x + 20.f, playerPaddle->paddle_shape.getPosition().y - ball->shape.getSize().x / 2.f + playerPaddle->paddle_shape.getSize().y / 2.f);
	this->debugBall->shape.setFillColor(sf::Color::Transparent);
	this->debugBall->shape.setOutlineColor(sf::Color::Red);
	this->debugBall->shape.setOutlineThickness(5.f);




}

void Game::InitText()
{	
	if (!font.loadFromFile("arial.ttf")) {
		// Handle error
	}
	points.x = 0;
	points.y = 0;
	score[0].setFont(font);
	score[0].setFillColor(sf::Color::Green);
	score[0].setString("0");
	score[0].setPosition(sf::Vector2f(videoMode.width / 4, videoMode.height / 10));

	score[1].setFont(font);
	score[1].setFillColor(sf::Color::Green);
	score[1].setString("0");
	score[1].setPosition(sf::Vector2f(videoMode.width *3 / 4, videoMode.height / 10));

	pauseText.setFont(font);
	pauseText.setFillColor(sf::Color::Green);
	pauseText.setString("Pause");
	pauseText.setPosition(sf::Vector2f(videoMode.width / 2, videoMode.height / 2));
}

void Game::InitMenu()
{
	if (this->Menu) {
		delete this->Menu;
	}
	this->Menu = new MainMenu(window->getSize().x, window->getSize().y,fullscreen);

}

void Game::InitSounds()
{
	if (!ballHit_buffer.loadFromFile("sounds/collision.mp3")) {
		return;
	}
	if (!ballReset_buffer.loadFromFile("sounds/Ball.mp3")) {
		return;
	}
	if (!gameOver_buffer.loadFromFile("sounds/game_over.mp3")) {
		return;
	}

	ballHit_sound.setBuffer(ballHit_buffer);
	ballReset_sound.setBuffer(ballReset_buffer);
	gameOver_sound.setBuffer(gameOver_buffer);
}

//constructor / deconstructor
Game::Game()
{
	this->InitWindow();
	this->InitMenu();
	this->InitEnemies();
	this->InitPaddle();
	this->InitBall();
	this->InitText();
	this->initVariables();
	this->InitSounds();

}

Game::~Game()
{
	delete this->window;
	delete this->Menu;
	delete this->enemyPaddle;
	delete this->playerPaddle;
	delete this->ball;
	delete this->debugBall;
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

sf::Vector2i Game::getScore()
{
	return points;
}

bool Game::getFullscrenMode()
{
	return fullscreen;
}

Ball& Game::getBall()
{
	return *debugBall;
}

void Game::setBallPos(float a, float b)
{
	this->debugBall->shape.setPosition(a, b);
}


//functions

void Game::checkCollision()
{

	if (ball->shape.getGlobalBounds().intersects(enemyPaddle->paddle_shape.getGlobalBounds()) && lastTouch) {
		ballSpeed *= 1.02f;
		float paddleCentre = enemyPaddle->paddle_shape.getPosition().y + enemyPaddle->paddle_shape.getSize().y / 2.f;
		float ballCentre = ball->shape.getPosition().y + ball->shape.getSize().y / 2.f;

		float diff = ballCentre - paddleCentre;
		diff = (diff / (playerPaddle->paddle_shape.getSize().y / 2.f));
		ball->direction.x = -ballSpeed;
		ball->direction.y = -diff * (ball->direction.x);
		lastTouch = false;
		ballHit_sound.play();


	}

	if (ball->shape.getGlobalBounds().intersects(playerPaddle->paddle_shape.getGlobalBounds()) && !lastTouch) {
		ballSpeed *= 1.02f;
		float paddleCentre = playerPaddle->paddle_shape.getPosition().y + playerPaddle->paddle_shape.getSize().y / 2.f;
		float ballCentre = ball->shape.getPosition().y + ball->shape.getSize().y / 2.f;

		float diff = ballCentre - paddleCentre;
		diff = (diff / (playerPaddle->paddle_shape.getSize().y / 2.f));
		ball->direction.x = ballSpeed;
		ball->direction.y = diff * (ball->direction.x);
		lastTouch = true;
		ballHit_sound.play();

	}

	if (ball->shape.getPosition().y <= 0 || ball->shape.getPosition().y + ball->shape.getSize().y >= videoMode.height) {
		ball->direction.y = -ball->direction.y;
		if (points.x != pointsTOwin && points.y != pointsTOwin) {
			ballHit_sound.play();

		}

	}


}

void Game::win()
{
	if (ball->shape.getPosition().x < -35) {
		points.y++;  // Enemy player score
		std::cout << "Points: " << points.x << " : " << points.y << std::endl;
		if (points.y == pointsTOwin) {
			end = true;
			play = false;
			gameOver_sound.play();

		}
		resetBall(1);
	}
	if (ball->shape.getPosition().x > videoMode.width + 35) {
		points.x++;  // Player score
		std::cout << "Points: " << points.x << " : " << points.y << std::endl;
		if (points.x == pointsTOwin) {
			end = true; 
			play = false;
			gameOver_sound.play();

		}
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

	ballSpeed = defaulBallSpeed;

	ballReset_sound.play();

}

void Game::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::KeyPressed:
                switch (this->ev.key.code) {
                    case sf::Keyboard::W:
						if (!play && !end) {
							Menu->MoveUp();
						}
						if (end) {
							Menu->MoveRigh();
						}
                        break;
                    case sf::Keyboard::S:
						if (!play && !end) {
							Menu->MoveDown();
						}
						if (end) {
							Menu->MoveLeft();
						}
						break;
					case sf::Keyboard::Space:
						pause = !pause;
                    case sf::Keyboard::Return:
						if (!play && !end) {
							mainMenu();
						}
						if (end) {
							endGameMenu();
						}
                        break;
                    case sf::Keyboard::Escape:
						if (!play && !end) {
							window->close();
							break;
						}
						endGameMenu();
						play = false;
						end = false;
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
		pause = false;
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
		fullscreen = !fullscreen;
		InitWindow();
		InitPaddle();
		InitBall();
		InitEnemies();
		InitText();
		Menu->updateMenu(videoMode.width, videoMode.height);
		Menu->updateEndMenu(videoMode.width, videoMode.height);
		break;
	case 4:
		window->close();
		break;
	}
}

void Game::endGameMenu()
{
	switch (Menu->getPressedEndItem()) {
	case 0:
		std::cout << "Play button has been pressed" << std::endl;
		end = false;
		play = false;
		start = false;
		twoPlayers = false;
		InitWindow();
		InitMenu();
		InitPaddle();
		InitBall();
		InitEnemies();
		InitText();
		initVariables();
		break;
	case 1:
		window->close();
		break;

	}
}

void Game::resetGame() {

	return;
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
	debugBall->direction.x = ball->direction.x;
	debugBall->direction.y = ball->direction.y;
	debugBall->move();

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
	if (!pause) {
		if (play) {
			this->updateEnemies();
			this->win();
			this->updateBall();
			this->updatePaddle();
		}
		this->updateScore();
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
	if (play ) {
		this->renderEnemies();
		this->window->draw(playerPaddle->paddle_shape);
		this->window->draw(ball->shape);
		this->window->draw(debugBall->shape);
		for (auto& h : score) {
			this->window->draw(h);
		}
		if (pause) {
			window->draw(pauseText);
		}
	}
	else if (end) {

		score[0].setPosition(sf::Vector2f(videoMode.width * 4 / 10, videoMode.height / 10));
		score[1].setPosition(sf::Vector2f(videoMode.width * 6 / 10, videoMode.height / 10));

		for (auto& h : score) {
			this->window->draw(h);
		}
		Menu->drawEnd(*window);
	}
	else {
		Menu->draw(*window);  
	}
	this->window->display();
}

void Game::renderEnemies()
{
		this->window->draw(enemyPaddle->paddle_shape);

}


