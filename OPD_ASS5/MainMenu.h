#pragma once
#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 5  // Increased to include additional options

class MainMenu {
public:
    MainMenu(float w, float h);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int getPressedItem() const { return selectedItemIndex; }

    // FPS and fullscreen settings
    int getFPSSetting() const { return fpsSetting; }
    bool isFullscreen() const { return fullscreen; }

    // Methods to modify options
    void toggleFullscreen();
    void cycleFPS();
    void togglePlayer();
    void updateMenu(int w,int h);

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];

    // Additional settings
    int fpsSetting;  // 0 for 60 FPS, 1 for 144 FPS
    bool fullscreen; // true for fullscreen mode
    bool Player; // true for 2 player 
    float width, height;
};
