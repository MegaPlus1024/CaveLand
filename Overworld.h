#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Projectile.h"
#include "Collider.h"
#include "Bat.h"
#include "Turtle.h"
#include "Hopper.h"
#include "GI.h"
#include "Platform.h"
#include "Transition.h"
#include "Slash.h"
#include "Level.h"
#include "Finish.h"
#include <filesystem>
#include <cmath>
namespace fs = std::filesystem;

Vector2f roundd(Vector2f ff);

class Overworld {
private:
    SoundBuffer buffer;

    Music fireballSound;

    Image mImage;
    Texture mTexture;
    Sprite mSprite;

    vector<vector<Sprite>> background;

    string *state;
public:
    Music theme;
    GI *gi;
    Vector2f winSize_;

    float fireballcd;
    float fireballtime;

    float slashcd;
    float slashtime;
    float slashaframe;

    Projectile* fireball_;
    vector<Projectile*> fireball;

    Slash* slash;

    bool isSlashing = false, isFireballing = false, isHealing = false;
    bool doSlash = false, doFireball = false, doHealing = false;

    float soulSpeed = 0.01f;
    int soul = 0, soulmax = 120, soulneed = 40, soulh = 40, soulsteel = 10;

    float dsoul = 0.0f;

    float timerSlash = 0.0f, timerFire = 0.0f;

    Player *player;

    vector<Platform*> platform;
    vector<Entity*> enemy;
    vector<Transition*> transition;
    vector<Finish*> finish;
    RectangleShape border;


    Level* level;

    void overworld_definition();

    Overworld();

    ~Overworld();

    Overworld(string* state_);

    void loadLevel(string path);

    void setBackground(string path);

    void ProjectileUpdate(float time);

    void CollisionUpdate(float time);

    void Parallax(Vector2f velocity_);

    void keyboardLogic(float time);

    void roundupdate();

    void update(Event event, RenderWindow &window, View& view, float time);

    void draw(RenderWindow& window);
};
