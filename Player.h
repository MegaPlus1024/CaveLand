#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include "Animation.h"
#include "Collider.h"
using namespace std;
using namespace sf;

class Entity;

class Player {
private:
    bool justJumped;

    int row;
    pair<int, int> col; //startFrame, frameCount
    Animation* animation;

    RectangleShape* body;
    Collider* collider;

    vector<SoundBuffer> buffer;

    Music stepsSound;   //звук шагов
    Music jumpSound;
    Music hurtSound;

    Vector2f* mPosition;
    Vector2f mSize;
    //float speed;

    int HP;
    int maxHP;

    Image mImage;
    Texture mTexture;

public:
    float speed;

    bool faceRight;

    float jumpHeight;
    bool canJump;
    Vector2f velocity;

    Vector2f knockback;
    float knockbacktime = 0.0f, knockbackcd = 300.0f;


    float iframe;
    Vector2f hitVelocity;

    Vector2f spritePos;
    Vector2f spriteSize;
    Sprite mSprite; //сам игрок

    Music healSound;

    Player(Vector2f Position, Vector2f size, float offset, float jumpHeight, int HP, int maxHP, const string image);

    //герой следит за спрайтом
    void sleditForSprite(Sprite& s, float x, float y);

    //рисует героя
    void draw(RenderWindow& window);

    //наведина мышка
    bool navediaMouse(Event& event, Vector2f  pos);

    //дать звук
    void getSound(string failAudio, Music& sound);

    //поменять громкость
    void soundSetVolume(int volume);

    //поменять размеры квадрата кнопки
    void setCharacterSize(float W, float H);
/*
    //Поменять на центр
    void setOriginCenter();*/

    //поменять позицию
    void setPosition(Vector2f position);

    //Поменять на центр
    void setOriginCenter();

    //получить хп
    int getHp();

    //получить хп
    int getMaxHp();

    void increaseHp(int inc);

    //обновление движения
    void updateMove(float time);

    //получить позицию
    Vector2f getPosition();

    //получить позицию
    Vector2f* getPositionLink();

    Vector2f getVelocity(float time);

    //проверка колизий с толчком
    bool CheckCollision(Collider *other, sf::Vector2f& direction, float push);

    //проверка колизий
    bool CheckCollision(Collider *other, sf::Vector2f& direction);

    //обработка коллизий
    void OnCollision(sf::Vector2f direction);

    //обработка коллизий с врагом
    void OnEnemyCollision(float time, sf::Vector2f direction, Entity* enemy);

    //обновление таймеров
    void timerUpdate(float time);

    //обновление анимации
    void updateAnimation(float time);

    //обновление
    void update(float time);

    void setKnockback(bool faceRight_);

    void updateSound();
};