#include "Turtle.h"

#include "Player.h"

Turtle::Turtle(Vector2f Position, Vector2f size, float offset, int HP, int maxHP, int damage, const string image, Vector2u imageCount, float switchTime)
: Entity(Position, size, offset, HP, maxHP, damage, image, imageCount, switchTime) {
    velocity = {speed, 0};
    spritePos = {mSize.x / 4.0f, -mSize.y / 1.0f};
    spriteSize = {body->getSize().x * 4.0f, body->getSize().y * 6.0f };

    getSound("sound/crab_crawling.ogg");
}

//обновление движения
void Turtle::updateMove(float time, Player* Player) {
    if (active) {
        velocity.y += 5.0f * 0.000981f * time;

        velocity.y = min(10.0f, velocity.y);

        row = 0;
        if (velocity.x > 0.0f) {
            faceRight = true;
            spritePos.x = abs(spritePos.x);
        } else {
            faceRight = false;
            spritePos.x = -abs(spritePos.x);
        }
    }

    body->move((velocity + knockback) * time);
    mPosition = body->getPosition();
}

void Turtle::OnCollision(sf::Vector2f direction) {
    if (direction.x < 0.0f) {
        velocity.x = abs(velocity.x);
    }else if (direction.x > 0.0f) {
        velocity.x = -abs(velocity.x);
    }
    if (direction.y > 0.0f) {
        velocity.y = 0.0f;
    }else if (direction.y < 0.0f && velocity.y < 0.0f) {
        velocity.y = 0.0f;
    }
}


/*
* 
void Turtle::updateMove(float time, Player* Player) {
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
}
else {
    faceRight = false;
}
if (abs(velocity.x) <= 0.1f) {
    row = 0;
}
else {
    row = 1;
}
    }
else {
    row = 2;
    velocity = { 0, 0 };
    }

    body->move(velocity * time);
    mPosition = body->getPosition();
}

*/