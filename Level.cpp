//
// Created by User on 23.02.2025.
//

#include "Level.h"

Level::Level() {

}

Level::~Level() {
    for (auto i : enemy) {
        delete i;
    }
    for (auto i : finish) {
        delete i;
    }
    for (auto i : transition) {
        delete i;
    }
    for (auto i : platform) {
        delete i;
    }
}

Level::Level(const string path) {
    this->path = path;
    border.setSize({1000.0f, 1000.0f});
    border.setPosition(0, 0);
    border.setOrigin(border.getSize() / 2.0f);
    ifstream indata;
    indata.open("level/" + path + ".txt");
    //freopen(path.c_str(), "r", stdin);
    //cout << path.c_str() << endl;

    while (!indata.eof()) {
        string s;
        indata >> s;
        bool is = true;
        if (s == "*") {
            is = false;
            indata >> s;
        }
        if (s == "bat") {
            Vector2f a, b = {200.0f, 200.0f};
            float f1 = 1.3, f2 = 0.03, f3 = 120;
            int i1 = 7, i2 = i1, i3 = 1, cost = 50;
            Vector2u col = {4, 4};
            string path_ = "bat.png";
            indata >> a;
            if (is) {
                enemy.push_back(new Bat(a, b, f1, f2, i1, i2, i3, path_, col, f3));
                enemy.back()->cost = cost;
            }
            //cout << s << ' ' << a << ' ' << b << ' ' << f1 << ' ' << f2 << ' ' << i1 << ' ' << i2 << ' ' << i3 << ' ' << path_ << endl;
        }else if (s == "platform") {
            Vector2f a, b;
            //float f1, f2;
            //int i1, i2, i3;
            //string path_;
            indata >> a >> b;
            if (is) {
                platform.push_back(new Platform(a, b, "image/stone.png"));
            }
            //cout << a << ' ' << b << endl;
        }else if (s == "background") {
            indata >> backgroundpath;
            //cout << backgroundpath << endl;
        }else if (s == "border_size") {
            Vector2f a;
            indata >> a;
            if (is) {
                border.setSize(a);
                border.setOrigin(border.getSize() / 2.0f);
            }
        }else if (s == "border_position") {
            Vector2f a;
            indata >> a;
            if (is) {
                border.setPosition(a);
            }
        }else if (s == "transition") {
            Vector2f a, b, c;
            string path_;
            indata >> a >> b >> path_ >> c;

            if (is) {
                transition.push_back(new Transition(a, b, path_, c));
            }
        }else if (s == "turtle") {
            Vector2f a, b = {3.0 / 4 * 500.0f, 250.0f};
            float f1 = 0.8, f2 = 120.0f;
            int i1 = 6, i2 = i1, i3 = 1, cost = 40;
            Vector2u col = {6, 1};
            string path_ = "crab.png";
            indata >> a;
            if (is) {
                enemy.push_back(new Turtle(a, b, f1, i1, i2, i3, path_, col, f2));
                enemy.back()->cost = cost;
            }
        }else if (s == "hopper") {
            Vector2f a, b = {3.0 / 4 * 500.0f, 250.0f};
            float f1 = 1.5, f2 = 300;
            Vector2u col = {4, 3};
            int i1 = 15, i2 = i1, i3 = 1, cost = 80;
            string path_ = "slime.png";
            indata >> a;
            if (is) {
                enemy.push_back(new Hopper(a, b, f1, i1, i2, i3, path_, col, f2));
                enemy.back()->cost = cost;
            }
        }else if (s == "player") {
            Vector2f a;
            indata >> a;
            if (is) {
                startPos = a;
            }
        }else if (s == "finish") {
            Vector2f a, b;
            indata >> a >> b;

            if (is) {
                finish.push_back(new Finish(a, b, "finish.png"));
            }
        }
    }
    indata.close();
    indata.open("alive/" + path + ".txt");
    if (!indata.is_open()) {
        ofstream outdata;
        outdata.open("alive/" + path + ".txt");
        for (auto& i : enemy) {
            outdata << "1\n";
        }
        outdata.close();
        indata.close();
    }else {
        int a;
        for (auto& i : enemy) {
            indata >> a;
            if (!a) {
                i->isAlive = false;
            }
        }
        indata.close();
    }
}