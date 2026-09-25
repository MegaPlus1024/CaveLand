//
// Created by User on 24.02.2025.
//

#include "Transition.h"

Transition::Transition(Vector2f mPosition, Vector2f mSize, string nextlevel_, Vector2f positionStart_) {
    nextlevel = nextlevel_;

    body = new RectangleShape(mSize);
    body->setOrigin(mSize / 2.0f);
    body->setOutlineColor(sf::Color::Magenta);
    body->setOutlineThickness(7.0f);
    body->setPosition(mPosition);
    body->setFillColor(sf::Color::Transparent);
    collider = new Collider(this->body);

    positionStart = positionStart_;
}

bool Transition::CheckCollision(Collider *other, sf::Vector2f& direction) {
    bool b = collider->CheckCollision(other, direction);
    return b;
}

void Transition::draw(RenderWindow &window) {
#ifdef godmode
    window.draw(*collider->body);
#endif
}