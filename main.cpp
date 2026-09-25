#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include <random>
#include <filesystem>

using namespace std;
using namespace sf;
namespace fs = std::filesystem;


const int winWidth_ = 1920, winHeight_ = 1080;


float cof = 1;
Vector2f winSize = {cof * winWidth_, cof * winHeight_};


void startmenu_definition(Game& game) {
    game.startmenu->start = new Button(750 * 3, 150 * 3, "START");
    game.startmenu->start->getSound("sound/iron_press.ogg");
    game.startmenu->start->setCharacterSize(100 * 3);
    game.startmenu->start->setOriginCenter();
    game.startmenu->start->setPosition(winWidth_ * 3/ 2, winHeight_ * 1);


    game.startmenu->exit = new Button(750 * 3, 150 * 3, "EXIT");
    game.startmenu->exit->getSound("sound/iron_press.ogg");
    game.startmenu->exit->setCharacterSize(100 * 3);
    game.startmenu->exit->setOriginCenter();
    game.startmenu->exit->setPosition(winWidth_ / 2 * 3, winHeight_ * 2 / 3 * 3);

    game.startmenu->startMenuTheme.openFromFile("sound/maintheme.ogg");

    game.startmenu->setBackground("image/start_background.png");
}

void pausemenu_definition(Game& game) {
    game.pausemenu->resume = new Button(750 * 3, 150 * 3, "RESUME");
    game.pausemenu->resume->getSound("sound/iron_press.ogg");
    game.pausemenu->resume->setCharacterSize(100 * 3);
    game.pausemenu->resume->setOriginCenter();
    game.pausemenu->resume->setPosition(winWidth_ * 3/ 2, winHeight_ * 1);
    game.pausemenu->resumepos = {winWidth_ * 3/ 2, winHeight_ * 1};

    game.pausemenu->exit = new Button(750 * 3, 150 * 3, "EXIT");
    game.pausemenu->exit->getSound("sound/iron_press.ogg");
    game.pausemenu->exit->setCharacterSize(100 * 3);
    game.pausemenu->exit->setOriginCenter();
    game.pausemenu->exit->setPosition(winWidth_ / 2 * 3, winHeight_ * 2 / 3 * 3);
    game.pausemenu->exitpos = {winWidth_ / 2 * 3, winHeight_ * 2 / 3 * 3};
}

void finishmenu_definition(Game& game) {
    game.finishmenu->continue_ = new Button(750 * 3, 150 * 3, "CONTINUE");
    game.finishmenu->continue_->getSound("sound/iron_press.ogg");
    game.finishmenu->continue_->setCharacterSize(100 * 3);
    game.finishmenu->continue_->setOriginCenter();
    game.finishmenu->continue_->setPosition(winWidth_ * 3 / 2, winHeight_ * 2);

    game.finishmenu->score = new Button(1000 * 3, 400 * 3, "");
    game.finishmenu->score->setFillRacktengelColor(255, 255, 0);
    game.finishmenu->score->setCharacterSize(100 * 5);
    game.finishmenu->score->setOriginCenter();
    game.finishmenu->score->setPosition(winWidth_ * 3 / 2, winHeight_ * 1);

    game.finishmenu->FinishMenuTheme.openFromFile("sound/maintheme.ogg");

    game.finishmenu->setBackground("image/start_background2.png");
}

int main() {
    RenderWindow window(VideoMode(winSize.x , winSize.y), "sfml_check");

    float FPS = 60;
    mt19937 mt(239);

    window.setFramerateLimit(int(FPS));
    window.setSize(Vector2u(winSize));
    //window.setMouseCursorVisible(false);

    //sf::Image icon;
    //icon.loadFromFile(s + "icon.png"); // File/Image/Pixel
    //window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    Game game(winWidth_ * 3, winHeight_ * 3);

    startmenu_definition(game);
    pausemenu_definition(game);
    finishmenu_definition(game);
    //game.overworld->overworld_definition();
    //game.overworld ;
    //overworld_definition(game);


    Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();

        clock.restart();
        time = time / 800;
        time = min(time, 30.0f);
        //cout << time << '\n';
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear(Color::Black);


        game.update(event, window, time);
        game.draw(window);

        window.display();
    }



        fs::path dirPath = "alive";
        remove_directory(dirPath);
}

/*
    CircleShape c;
    c.setRadius(20);
    c.setFillColor(Color::Magenta);
    c.setOrigin(c.getGlobalBounds().width / 2, c.getGlobalBounds().height / 2);

    Image im2;
    im2.loadFromFile("image/0.png");
    Texture texture2;
    texture2.loadFromImage(im2);
    Sprite sprr;
    sprr.setTexture(texture2);
    sprr.setPosition(0, 0);
    sprr.setOrigin(sprr.getGlobalBounds().width / 2, sprr.getGlobalBounds().height / 2);
    //sprr.setScale(0.5, 0.5);
    sprr.setScale(300 / sprr.getGlobalBounds().width, 300 / sprr.getGlobalBounds().height);
    sprr.setPosition(500, 500);

    Image im;
    im.loadFromFile("image/snail.png");
    Texture texture;
    texture.loadFromImage(im);

    vector<Sprite> sp(800);
    vector<vector<Sprite>> sp2(4, vector<Sprite>(100));

    for (auto& i : sp) {
        i.setTexture(texture);
        i.setPosition(Vector2f(mt() % 20000 - 10000.0, mt() % 20000 - 10000.0));
    }

    for (int i = 0; i < 100; i++) {
        sp2[0][i].setTexture(texture);
        sp2[0][i].setPosition(Vector2f(-10000 + i * 200, -10000));
    }
    for (int i = 0; i < 100; i++) {
        sp2[1][i].setTexture(texture);
        sp2[1][i].setPosition(Vector2f(-10000, -10000 + i * 200));
    }
    for (int i = 0; i < 100; i++) {
        sp2[2][i].setTexture(texture);
        sp2[2][i].setPosition(Vector2f(10000, -10000 + i * 200));
    }
    for (int i = 0; i < 100; i++) {
        sp2[3][i].setTexture(texture);
        sp2[3][i].setPosition(Vector2f(-10000 + i * 200, 10000));
    }








            c.setPosition(game.player->getPosition());
        //window.draw(c);
        game.update(event, window, time);

        window.draw(sprr);
        for (auto& i : sp) {
            window.draw(i);
        }
        for (auto& i : sp2) {
            for (auto& j : i) {
                window.draw(j);
            }
        }

        game.draw(window);
        //cout << game.bat->velocity << "\n\n";

        window.display();
    */