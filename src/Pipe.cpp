#include "Pipe.hpp"
#include "World.hpp"
#include "Game.hpp"
#include <iostream>
#include <math.h>



Pipe::Pipe(const b2Vec2& position, const World& world)
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
    dynamicBox.SetAsBox(pipe_dimensions.x,
                        pipe_dimensions.y,
                        b2Vec2(pipe_dimensions.x/2.0, pipe_dimensions.y/2.0), 0.0);
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = _density;
    fixtureDef.friction = _friction;
    fixtureDef.restitution = _restitution;
    // Using the fixture definition we can now create the fixture. This automatically updates the mass of the body.
    // You can add as many fixtures as you like to a body. Each one contributes to the total mass.
    _body->CreateFixture(&fixtureDef);
    _body->SetFixedRotation(true);
}

void Pipe::impulse() {
    _body->SetLinearVelocity(b2Vec2(0, _speed));
}

SDL_Texture* Pipe::initTexture(const std::string& name, SDL_Renderer *renderer) {
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

void Pipe::render(SDL_Renderer *renderer, float color) {
    //Render filled quad


    b2Vec2 pipe_world_position = getPosition();
    std::cout << pipe_world_position.x << "," << pipe_world_position.y << std::endl;
    b2Vec2 pipe_screen_position = Game::world2screen(pipe_world_position);
    SDL_Rect pipeRect = { static_cast<int>(pipe_screen_position.x-Game::SCALEX*pipe_dimensions.x/2.0),
                          static_cast<int>(pipe_screen_position.y-Game::SCALEY*pipe_dimensions.y/2.0),
                          static_cast<int>(Game::SCALEX*pipe_dimensions.x),
                          static_cast<int>(Game::SCALEY*pipe_dimensions.y)};

    if(!_texture) {
        _texture = initTexture("pipe.png", renderer);
    }
    else {
        SDL_RenderCopyEx(renderer, _texture, NULL, &pipeRect, 0.0, NULL, SDL_FLIP_NONE);
    }
    
    //SDL_RenderFillRect( renderer, &pipeRect );
}

void Pipe::update(float delta) {
    _timeAlive += delta;
}
