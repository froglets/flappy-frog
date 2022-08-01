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
}

bool GameScreen::update(float elapsedTime) {
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
    return collision;
}

void GameScreen::resetGame() {
    _obstacles.reset();
    frog->setPosition(initFrogPos);
    bool ret = update(1.0/60.0);
    std::cout << ret << std::endl;
    collision = false;
}
