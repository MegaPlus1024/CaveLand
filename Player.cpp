#include "Player.h"

#include "Bat.h"
#include "Turtle.h"
#include "Hopper.h"

Player::Player(Vector2f Position, Vector2f size, float offset, float jumpHeight, int HP, int maxHP, const string image) {
    mImage.loadFromFile("image/" + image);
    mTexture.loadFromImage(mImage);
    mSprite.setPosition(Position);

    //mSprite.

    animation = new Animation(&mTexture, {8, 9}, 120.0f);
    mSprite.setTexture(mTexture);
    //cout << size.x << ' '  << mSprite.getGlobalBounds().width << ' ' <<  size.y << ' ' << mSprite.getGlobalBounds().height;
    //mSprite.setScale(size.x / mSprite.getGlobalBounds().width, size.y / mSprite.getGlobalBounds().height);
    setOriginCenter();
    //mSprite.setColor(sf::Color::White);

    mPosition = new Vector2f(Position);
    mSize = size;
    speed = offset;

    body = new RectangleShape(mSize);
    body->setOrigin(mSize / 2.0f);
    body->setOutlineColor(sf::Color::Magenta);
    body->setOutlineThickness(7.0f);
    body->setPosition(*mPosition);
    body->setFillColor(sf::Color::Transparent);
    collider = new Collider(this->body);

    this->jumpHeight = jumpHeight;

    knockback = {0.0f, 0.0f};

    this->maxHP = maxHP;
    if (HP > maxHP) {
        this->HP = maxHP;
    }else {
        this->HP = HP;
    }

    spritePos = {0.0f, -mSize.y / 4.0f};
    spriteSize = {body->getSize().x * 3.0f, body->getSize().y * 1.5f };


    getSound("sound/jumpp.ogg", jumpSound);
    getSound("sound/steps.ogg", stepsSound);
    getSound("sound/damaged.ogg", hurtSound);
    getSound("sound/heal.ogg", healSound);
}

//герой следит за спрайтом
void Player::sleditForSprite(Sprite &s, float x, float y) {
    mSprite.setPosition(s.getPosition().x + x, s.getPosition().y + y);
}

//рисует героя
void Player::draw(RenderWindow &window) {
    window.draw(mSprite);
#ifdef godmode
    window.draw(*collider->body);
#endif
}

//наведина мышка
bool Player::navediaMouse(Event &event, Vector2f pos) {
    if (mSprite.getGlobalBounds().contains(pos.x, pos.y)) return true;
    else return false;
}

//дать звук
void Player::getSound(string failAudio, Music& sound) {
    sound.openFromFile(failAudio);
}

//поменять громкость
void Player::soundSetVolume(int volume) {
    stepsSound.setVolume(volume);
}

//поменять размеры героя
void Player::setCharacterSize(float W, float H) {
    mSize = {W, H};
}

//поменять позицию
void Player::setPosition(Vector2f position) {
    body->setPosition(position);
    mPosition->x = body->getPosition().x;
    mPosition->y = body->getPosition().y;
}

//обновление движения
void Player::updateMove(float time) {
    justJumped = false;

    if (hitVelocity == Vector2f(0.0f, 0.0f)) {
        velocity.x = 0.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            velocity.x -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            velocity.x += speed;
        if (velocity.y > 0.0f) {
            canJump = false;
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
            //|| sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            ) && canJump) {
            canJump = false;
            justJumped = true;
            velocity.y = -sqrtf(5.0f * 2.0f * 0.000981f * jumpHeight);
        } else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
                     //|| sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
                     || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
        )) {
            velocity.y = max(0.0f, velocity.y);
        }

        velocity.y += 5.0f * 0.000981f * time;

        velocity.y = min(5.0f, velocity.y);
    }else {
        velocity = hitVelocity;
    }

    body->move((velocity + knockback) * time);
    mPosition->x = body->getPosition().x;
    mPosition->y = body->getPosition().y;
}

//Поменять на центр
void Player::setOriginCenter() {
    mSprite.setOrigin(animation->uvRect.width / 2.0f, animation->uvRect.height / 2.0f);
}

//получить хп
int Player::getHp() {
    return HP;
}

//получить макс хп
int Player::getMaxHp() {
    return maxHP;
}

void Player::increaseHp(int inc) {
    HP += inc;
    HP = min(HP, maxHP);
}

//int Player::

Vector2f Player::getPosition() {
    return *mPosition;
}

