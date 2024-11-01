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
	sf::Vector2i points; //x is player; y is enemy;
	
	bool play;
	bool start;
	bool pause = false;
	bool end = false;
	bool fullscreen = false;
	bool twoPlayers = false;

	int fps = 60;

	//collision
	bool lastTouch;

	//Window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	//Game logic
	float paddleSpeed;
	float ballSpeed;
	float defaulBallSpeed;
	float resetBallSpeedX;
	float resetBallSpeedY;

	int pointsTOwin = 3;


	// game objects
	PlayerPaddle* playerPaddle;
	EnemyPaddle* enemyPaddle;
	Ball* ball;
	Ball* debugBall;
	MainMenu* Menu;

	sf::Font font;
	sf::Text score[2];
	sf::Text pauseText;

	sf::SoundBuffer ballHit_buffer;
	sf::SoundBuffer ballReset_buffer;
	sf::SoundBuffer gameOver_buffer;

	sf::Sound ballHit_sound;
	sf::Sound ballReset_sound;
	sf::Sound gameOver_sound;
	
	//private func
	void initVariables();
	void InitWindow();
	void InitEnemies();
	void InitPaddle();
	void InitBall();
	void InitText();
	void InitMenu();
	void InitSounds();


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
	sf::Vector2i getScore();
	bool getFullscrenMode();
	Ball& getBall();
	void setBallPos(float a, float b);


	//Functions
	void checkCollision();

	void win();
	void resetBall(int param);

	void pollEvents();
	void mainMenu();
	void endGameMenu();
	void resetGame();

	void updateEnemies();
	void updatePaddle();
	void updateBall();
	void updateScore();
	void update();
	
	
	void render();
	void renderEnemies();

};

