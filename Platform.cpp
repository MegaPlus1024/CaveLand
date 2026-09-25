#include "Platform.h"

#include "Player.h"

Platform::Platform(Vector2f Position, Vector2f size) {
    mPosition = Position;
    mSize = size;

    body = new RectangleShape(mSize);
    body->setOrigin(mSize / 2.0f);
    body->setOutlineColor(sf::Color::Magenta);
    body->setOutlineThickness(7.0f);
    body->setPosition(mPosition);
    body->setFillColor(sf::Color::White);
    collider = new Collider(this->body);
}

Platform::Platform(Vector2f Position, Vector2f size, string path_) {
    mPosition = Position;
    mSize = size;

    body = new RectangleShape(mSize);
    body->setOrigin(mSize / 2.0f);
    body->setOutlineColor(sf::Color::Magenta);
    body->setOutlineThickness(7.0f);
    body->setPosition(mPosition);
    body->setFillColor(sf::Color::White);
    collider = new Collider(this->body);

    setTexture(path_);
}

//рисует героя
void Platform::draw(RenderWindow &window) {
#ifdef godmode
    window.draw(*collider->body);
#endif
    window.draw(mSprite);
}

//дать звук
void Platform::getSound(string failAudio) {
    buffer.loadFromFile(failAudio);

    stepsSound.setBuffer(buffer);
}

//поменять громкость
void Platform::soundSetVolume(int volume) {
    stepsSound.setVolume(volume);
}

//поменять размеры героя
void Platform::setSize(float W, float H) {
    mSize = {W, H};
}

void Platform::setTexture(string path_) {
    mImage.loadFromFile(path_);
    mTexture.loadFromImage(mImage);
    mTexture.setRepeated(true);
    //mSprite.set;
    mSprite = Sprite(mTexture, IntRect(0, 0, mSize.x, mSize.y));
    mSprite.setPosition(mPosition);
    mSprite.setOrigin(mSize / 2.0f);
    //mSprite.scale(mSize.x / mSprite.getGlobalBounds().width, mSize.y / mSprite.getGlobalBounds().height);
}

//поменять позицию
void Platform::setPosition(float x, float y) {
    mSprite.setPosition(x, y);
}

Vector2f Platform::getPosition() {
    return mPosition;
}

bool Platform::CheckCollision(Collider *other, sf::Vector2f& direction, float push) {
    bool b = collider->CheckCollision(other, direction, push);
    mPosition = body->getPosition();
    mSprite.setPosition(mPosition);
    return b;
}