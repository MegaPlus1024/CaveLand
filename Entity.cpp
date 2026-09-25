#include "Entity.h"

#include "Player.h"

Entity::Entity(Vector2f Position, Vector2f size, float offset, int HP, int maxHP, int damage, const string image, Vector2u imageCount, float switchTime) {
    mImage.loadFromFile("image/" + image);
    mTexture.loadFromImage(mImage);
    mSprite.setPosition(Position);

    col = {0, imageCount.x};
    animation = new Animation(&mTexture, imageCount, switchTime);
    mSprite.setTexture(mTexture);
    setOriginCenter();

    mPosition = Position;
    mSize = size;
    speed = offset;

    velocity = {0, 0};

    body = new RectangleShape(mSize);
    body->setOrigin(mSize / 2.0f);
    body->setOutlineColor(sf::Color::Magenta);
    body->setOutlineThickness(7.0f);
    body->setPosition(mPosition);
    body->setFillColor(sf::Color::Transparent);
    collider = new Collider(this->body);

    this->maxHP = maxHP;
    if (HP > maxHP) {
        this->HP = maxHP;
    }else {
        this->HP = HP;
    }

    isAlive = true;
    this->damage = damage;

    hitSlash = false;
    hitFireball.resize(20);

    spritePos = {0, 0};
    spriteSize = {body->getSize().x, body->getSize().y};

    impact_sound.openFromFile("sound/slashimpact.ogg");
    deathSound.openFromFile("sound/kill.ogg");
    burnt.openFromFile("sound/burned.ogg");
}

//рисует героя
void Entity::draw(RenderWindow &window) {
    if (isAlive) {
        window.draw(mSprite);
    }
#ifdef godmode
    window.draw(*collider->body);
#endif
}

//дать звук
void Entity::getSound(string failAudio) {
    stepsSound.openFromFile(failAudio);
}

//поменять громкость
void Entity::soundSetVolume(int volume) {
    stepsSound.setVolume(volume);
}

//поменять размеры героя
void Entity::setSize(float W, float H) {
    mSize = {W, H};
}

//поменять позицию
void Entity::setPosition(float x, float y) {
    mSprite.setPosition(x, y);
}

//обновление движения
void Entity::updateMove(float time, Player* Player) {
    body->move((velocity + knockback) * time);
    mPosition = body->getPosition();
}

//Поменять на центр
void Entity::setOriginCenter() {
    mSprite.setOrigin(animation->uvRect.width / 2.0f, animation->uvRect.height / 2.0f);
}

Vector2f Entity::getPosition() {
    return mPosition;
}

bool Entity::CheckCollision(Collider *other, sf::Vector2f& direction, float push) {
    bool b = collider->CheckCollision(other, direction, push);
    mPosition = body->getPosition();
    mSprite.setPosition(mPosition + spritePos);
    return b;
}

void Entity::OnCollision(sf::Vector2f direction) {
    if (direction.x < 0.0f) {
        //velocity.x = 0.0f;
    }else if (direction.x > 0.0f) {
        //velocity.x = 0.0f;
    }
    if (direction.y > 0.0f) {
        velocity.y = 0.0f;
    }else if (direction.y < 0.0f && velocity.y < 0.0f) {
        velocity.y = 0.0f;
    }
}

void Entity::updateActive(Player* Player) {
    active = true;
}

void Entity::updateSound(Player* player) {
    if (stepsSound.getDuration().asMilliseconds() != 0 && active) {
        if (stepsSound.getStatus() != stepsSound.Playing) {
            auto d = mPosition - player->getPosition();
            stepsSound.setVolume(max(min(100, 120 - int(sqrt(d.x * d.x + d.y * d.y) / 50.0f)), 0));
            //cout << d.x << ' ' << d.y << ' ' << 120 - int(sqrt(d.x * d.x + d.y * d.y) / 50.0f) << endl;
            stepsSound.play();
        }
    }
}

void Entity::timerUpdate(float time) {
    knockbacktime -= time;
    if (knockbacktime < 0) {
        knockbacktime = 0;
        knockback = {0.0f, 0.0f};
    }
}

void Entity::setKnockback(bool faceRight_, float mas) {
    if (faceRight_) {
        knockback.x = speed * mas;
    }else {
        knockback.x = -speed * mas;
    }
    knockbacktime = knockbackcd;
}

void Entity::update(float time, Player* Player) {
    if (isAlive) {
        timerUpdate(time);
        updateActive(Player);
        updateMove(time, Player);
        updateSound(Player);
        animation->update(row, time, faceRight, col);
        mSprite.setTextureRect(animation->uvRect);
        mSprite.setPosition(mPosition + spritePos);
        mSprite.scale(spriteSize.x / mSprite.getGlobalBounds().width, spriteSize.y / mSprite.getGlobalBounds().height);
    }
}