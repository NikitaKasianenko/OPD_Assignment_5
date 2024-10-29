#pragma once

#include <iostream>
#include <vector>
#include <ctime>



#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "MainMenu.h"


// class that acts as the game engine 
//wrapper class 

class PlayerPaddle;
class EnemyPaddle;
class Ball;

class Game
{
private:

	//variables

	float paddleSpeed;
	float ballSpeed;
	float resetBallSpeedX;
	float resetBallSpeedY;
	sf::Vector2i points; //x is player; y is enemy;
	bool play;
	bool start;
	bool fullscreen;
	int fps = 60;
	bool twoPlayers = false;
	

	//collision
	bool lastTouch;

	//Window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	//Game logic
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;


	// game objects
	PlayerPaddle* playerPaddle;
	EnemyPaddle* enemyPaddle;
	Ball* ball;
	MainMenu* Menu;
	sf::Font font;
	sf::Text score[2];


	//private func
	void initVariables();
	void InitWindow();
	void InitEnemies();
	void InitPaddle();
	void InitBall();

	void InitScore();
	void InitMenu();

public:

	//constructors / desctructors
	Game();
	virtual ~Game();

	//accessors
	const bool running() const;
	sf::VideoMode getVideoMode();
	sf::Vector2f getBallPositoin();
	sf::Vector2f getBallSize();
	sf::Vector2f getBallDirection();
	sf::RenderWindow& getWindow();


	//Functions
	void checkCollision();

	void win();
	void resetBall(int param);

	void pollEvents();
	void mainMenu();

	void updateEnemies();
	void updatePaddle();
	void updateBall();
	void updateScore();
	void update();
	
	

	void render();
	void renderEnemies();

};

