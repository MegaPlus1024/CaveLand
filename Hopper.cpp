#include "Hopper.h"

#include "Player.h"

Hopper::Hopper(Vector2f Position, Vector2f size, float offset, int HP, int maxHP, int damage, const string image, Vector2u imageCount, float switchTime)
        : Entity(Position, size, offset, HP, maxHP, damage, image, imageCount, switchTime) {
    velocity = {speed, 0};

    col = {1, 3};

    canJump = false;

    spritePos = {0.0f, -mSize.y / 1.0f};
    spriteSize = {body->getSize().x * 4.0f, body->getSize().y * 6.0f };
}

//обновление движения
void Hopper::updateMove(float time, Player* Player) {
    if (active) {
        if (velocity.y > 0.0f) {
            canJump = false;
        }

        if (canJump) {
            canJump = false;
            velocity.y = -sqrtf(5.0f * 2.0f * 0.000981f * 1000);
        }

        velocity.y += 5.0f * 0.000981f * time;

        velocity.y = min(10.0f, velocity.y);

        if (velocity.x > 0.0f) {
            faceRight = true;
            spritePos.x = abs(spritePos.x);
        } else {
            faceRight = false;
            spritePos.x = -abs(spritePos.x);
        }

        if (velocity.y < 0.0f) {
            if (row != 1) {
                animation->reset();
            }
            row = 1;
        }else {
            if (row != 2) {
                animation->reset();
            }
            row = 2;
        }
    }

    body->move((velocity + knockback) * time);
    mPosition = body->getPosition();
}

void Hopper::OnCollision(sf::Vector2f direction) {
    if (direction.x < 0.0f) {
        velocity.x = abs(velocity.x);
    }else if (direction.x > 0.0f) {
        velocity.x = -abs(velocity.x);
    }
    if (direction.y > 0.0f) {
        velocity.y = 0.0f;
        canJump = true;
    }else if (direction.y < 0.0f && velocity.y < 0.0f) {
        velocity.y = 0.0f;
    }
}


/*
* 
void Hopper::updateMove(float time, Player* Player) {
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