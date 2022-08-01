#include "ObstacleManager.hpp"
#include "Game.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ctime>

void ObstacleManager::init(World& world, SDL_Renderer *renderer) {
    _interval = Game::WORLD_WIDTH/2.0;
    float floor = Game::WORLD_HEIGHT/2.0 - Game::WORLD_HEIGHT/2.0;
    float roof = Game::WORLD_HEIGHT/2.0 + Game::WORLD_HEIGHT/4.0;
    _obstacles[0]->floor_pipe = std::make_unique<Pipe>(b2Vec2(2*_interval,floor), world, renderer);
    _obstacles[0]->roof_pipe = std::make_unique<Pipe>(b2Vec2(2*_interval,roof), world, renderer, true);
    _obstacles[1]->floor_pipe = std::make_unique<Pipe>(b2Vec2(3*_interval,floor), world, renderer);
    _obstacles[1]->roof_pipe = std::make_unique<Pipe>(b2Vec2(3*_interval,roof), world, renderer, true);
    _obstacles[2]->floor_pipe = std::make_unique<Pipe>(b2Vec2(4*_interval,floor), world, renderer);
    _obstacles[2]->roof_pipe = std::make_unique<Pipe>(b2Vec2(4*_interval,roof), world, renderer, true);
}

void ObstacleManager::reset() {
    _interval = Game::WORLD_WIDTH/2.0;
    float floor = Game::WORLD_HEIGHT/2.0 - Game::WORLD_HEIGHT/2.0;
    float roof = Game::WORLD_HEIGHT/2.0 + Game::WORLD_HEIGHT/4.0;

    _obstacles[0]->floor_pipe->setPosition(b2Vec2(2*_interval,floor));
    _obstacles[0]->roof_pipe->setPosition(b2Vec2(2*_interval,roof));
    _obstacles[1]->floor_pipe->setPosition(b2Vec2(3*_interval,floor));
    _obstacles[1]->roof_pipe->setPosition(b2Vec2(3*_interval,roof));
    _obstacles[2]->floor_pipe->setPosition(b2Vec2(4*_interval,floor));
    _obstacles[2]->roof_pipe->setPosition(b2Vec2(4*_interval,roof));

    _obstacles[0]->floor_pipe->resetVel();    
    _obstacles[0]->roof_pipe->resetVel();
    _obstacles[1]->floor_pipe->resetVel();
    _obstacles[1]->roof_pipe->resetVel();
    _obstacles[2]->floor_pipe->resetVel();
    _obstacles[2]->roof_pipe->resetVel();
}

float ObstacleManager::getFreePosition() {
    float max_x = 0.0;
    for(const auto& obstacle: _obstacles) {
        max_x = std::max(obstacle->floor_pipe->getPosition().x, max_x);
    }
    return max_x + _interval;
}

void ObstacleManager::update(float elapsedTime) {
    float free_pos = getFreePosition();
    for(const auto& obstacle: _obstacles) {
        float r = static_cast <float>(std::rand())/static_cast<float>(RAND_MAX)-0.5;
        r = r*Game::WORLD_HEIGHT/8.0;
        obstacle->floor_pipe->update(elapsedTime, free_pos, r);
        obstacle->roof_pipe->update(elapsedTime, free_pos, r);
    }
}

void ObstacleManager::render() {
    for(const auto& obstacle: _obstacles) {
        obstacle->floor_pipe->render();
        obstacle->roof_pipe->render();
    }
}

void ObstacleManager::stop() {
    for(const auto& obstacle: _obstacles) {
        obstacle->floor_pipe->stop();
        obstacle->roof_pipe->stop();
    }
}
