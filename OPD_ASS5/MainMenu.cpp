#include "MainMenu.h"

MainMenu::MainMenu(float w, float h,bool flscrn) : width(w),height(h), fpsSetting(0), fullscreen(flscrn) {
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
    }
    Player = false;
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("1 Player");
    menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("FPS: 60");  
    menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString(fullscreen ? "Fullscreen: On" : "Fullscreen: Off");
    menu[3].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));

    menu[4].setFont(font);
    menu[4].setFillColor(sf::Color::White);
    menu[4].setString("Exit");
    menu[4].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 5));



    endMenu[0].setFont(font);
    endMenu[0].setFillColor(sf::Color::Red);
    endMenu[0].setString("Play again!");
    endMenu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    endMenu[1].setFont(font);
    endMenu[1].setFillColor(sf::Color::White);
    endMenu[1].setString("Exit");
    endMenu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));


    selectedItemIndex = 0;
    selectedEndItemIndex = 0;
}

void MainMenu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

void MainMenu::drawEnd(sf::RenderWindow& window)
{


    for (int i = 0; i < MAX_NUMBER_OF_END_ITEMS; i++) {
        window.draw(endMenu[i]);
    }

}


void MainMenu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void MainMenu::MoveDown() {
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void MainMenu::MoveRigh()
{
    if (selectedEndItemIndex - 1 >= 0) {
        endMenu[selectedEndItemIndex].setFillColor(sf::Color::White);
        selectedEndItemIndex--;
        endMenu[selectedEndItemIndex].setFillColor(sf::Color::Red);
    }
}

void MainMenu::MoveLeft()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_END_ITEMS) {
        endMenu[selectedEndItemIndex].setFillColor(sf::Color::White);
        selectedEndItemIndex++;
        endMenu[selectedEndItemIndex].setFillColor(sf::Color::Red);
    }
}

void MainMenu::cycleFPS() {
    fpsSetting = (fpsSetting + 1) % 2;
    if (fpsSetting == 0) {
        menu[2].setString("FPS: 60");
    }
    else {
        menu[2].setString("FPS: 144");
    }
}

void MainMenu::togglePlayer()
{
    Player = !Player;
    menu[1].setString(Player ? "2 Players" : "1 Player");
}

void MainMenu::updateMenu(int w, int h)
{   
    width = w;
    height = h;
    menu[0].setPosition(sf::Vector2f(w / 2 - menu[0].getGlobalBounds().width / 2, h / (MAX_NUMBER_OF_ITEMS + 1) * 1));
    menu[1].setPosition(sf::Vector2f(w / 2 - menu[1].getGlobalBounds().width / 2, h / (MAX_NUMBER_OF_ITEMS + 1) * 2));
    menu[2].setPosition(sf::Vector2f(w / 2 - menu[2].getGlobalBounds().width / 2, h / (MAX_NUMBER_OF_ITEMS + 1) * 3));
    menu[3].setPosition(sf::Vector2f(w / 2 - menu[3].getGlobalBounds().width / 2, h / (MAX_NUMBER_OF_ITEMS + 1) * 4));
    menu[4].setPosition(sf::Vector2f(w / 2 - menu[4].getGlobalBounds().width / 2, h / (MAX_NUMBER_OF_ITEMS + 1) * 5));





}

void MainMenu::updateEndMenu(int w, int h) {
    endMenu[0].setPosition(sf::Vector2f(w / 2 - endMenu[0].getGlobalBounds().width / 2, h / (MAX_NUMBER_OF_END_ITEMS + 1) * 1));
    endMenu[1].setPosition(sf::Vector2f(w / 2 - endMenu[1].getGlobalBounds().width / 2, h / (MAX_NUMBER_OF_END_ITEMS + 1) * 2));
}







void MainMenu::toggleFullscreen() {
    fullscreen = !fullscreen;
    menu[3].setString(fullscreen ? "Fullscreen: On" : "Fullscreen: Off");

}
