#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Game.h"
#include "LevelSystem.h"

using namespace sf;
using namespace std;

std::unique_ptr<Player>player;

void Reset() {

}

void Load() {
    player = std::make_unique<Player>();
    ls::loadLevelFile("res/maze_2.txt");

    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            cout << ls::getTile({ x, y });
        }
        cout << endl;
    }
}

void Update(RenderWindow& window) {
    /*
    ** Clock
    */
    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();
    /*
    ** Close Window and other Events
    */
    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }
    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }
    /*
    ** Updates go here
    */

    player->Update(dt);
}

void Render(RenderWindow& window) {
    ls::Render(window);
    player->Render(window);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "TileSet");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}