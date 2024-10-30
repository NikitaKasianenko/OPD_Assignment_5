#include <vector>
#include <iostream>
#include <string>
#include "Game.h"
#include "PlayerPaddle.h"


using namespace std;


int main() {


	//init game engine
	Game game;
	


	//game loop
	while (game.running()) {

		////update
		game.update();
		////render
		game.render();
		

	}

	//end of app


	return 0;

}