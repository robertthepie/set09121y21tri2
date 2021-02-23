//bullet.cpp
#include "Bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

//Create definition for the constructor
//...
unsigned char Bullet::bulletPointer = 0;
Bullet Bullet::bullets[256];

Bullet::Bullet() {
    bullets[bulletPointer++] = *this;
    setPosition(0.0f, 0.0f);
    _mode = false;
    setTexture(spritesheet);
    _sprite = sf::IntRect(64, 32, 32, 32);
    setTextureRect(_sprite);
}
Bullet::Bullet(const sf::Vector2f& pos, const bool mode) {
    bullets[bulletPointer++] = *this;
    setPosition(pos);
    _mode = mode;
    setTexture(spritesheet);
    if (mode) {
        _sprite = sf::IntRect(64, 32, 32, 32);
    }
    else {
        _sprite = sf::IntRect(32, 32, 32, 32);
    }
    setTextureRect(_sprite);
}



void Bullet::Update(const float& dt) {
    for (auto &s : bullets) {
        s._Update(dt);
    }
}

//bullet.cpp
void Bullet::_Update(const float& dt) {
    if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
        //off screen - do nothing
        return;
    }
    else {
        move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
        const FloatRect boundingBox = getGlobalBounds();

        for (auto s : ships) {
            if (!_mode && s == player) {
                //player bulelts don't collide with player
                continue;
            }
            if (_mode && s != player) {
                //invader bullets don't collide with other invaders
                continue;
            }
            if (!s->is_exploded() &&
                s->getGlobalBounds().intersects(boundingBox)) {
                //Explode the ship
                s->Explode();
                //warp bullet off-screen
                setPosition(-100, -100);
                return;
            }
        }
    }
}

// spawns a bullet at passed in position, false = player, true = invader
void Bullet::Fire(const sf::Vector2f& pos, const bool mode) {
    bullets[++bulletPointer].setPosition(pos);
    bullets[bulletPointer]._mode = mode;
    bullets[bulletPointer].setTexture(spritesheet);
    if (mode) {
        bullets[bulletPointer]._sprite = sf::IntRect(64, 32, 32, 32);
    }
    else {
        bullets[bulletPointer]._sprite = sf::IntRect(32, 32, 32, 32);
    }
    bullets[bulletPointer].setTextureRect(bullets[bulletPointer]._sprite);
}

void Bullet::Render(sf::RenderWindow& window) {
    for (auto& s : bullets) {
        window.draw(s);
    }
}