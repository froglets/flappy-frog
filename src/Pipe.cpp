#include "Pipe.hpp"
#include "World.hpp"
#include "Game.hpp"
#include <iostream>
#include <math.h>


Pipe::Pipe(const b2Vec2& position, const World& world, SDL_Renderer *renderer, bool roof):
_roof(roof),
_renderer(renderer),
_init_pos(position)
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
    dynamicBox.SetAsBox(pipe_dimensions.x/2.0,
                        pipe_dimensions.y/2.0,
                        b2Vec2(pipe_dimensions.x/2.0, pipe_dimensions.y/2.0), 0.0);
    fixtureDef.shape = &dynamicBox;
    _body->CreateFixture(&fixtureDef);
    _body->SetFixedRotation(true);
    _body->SetLinearVelocity(b2Vec2(-2.25,0.0));

    BodyUserData* myData = new BodyUserData;
    myData->id = 2;

    _body->GetUserData().pointer=(uintptr_t)myData;
    _texture = initTexture("pipe.png");
}

void Pipe::stop() {
    _body->SetLinearVelocity(b2Vec2(0.0,0.0));
}

SDL_Texture* Pipe::initTexture(const std::string& name) {
    SDL_Surface* tmp_image;
    tmp_image = IMG_Load(name.c_str());
    if(!tmp_image) {
        std::cout << "Error loading texture" << std::endl;
        exit(1);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, tmp_image);
    SDL_FreeSurface(tmp_image);
    return texture;
}

void Pipe::update(float delta, float free_pos_x, float rand_y) {
    if (_body->GetPosition().x<-pipe_dimensions.x) {
        _body->SetTransform(b2Vec2(free_pos_x,_init_pos.y+rand_y),0.0);
    }
}

void Pipe::render() {
    //Render filled quad


    b2Vec2 pipe_world_position = getPosition();
    b2Vec2 pipe_screen_position = Game::world2screen(pipe_world_position);
    SDL_Rect pipeRect = { static_cast<int>(pipe_screen_position.x),
                          static_cast<int>(pipe_screen_position.y-Game::SCALEY*pipe_dimensions.y),
                          static_cast<int>(Game::SCALEX*pipe_dimensions.x),
                          static_cast<int>(Game::SCALEY*pipe_dimensions.y)};

    
    SDL_RendererFlip flip = _roof ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(_renderer, _texture, NULL, &pipeRect, 0.0, NULL, flip);
}
