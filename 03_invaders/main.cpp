
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"
#include "game.h"
#include <typeinfo> 
#include "Bullet.h"


using namespace sf;
using namespace std;



/*
const int gameWidth = 800;
const int gameHeight = 600;
const int invaders_rows = 5;
const int invaders_columns = 12;
*/

/*
**
*/

Texture spritesheet;
Sprite invader;
Player *player;

std::vector<Ship*> ships;

void Reset() {
}

void Load() {
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    player = new Player();
    ships.push_back(player);
    //*
    //int spritePositions[] = { 0,64,128 };
    for (int i = 0; i < invaders_columns; i++) {
        for (int j = 0; j < invaders_rows; j++) {
            float x = (i * 48.0f + 100.0f);
            float y = (j * 48.0f + 100.0f);
            Vector2f pos = Vector2f(x, y);
            Invader* inv = new Invader(sf::IntRect(j*32, 0, 32, 32), pos);
            ships.push_back(inv);

        }
    }
    for (int i = 0; i < 256; i++) {
        new Bullet();
    }
    /*/ //@TODO uhhhhh i wasn't paying attention to the guide
    for (int r = 0; r < invaders_rows; ++r) {
        auto rect = IntRect(...);
        for (int c = 0; c < invaders_columns; ++c) {
            Vector2f position = ...;
            auto inv = new Invader(rect, position);
            ships.push_back(inv);
        }
    //*/
    Invader::speed = 50.0f;
}

void Update(RenderWindow& window) {
    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();
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

    for (auto& s : ships) {

        s->Update(dt);
    };

    Bullet::Update(dt);
}

void Render(RenderWindow& window) {
    // Draw Everything
    for (const auto s : ships) {
        window.draw(*s);
    }
    Bullet::Render(window);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}