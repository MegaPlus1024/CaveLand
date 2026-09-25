#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;
using namespace std;

ostream& operator<<(ostream& os, Vector2f a);

istream& operator>>(istream& is, Vector2f& v);

struct point {
    float x, y;

    point();

    point(float x_, float y_);

    point(Vector2f v);

    float len();

    int len2();
};

point operator-(const point& p1, const point& p2);

point operator+(const point& p1, const point& p2);

point operator*(const point& p1, const float a);

point operator/(const point& p1, const float a);

void operator-=(point& p1, const point& p2);

void operator+=(point& p1, const point& p2);

bool operator==(const point& p1, const point& p2);

float operator*(const point& p1, const point& p2);

float operator%(const point& p1, const point& p2);

float ugol(const point& p1, const point& p2);