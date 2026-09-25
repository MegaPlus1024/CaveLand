#include "Projectile.h"

#include "Bat.h"
#include "Turtle.h"
#include "Hopper.h"

Projectile::Projectile(Vector2f Position, Vector2f size, Vector2f velocity_, int damage, float time_, Vector2u ImageCount, const string image) {
    mImage.loadFromFile("image/" + image);
    mTexture.loadFromImage(mImage);
    mSprite.setPosition(Position);

    active = true;
    aFrame = time_;

    //mSprite.

    animation = new Animation(&mTexture, ImageCount, 120.0f);
    mSprite.setTexture(mTexture);
    //cout << size.x << ' '  << mSprite.getGlobalBounds().width << ' ' <<  size.y << ' ' << mSprite.getGlobalBounds().height;
    //mSprite.setScale(size.x / mSprite.getGlobalBounds().width, size.y / mSprite.getGlobalBounds().height);
    setOriginCenter();
    //mSprite.setColor(sf::Color::White);

    mPosition = Position;
    mSize = size;
    velocity = velocity_;

    body = new RectangleShape(mSize);
    body->setOrigin(mSize / 2.0f);
    body->setOutlineColor(sf::Color::Magenta);
    body->setOutlineThickness(7.0f);
    body->setPosition(mPosition);
    body->setFillColor(sf::Color::Transparent);
    collider = new Collider(this->body);

    this->damage = damage;
    spriteSize = {body->getSize().x * 3.0f, body->getSize().y * 3.0f };
}

//рисует героя
void Projectile::draw(RenderWindow &window) {
    window.draw(mSprite);
#ifdef godmode
    window.draw(*collider->body);
#endif
}

//дать звук
void Projectile::getSound(string failAudio) {
    buffer.loadFromFile(failAudio);

    stepsSound.setBuffer(buffer);
}

//поменять громкость
void Projectile::soundSetVolume(int volume) {
    stepsSound.setVolume(volume);
}

//поменять размеры героя
void Projectile::setSize(float W, float H) {
    mSize = {W, H};
}

//поменять позицию
void Projectile::setPosition(Vector2f mPosition_) {
    mPosition = mPosition_;
    body->setPosition(mPosition_);
}

//обновление движения
void Projectile::updateMove(float time) {
    if (active) {
        if (velocity.x > 0.0f) {
            faceRight = true;
        } else {
            faceRight = false;
        }
        row = 0;
    }

    body->move(velocity * time);
    mPosition = body->getPosition();
}

void Projectile::resetAnimation() {
    animation->reset();
}
//Поменять на центр
void Projectile::setOriginCenter() {
    mSprite.setOrigin(animation->uvRect.width / 2.0f, animation->uvRect.height / 2.0f);
}

Vector2f Projectile::getPosition() {
    return mPosition;
}

bool Projectile::CheckCollision(Collider *other, sf::Vector2f& direction) {
    bool b = collider->CheckCollision(other, direction);
    mPosition = body->getPosition();
    mSprite.setPosition(mPosition);
    return b;
}

void Projectile::OnCollision(sf::Vector2f direction) {
    if (direction.x < 0.0f) {
        velocity.x = 0.0f;
    }else if (direction.x > 0.0f) {
        velocity.x = 0.0f;
    }
    if (direction.y > 0.0f) {
        velocity.y = 0.0f;
    }else if (direction.y < 0.0f) {
        velocity.y = 0.0f;
    }
    active = false;
}

void Projectile::OnEnemyCollision(float time, sf::Vector2f direction, Entity* enemy) {
        enemy->HP -= damage;
        if (enemy->HP <= 0) {
            enemy->isAlive = false;

            ifstream indata("game_data/current.txt");
            int cur;
            indata >> cur;
            cur += enemy->cost;
            indata.close();

            ofstream outdata("game_data/current.txt");
            outdata << cur << '\n';
            outdata.close();
        }
}

void Projectile::timerUpdate(float time) {
    aFrame -= time;
    if (aFrame < 0) {
        aFrame = 0;
        active = false;
    }
}

void Projectile::update(float time) {
    updateMove(time);
    timerUpdate(time);
    animation->update(row, time, !faceRight);
    mSprite.setTextureRect(animation->uvRect);
    mSprite.setPosition(mPosition);
    mSprite.scale(spriteSize.x / mSprite.getGlobalBounds().width, spriteSize.y / mSprite.getGlobalBounds().height);
}
