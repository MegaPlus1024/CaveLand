#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Projectile.h"
#include "Button.h"
#include "Collider.h"
#include "Bat.h"
#include "GI.h"
#include "Platform.h"
#include "Slash.h"
#include "StartMenu.h"
#include "PauseMenu.h"
#include "Overworld.h"
#include "FinishMenu.h"
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;
using namespace sf;

void remove_directory(const fs::path& dirPath);


class Game {
private:
    int bestScore = 0;

    SoundBuffer buffer;

    string *state;

public:
    Vector2f winSize_;

    StartMenu* startmenu;
    PauseMenu* pausemenu;
    FinishMenu* finishmenu;
    Overworld* overworld;

    View view;

    Game(float winWidth, float winHeight);

    //обновление глобал
    void update(Event event, RenderWindow& window, float time);

    //рисовашка
    void draw(RenderWindow& window);
};