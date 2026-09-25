#include "Bat.h"

#include "Player.h"

Bat::Bat(Vector2f Position, Vector2f size, float offset, float offseta, int HP, int maxHP, int damage, const string image, Vector2u imageCount, float switchTime)
: Entity(Position, size, offset, HP, maxHP, damage, image, imageCount, switchTime) {
        //4 4 120


    accel = offseta;

    active = false;


    spritePos = {0.0f, -mSize.y / 4.0f};
    spriteSize = {body->getSize().x * 3.0f, body->getSize().y * 3.0f };

    activation.openFromFile("sound/activation.ogg");
    stepsSound.openFromFile("sound/bat.ogg");
}

//обновление движения

void Bat::updateMove(float time, Player* Player) {
    if (active) {


        point dir = (Player->getPosition() - getPosition());

         dir = dir * speed / dir.len();

            point dira = dir - velocity;

            if (abs(dira.x) > 1e-7 || abs(dir.y) > 1e-7) {
                dira = dira / dira.len() * accel;

                velocity.x += dira.x;
                velocity.y += dira.y;
            }

        if (velocity.x > 0.0f) {
            faceRight = true;
        } else {
            faceRight = false;
        }
        if (abs(velocity.x) <= 0.1f) {
            row = 0;
        } else {
            row = 1;
        }
    }else {
        row = 2;
        velocity = {0, 0};
    }

    body->move((velocity + knockback) * time);
    mPosition = body->getPosition();
}

void Bat::updateActive(Player* Player) {
    Vector2f dist = Player->getPosition() - getPosition();
    if (dist.x * dist.x + dist.y * dist.y < 4000000.f && !active) {
        active = true;
        activation.play();
    }
}




/*

void Bat::updateMove(float time, Player* Player) {
    if (active) {
        point dir = (Player->getPosition() - getPosition());
        
        dir = dir * speed / dir.len();
        velocity = {dir.x, dir.y};

        dir = dir * speed / dir.len();

        point dira = dir - velocity;

        if (abs(dira.x) > 1e-7 || abs(dir.y) > 1e-7) {
            dira = dira / dira.len() * accel;

            velocity.x += dira.x;
            velocity.y += dira.y;
        }

        if (velocity.x > 0.0f) {
            faceRight = true;
        }else {
            faceRight = false;
        }
        if (abs(velocity.x) <= 0.1f) {
            row = 0;
        } else {
            row = 1;
        }
    } else {
        row = 2;
        velocity = { 0, 0 };
    }

    body->move(velocity * time);
    mPosition = body->getPosition();
}*/



/*point dir = ((Player->getPosition() - getPosition()) / (point(Player->getPosition() - getPosition())).len())
    * (((point(Player->getPosition() - getPosition())).len() - kkk * sqrt(2)) / 10);

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
    kkk += (400.0f / (kkk * kkk * kkk * kkk * kkk)) * 50000000000000;
}
else {
    kkk = 400.0f;
}kkk = max(400.0f, kkk);

velocity = {dir.x, dir.y};*/