Vector2f* Player::getPositionLink() {
    return mPosition;
}

Vector2f Player::getVelocity(float time) {
    return (velocity + knockback) * time;
}

bool Player::CheckCollision(Collider *other, sf::Vector2f& direction, float push) {
    bool b = collider->CheckCollision(other, direction, push);
    mPosition->x = body->getPosition().x;
    mPosition->y = body->getPosition().y;
    mSprite.setPosition(*mPosition + spritePos);
    return b;
}

bool Player::CheckCollision(Collider *other, sf::Vector2f& direction) {
    bool b = collider->CheckCollision(other, direction);
    mPosition->x = body->getPosition().x;
    mPosition->y = body->getPosition().y;
    mSprite.setPosition(*mPosition + spritePos);
    return b;
}

void Player::OnCollision(sf::Vector2f direction) {
    if (direction.x < 0.0f) {
        //velocity.x = 0.0f;
    }else if (direction.x > 0.0f) {
        //velocity.x = 0.0f;
    }
    if (direction.y > 0.0f) {
        velocity.y = 0.0f;
        canJump = true;
    }else if (direction.y < 0.0f && velocity.y < 0.0f) {
        velocity.y = 0.0f;
    }
}

void Player::OnEnemyCollision(float time, sf::Vector2f direction, Entity* enemy) {
    if (iframe == 0) {
        iframe = 2000.0f;
        if (velocity.x > 0.0f || faceRight) {
            hitVelocity.x = -speed * 1.5;
        }else {
            hitVelocity.x = speed * 1.5;
        }
        HP -= enemy->damage;
        hurtSound.play();
    }
}

void Player::updateAnimation(float time) {
    if (velocity.x > 0.0f) {
        faceRight = true;
    }else if (velocity.x < 0.0f) {
        faceRight = false;
    }
    if (hitVelocity == Vector2f(0.0f, 0.0f)) {
        if (velocity.x == 0.0f) {
            row = 0;
            col = {0, 2};
        } else {
            row = 3;
            col = {0, 8};
        }
        if (velocity.y < 0.0f) {
            row = 5;
            col = {0, 4};
        } else if (velocity.y > 0.0f) {
            row = 5;
            col = {4, 4};
        }
    }else {
        row = 7;
        col = {1, 3};
        faceRight = !faceRight;
    }

    animation->update(row, time, faceRight, col);
    mSprite.setTextureRect(animation->uvRect);
    //mSprite.setTextureRect(IntRect(384, 576, 192, 192));
}

void Player::timerUpdate(float time) {
    iframe -= time;
    if (iframe <= 1700.0f) {
        hitVelocity = {0, 0};
    }
    if (iframe < 0) {
        iframe = 0;
    }

    knockbacktime -= time;
    if (knockbacktime < 0) {
        knockbacktime = 0;
        knockback = {0.0f, 0.0f};
    }
}

void Player::updateSound() {
    /*if (stepsSound.getStatus() != stepsSound.Playing) {
        stepsSound.play();
    }*/
    if (canJump && abs(velocity.x) > 0.00001) {
        if (stepsSound.getStatus() != stepsSound.Playing) {
            stepsSound.play();
        }
    }else {
        stepsSound.pause();
    }

    if (justJumped) {
        jumpSound.play();
    }
}

void Player::setKnockback(bool faceRight_) {
    if (faceRight_) {
        knockback.x = -speed * 0.3;
    }else {
        knockback.x = speed * 0.3;
    }
    knockbacktime = knockbackcd;
}

void Player::update(float time) {
    timerUpdate(time);
    updateMove(time);
    updateSound();

    mSprite.setPosition(*mPosition + spritePos);
    mSprite.scale(spriteSize.x / mSprite.getGlobalBounds().width, spriteSize.y / mSprite.getGlobalBounds().height);

    //mSprite.setPosition(*mPosition);
    //mSprite.scale(mSize.x / mSprite.getGlobalBounds().width, mSize.y / mSprite.getGlobalBounds().height);
}


//bat collision
/*

    if (direction.x < 0.0f) {
        velocity.x = 0.0f;
    }else if (direction.x > 0.0f) {
        velocity.x = 0.0f;
    }
    if (direction.y > 0.0f) {
        velocity.y = 0.0f;
        canJump = true;
    }else if (direction.y < 0.0f) {
        velocity.y = 0.0f;
    }*/