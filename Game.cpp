#include "Game.h"

void remove_directory(const fs::path& dirPath) {
    if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
        for (const auto& entry : fs::directory_iterator(dirPath)) {
            if (fs::is_directory(entry)) {
                remove_directory(entry); // Удаление подпапки рекурсивно
            } else {
                fs::remove(entry); // Удаление файла
            }
        }
        fs::remove(dirPath); // Удаление самой папки
        //std::cout << "directory '" << dirPath << "' deleted." << std::endl;
    } else {
        //std::cout << "directory does not exits." << std::endl;
    }
}


Game::Game(float winWidth, float winHeight) {
    fs::path dirPath = "alive";
    remove_directory(dirPath);
    state = new string("START_MENU");
    winSize_ = {winWidth, winHeight};
    overworld = nullptr;

    //overworld = new Overworld(state);
    startmenu = new StartMenu(state, winSize_);
    pausemenu = new PauseMenu(state, winSize_);
    finishmenu = new FinishMenu(state, winSize_);

    //overworld->winSize_ = winSize_;
}


//обновление игры
void Game::update(Event event, RenderWindow& window, float time) {
    if (*state == "START_MENU") { //старт меню
        startmenu->update(event, window, view, winSize_, time);
    }else if (*state == "GAME_OVERWORLD") { //игровой процесс
        overworld->update(event, window, view, time);
    }else if (*state == "PAUSE_MENU") {
        pausemenu->update(event, window, view, winSize_, time);
    }else if (*state == "FINISH") {
        finishmenu->setBackground("image/finish.png");
        finishmenu->update(event, window, view, winSize_, time);
    }else if (*state == "GAMEOVER") {
        //window.clear();
        finishmenu->setBackground("image/gameover.png");
        finishmenu->update(event, window, view, winSize_, time);
    }
    if (*state == "GAME_OVERWORLD" && !overworld) {
        ofstream outdata("game_data/current.txt");
        outdata << 0 << '\n';
        outdata.close();
        overworld = new Overworld(state);
        overworld->winSize_ = winSize_;
        overworld->overworld_definition();
    }else if (*state != "GAME_OVERWORLD" && *state != "PAUSE_MENU") {
        delete overworld;
        overworld = nullptr;
        fs::path dirPath = "alive";
        remove_directory(dirPath);
    }
    //draw(window);
}

//рисовашка
void Game::draw(RenderWindow& window) {
    if (*state == "START_MENU") { //старт меню
        startmenu->draw(window);
    }else if (*state == "GAME_OVERWORLD") { //игровой процесс
        overworld->draw(window);
    }else if (*state == "PAUSE_MENU") {
        overworld->draw(window);
        pausemenu->draw(window);
    }else if (*state == "FINISH" || *state == "GAMEOVER") {
        finishmenu->draw(window);
    }
}