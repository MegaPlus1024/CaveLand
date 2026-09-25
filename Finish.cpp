//
// Created by User on 24.02.2025.
//

#include "Finish.h"

Finish::Finish(Vector2f mPosition, Vector2f mSize) {
    body = new RectangleShape(mSize);
    body->setOrigin(mSize / 2.0f);
    body->setOutlineColor(sf::Color::Magenta);
    body->setOutlineThickness(7.0f);
    body->setPosition(mPosition);
    body->setFillColor(sf::Color::Transparent);
    collider = new Collider(this->body);
}

Finish::Finish(Vector2f mPosition, Vector2f mSize, string path_) {
    this->mPosition = mPosition;
    this->mSize = mSize;

    body = new RectangleShape(mSize);
    body->setOrigin(mSize / 2.0f);
    body->setOutlineColor(sf::Color::Magenta);
    body->setOutlineThickness(7.0f);
    body->setPosition(mPosition);
    body->setFillColor(sf::Color::Transparent);
    collider = new Collider(this->body);

    setTexture("image/" + path_);
}

void Finish::setTexture(string path_) {
    mImage.loadFromFile(path_);
    mTexture.loadFromImage(mImage);
    mTexture.setRepeated(true);
    mSprite = Sprite(mTexture, IntRect(0, 0, mSize.x, mSize.y));
    mSprite.setPosition(mPosition);
    mSprite.setOrigin(mSize / 2.0f);
}

bool Finish::CheckCollision(Collider *other, sf::Vector2f &direction) {
    bool b = collider->CheckCollision(other, direction);
    return b;
}

void Finish::draw(RenderWindow &window) {
    window.draw(mSprite);
#ifdef godmode
    window.draw(*collider->body);
#endif
}