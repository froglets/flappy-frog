#include "World.hpp"
#include "Game.hpp"

World::World() {
    createFloor();
    createRoof();
}


void World::update(float elapsedTime) {
    _world->Step(elapsedTime, _velocityIterations, _positionIterations);
}

void World::createFloor() {
    // Create the ground body
    float floorY = 0.5;
    b2BodyDef floorBodyDef;
    floorBodyDef.position.Set(0,0);
    b2Body* floorBody = _world->CreateBody(&floorBodyDef);
    b2EdgeShape floorBox;
    floorBox.SetTwoSided(b2Vec2(0,floorY), b2Vec2(Game::WORLD_WIDTH,floorY));
    floorBody->CreateFixture(&floorBox, 0.0f);
}

void World::createRoof() {
    // Create the ground body
    b2BodyDef roofBodyDef;
    roofBodyDef.position.Set(0,Game::WORLD_HEIGHT);
    b2Body* roofBody = _world->CreateBody(&roofBodyDef);
    b2EdgeShape roofBox;
    roofBox.SetTwoSided(b2Vec2(0,0), b2Vec2(Game::WORLD_WIDTH,0));
    roofBody->CreateFixture(&roofBox, 0.0f);
}
