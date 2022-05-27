#include "World.hpp"
#include "Game.hpp"
#include <iostream>

World::World() {
    createFloor();
    createRoof();
}

bool World::checkFrogCollision() {

    bool kill_frog = false;
    for (b2Contact* contact = _world->GetContactList(); contact; contact = contact->GetNext()) {
        if (contact->IsTouching()) {
            b2BodyUserData user_data_a = contact->GetFixtureA()->GetBody()->GetUserData();
            b2BodyUserData user_data_b = contact->GetFixtureB()->GetBody()->GetUserData();
            if (user_data_a.pointer != 0) {
                BodyUserData* wrapper = reinterpret_cast<BodyUserData*>(user_data_a.pointer);
                //std::cout << wrapper->id << std::endl;
                if (wrapper->id==1) {
                    kill_frog = true;
                }
            }
            if (user_data_b.pointer != 0) {
                BodyUserData* wrapper = reinterpret_cast<BodyUserData*>(user_data_b.pointer);
                //std::cout << wrapper->id << std::endl;
                if (wrapper->id==1) {
                    kill_frog = true;
                }
            }
        }
        if (kill_frog) {
            return kill_frog;
        }
    }
    return kill_frog;
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
