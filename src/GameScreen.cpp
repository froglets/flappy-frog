//
//  GameScreen.cpp
//  flappy-frog
//
//  Created by Conan Team on 29/7/22.
//

#include "GameScreen.hpp"

#include "Game.hpp"
#include "Frog.hpp"
#include "Pipe.hpp"
#include "World.hpp"

GameScreen::GameScreen(SDL_Renderer *renderer):
_renderer(renderer)
{
    initFrogPos = b2Vec2(Game::WORLD_WIDTH/3.0,Game::WORLD_HEIGHT/2.0);
    frog = std::make_unique<Frog>(initFrogPos, world, _renderer);
    _obstacles.init(world, _renderer);

    sky = std::make_unique<Layer>(_renderer, "background-sky.png", 100);
    mountains = std::make_unique<Layer>(_renderer, "background-mountains.png", 20);
    ground = std::make_unique<Layer>(_renderer, "background-ground.png", 840);

    _game_text = std::make_unique<Text>(std::string("0"), _renderer, 48, SDL_Color{128, 128, 128, 0}, Game::SCREEN_WIDTH/2.0, Game::SCREEN_HEIGHT/8.0);

}

GameScreen::~GameScreen() {
}

bool GameScreen::handleEvent(const SDL_Event& event) {
    if (event.key.keysym.sym == SDLK_UP || event.type == SDL_FINGERDOWN)
    {
        frog->impulse();
    }
    return true;
}

void GameScreen::render() {
    SDL_SetRenderDrawColor( _renderer, 120, 120, 230, 0 );
    SDL_RenderClear( _renderer );

    sky->render();
    mountains->render();
    frog->render();
    _obstacles.render();
    ground->render();
    _game_text->render();
}

bool GameScreen::update(float elapsedTime) {
    float before = _obstacles.nearestdPipeX(frog->getPosition());
    collision = world.checkFrogCollision();
    if (!collision) {
        _obstacles.update(elapsedTime);
        sky->update(elapsedTime);
        mountains->update(elapsedTime);
        ground->update(elapsedTime);
    }
    else {
        _obstacles.stop();
    }
    world.update(elapsedTime);
    float after = _obstacles.nearestdPipeX(frog->getPosition());
    if (before>0 && after <0) {
        _score++;
        if (_score>_max_score) {
            _max_score = _score;
        }
        _game_text->setText(std::to_string(_score));
    }
    return collision;
}

void GameScreen::resetGame() {
    frog->setPosition(initFrogPos);
    update(1.0/60.0);
    _obstacles.reset();
    _score=0;
    _game_text->setText(std::to_string(_score));
}
