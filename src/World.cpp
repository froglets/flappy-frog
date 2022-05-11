#include "World.hpp"
#include "Game.hpp"

World::World() {
    // Create the ground body
    b2BodyDef groundBodyDef;
    b2Vec2 world_position = b2Vec2(Game::WORLD_WIDTH/2.0,-0.5);
    groundBodyDef.position.Set(world_position.x, world_position.y);
    b2Body* groundBody = _world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(Game::WORLD_WIDTH/2.0, 0.5f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Create the top body
    b2BodyDef topBodyDef;
    b2Vec2 worldPos = b2Vec2(Game::WORLD_WIDTH/2.0, 6.0);
    topBodyDef.position.Set(worldPos.x, worldPos.y);
    b2Body* topBody = _world->CreateBody(&topBodyDef);
    b2PolygonShape topBox;
    topBox.SetAsBox(Game::WORLD_WIDTH/2.0, 0.5f);
    topBody->CreateFixture(&topBox, 0.0f);
}


void World::update(float elapsedTime) {
    _world->Step(elapsedTime, _velocityIterations, _positionIterations);
}
