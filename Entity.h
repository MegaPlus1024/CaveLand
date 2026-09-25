#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include "Geometry.h"
#include "Animation.h"
#include "Collider.h"
using namespace std;
using namespace sf;

class Player;

class Entity {
protected :
    float kkk = 400.0f;

    bool active;

    int row;
    pair<int, int> col; //startFrame, frameCount
    bool faceRight;
    Animation* animation;

    Music stepsSound;   //звук шагов

    Vector2f mPosition;
    Vector2f mSize;
    float speed;
    float accel;

    Image mImage;
    Texture mTexture;

public:
    Music impact_sound;
    Music burnt;
    Music deathSound;

    int HP;
    int maxHP;

    bool hitSlash;
    vector<bool> hitFireball;

    RectangleShape* body;
    Collider* collider;

    Vector2f velocity;
    Vector2f acceleration;

    Vector2f knockback;
    float knockbacktime = 0.0f, knockbackcd = 300.0f;

    int damage;

    bool isAlive;

    Vector2f spritePos;
    Vector2f spriteSize;
    Sprite mSprite; //сам игрок

    int cost;

    Entity(Vector2f Position, Vector2f size, float offset, int HP, int maxHP, int damage, const string image, Vector2u imageCount, float switchTime);

    //рисует героя
    void draw(RenderWindow& window);

    //дать звук
    void getSound(string failAudio);

    //поменять громкость
    void soundSetVolume(int volume);

    //поменять размеры квадрата кнопки
    void setSize(float W, float H);
/*
    //Поменять на центр
    void setOriginCenter();*/

    //поменять позицию
    void setPosition(float x, float y);

    //Поменять на центр
    void setOriginCenter();

    virtual //обновление движения
    void updateMove(float time, Player* Player);

    //получить позицию
    Vector2f getPosition();

    //проверка колизий
    bool CheckCollision(Collider *other, sf::Vector2f& direction, float push);

    virtual //обработка коллизий
    void OnCollision(sf::Vector2f direction);

    virtual //обновление активности
    void updateActive(Player* Player);

    void timerUpdate(float time);

    void updateSound(Player* player);

    //обновление
    void update(float time, Player* Player);

    void setKnockback(bool faceRight_, float mas);
};