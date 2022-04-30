#include "Frog.hpp"
#include "World.hpp"
#include "Game.hpp"
#include <iostream>
#include <math.h>


Frog::Frog(const b2Vec2& position, const World& world)
{
    // Create a dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    _body = world.getWorld()->CreateBody(&bodyDef);

    // Next we create a fixture definition using the box. Notice that we set density to 1.
    // The default density is zero. Also, the friction on the shape is set to 0.3.
    b2FixtureDef fixtureDef;
    // create and attach a polygon shape using a fixture definition. First we create a box shape:
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(frog_dimensions.x/2.0,
                        frog_dimensions.y/2.0,
                        b2Vec2(frog_dimensions.x/2.0, frog_dimensions.y/2.0), 0.0);
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = _density;
    fixtureDef.friction = _friction;
    fixtureDef.restitution = _restitution;
    // Using the fixture definition we can now create the fixture. This automatically updates the mass of the body.
    // You can add as many fixtures as you like to a body. Each one contributes to the total mass.
    _body->CreateFixture(&fixtureDef);
    _body->SetFixedRotation(true);

    jumpSound = Mix_LoadWAV("jump.wav");
    if(!jumpSound) {
        std::cout << SDL_GetError() << std::endl;
        return 0;
    }
}

void Frog::impulse() {
    _body->SetLinearVelocity(b2Vec2(0, _speed));
    if(Mix_PlayChannel(-1, jumpSound, 0) == -1) {
        std::cout << SDL_GetError() << std::endl;
        Mix_FreeChunk(jumpSound);
        return 0;
    }
}

SDL_Texture* Frog::initTexture(const std::string& name, SDL_Renderer *renderer) {
    SDL_Surface* tmp_image;
    tmp_image = IMG_Load(name.c_str());
    if(!tmp_image) {
        std::cout << "Error loading texture" << std::endl;
        exit(1);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmp_image);
    SDL_FreeSurface(tmp_image);
    return texture;
}

void Frog::render(SDL_Renderer *renderer) {
    //Render filled quad


    b2Vec2 frog_world_position = getPosition();
    b2Vec2 frog_screen_position = Game::world2screen(frog_world_position);

    SDL_Rect frogRect = { static_cast<int>(frog_screen_position.x),
                          static_cast<int>(frog_screen_position.y-Game::SCALEY*frog_dimensions.y),
                          static_cast<int>(Game::SCALEX*frog_dimensions.x),
                          static_cast<int>(Game::SCALEY*frog_dimensions.y)};
    if(!_texture) {
        _texture = initTexture("frog.png", renderer);
    }
    else {
        SDL_RenderCopyEx(renderer, _texture, NULL, &frogRect, 0.0, NULL, SDL_FLIP_NONE);
    }
    
    //SDL_RenderFillRect( renderer, &frogRect );
}

void Frog::update(float delta) {
    _timeAlive += delta;
}

Frog::~Frog() {
    Mix_FreeChunk(jumpSound);
}
