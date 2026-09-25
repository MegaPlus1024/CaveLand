#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collider.h"
#include "Bat.h"
#include "Turtle.h"
#include "Platform.h"
#include "Geometry.h"
#include "Transition.h"
#include "Hopper.h"
#include "Finish.h"
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

class Level {
public:
    string path;

    vector<Platform*> platform;
    vector<Entity*> enemy;
    vector<Finish*> finish;
    vector<Transition*> transition;

    string backgroundpath;
    RectangleShape border;

    Vector2f startPos = {0.0f, 0.0f};

    Level();

    ~Level();

    Level(const string path);
};