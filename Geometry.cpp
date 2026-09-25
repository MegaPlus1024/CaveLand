#include "Geometry.h"

ostream& operator<<(ostream& os, Vector2f a) {
    os << a.x << ' ' << a.y;
    return os;
}

istream& operator>>(istream& is, Vector2f& v) {
    is >> v.x >> v.y;
    return is;
}

point::point() {

}

point::point(float x_, float y_) : x(x_), y(y_) {

}

point::point(Vector2f v) : x(v.x), y(v.y) {

}

float point::len() {
    return sqrtf(x * x + y * y);
}

int point::len2() {
    return x * x + y * y;
}

point operator-(const point& p1, const point& p2) {
    return {p1.x - p2.x, p1.y - p2.y};
}

point operator+(const point& p1, const point& p2) {
    return {p1.x + p2.x, p1.y + p2.y};
}

point operator*(const point& p1, const float a) {
    return {p1.x * a, p1.y * a};
}

point operator/(const point& p1, const float a) {
    return {p1.x / a, p1.y / a};
}

void operator-=(point& p1, const point& p2) {
    p1 = {p1.x - p2.x, p1.y - p2.y};
}

void operator+=(point& p1, const point& p2) {
    p1 = {p1.x + p2.x, p1.y + p2.y};
}

bool operator==(const point& p1, const point& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

float operator*(const point& p1, const point& p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

float operator%(const point& p1, const point& p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

float ugol(const point& p1, const point& p2) {
    return atan2(p1 % p2, p1 * p2);
}