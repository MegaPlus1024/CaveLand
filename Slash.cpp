#include "Slash.h"

#include "Bat.h"
#include "Turtle.h"
#include "Hopper.h"

Slash::Slash(Vector2f* Position, Vector2f size, Vector2f velocity_, int damage, float time_, Vector2u imageCount, const string image) {
    mImage.loadFromFile("image/" + image);
    mTexture.loadFromImage(mImage);
    mSprite.setPosition(*Position);

    active = true;
    aFrame = time_;

    //mSprite.

    mImageCount = imageCount;

    animation = new Animation(&mTexture, imageCount, time_ / imageCount.x);
    mSprite.setTexture(mTexture);
    //cout << size.x << ' '  << mSprite.getGlobalBounds().width << ' ' <<  size.y << ' ' << mSprite.getGlobalBounds().height;
    //mSprite.setScale(size.x / mSprite.getGlobalBounds().width, size.y / mSprite.getGlobalBounds().height);
    setOriginCenter();
    //mSprite.setColor(sf::Color::White);

    playerPosition = Position;
    mPosition = *playerPosition;
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

    spritePos = {100, -50.0f};
    spriteSize = {body->getSize().x * 2.0f, body->getSize().y * 2.0f * 4 / 3};

    slash_sound.openFromFile("sound/slash.ogg");
}

//рисует героя
void Slash::draw(RenderWindow &window) {
    if (active) {
        window.draw(mSprite);
#ifdef godmode
        window.draw(*collider->body);
#endif
    }
}

//поменять размеры героя
void Slash::setSize(float W, float H) {
    mSize = {W, H};
}

void Slash::setSpriteBody(Vector2f spritePos_, Vector2f spriteSize_) {
    spritePos = spritePos_;
    spriteSize = spriteSize_;
}

//обновление движения
void Slash::updateMove(float time) {
    if (active) {
        mPosition = *playerPosition;
        if (velocity.x > 0.0f) {
            faceRight = true;
            spritePos.x = abs(spritePos.x);
            mPosition.x += mSize.x / 3;
            mPosition.y -= mSize.y / 6;
        } else {
            faceRight = false;
            spritePos.x = -abs(spritePos.x);
            mPosition.x -= mSize.x / 3;
            mPosition.y -= mSize.y / 6;
        }
        row = 0;
    }else {
        row = 0;
        velocity = {0, 0};
    }
}

void Slash::resetAnimation() {
    animation->reset();
}

//Поменять на центр
void Slash::setOriginCenter() {
    mSprite.setOrigin(animation->uvRect.width / 2.0f, animation->uvRect.height / 2.0f);
}

bool Slash::CheckCollision(Collider *other, sf::Vector2f& direction) {
    bool b = collider->CheckCollision(other, direction);
    return b;
}

void Slash::OnCollision(sf::Vector2f direction) {
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
}

void Slash::OnEnemyCollision(float time, sf::Vector2f direction, Entity* enemy) {
        enemy->HP -= damage;
        if (enemy->HP <= 0) {
            enemy->isAlive = false;
            enemy->deathSound.play();

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

void Slash::timerUpdate(float time) {
    aFrame -= time;
    if (aFrame < 0) {
        aFrame = 0;
        active = false;
    }
}

void Slash::updateAnimation(float time) {
    if (row == 0) {
        animation->update(row, time * (mImageCount.x - 1) / (mImageCount.x), faceRight, {0, mImageCount.x - 1});
    }
}

void Slash::updateSound() {

}

void Slash::update(float time) {
    updateMove(time);
    timerUpdate(time);
    //animation->update(row, time, faceRight);
    updateAnimation(time);
    mSprite.setTextureRect(animation->uvRect);
    body->setPosition(mPosition);
    //mSprite.setPosition(mPosition);
    //mSprite.scale(mSize.x / mSprite.getGlobalBounds().width, mSize.y / mSprite.getGlobalBounds().height);

    mSprite.setPosition(mPosition + spritePos);
    mSprite.scale(spriteSize.x / mSprite.getGlobalBounds().width, spriteSize.y / mSprite.getGlobalBounds().height);
}
