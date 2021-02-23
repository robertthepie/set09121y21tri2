//player.cpp
#include "player.h"
using namespace sf;
using namespace std;

void Player::Update(double dt) {
    //Move in four directions based on keys
    //@TODO
    static Vector2f mvdr; // move direction
    mvdr = { 0, 0 };
    if ((Keyboard::isKeyPressed(Keyboard::A)|| Keyboard::isKeyPressed(Keyboard::Left)) && !(Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))) { // left
        mvdr.x = -(_speed * dt);
    }
    else if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) && !(Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))) { // right
        mvdr.x = (_speed * dt);
    }
    if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) && !(Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))) { // up
        mvdr.y = -(_speed * dt);
    }
    else if ((Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) && !(Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))) { // down
        mvdr.y = (_speed * dt);
    }
    move(mvdr);
    Entity::Update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}
