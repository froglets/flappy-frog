#include "ScreenManager.hpp"

ScreenManager::ScreenManager(SDL_Renderer *renderer)
{
    gameScreen = std::make_unique<GameScreen>(renderer);
    startScreen = std::make_unique<StartScreen>(renderer);
    endScreen = std::make_unique<EndScreen>(renderer);
}

ScreenManager::~ScreenManager() {
}


void ScreenManager::handleEvent(const SDL_Event& event) {
    if (active_screen=="start") {
        if (startScreen->handleEvent(event)) {
            active_screen = "game";
        }
    }
    else if (active_screen=="game") {
        gameScreen->handleEvent(event);
    }
    else if (active_screen=="end") {
        if (endScreen->handleEvent(event)) {
            active_screen = "start";
        }
    }
}

void ScreenManager::render() {
    if (active_screen=="start") {
        startScreen->render();
    }
    else if (active_screen=="game") {
        gameScreen->render();
    }
    else if (active_screen=="end") {
        endScreen->render();
    }
}

int ScreenManager::update(float elapsedTime, bool endGame) {
    bool ret = false;

    if (active_screen=="start") {
        ret = startScreen->update(elapsedTime, endGame);
    }
    else if (active_screen=="game") {
        ret = gameScreen->update(elapsedTime, endGame);
        if (ret) {
            active_screen = "end";
        }
    }
    else if (active_screen=="end") {
        ret = endScreen->update(elapsedTime, endGame);
    }

    return ret;
}

