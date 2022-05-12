#include "Game.hpp"

#include <iomanip>
#include <iostream>
#include <cmath>
#include <memory>
#include <string>
#include <fmt/core.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


// Callback function for button state changed callback
void cb_button_state_changed(uint8_t state, void* user_data) {
    b2Body* body = (b2Body*)user_data;

    if(state == RGB_LED_BUTTON_BUTTON_STATE_PRESSED) {
        printf("State: Pressed\n");
    } else if(state == RGB_LED_BUTTON_BUTTON_STATE_RELEASED) {
        printf("State: Released\n");
    }
}

float remap(float value, float in_min, float in_max, float out_min, float out_max) {
    float result = (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

    if (result > out_max)
        return out_max;
    if (result < out_min)
        return out_min;
    return result;
}

int Game::SCREEN_WIDTH = 640;
int Game::SCREEN_HEIGHT = 480;
float Game::WORLD_WIDTH = 6.4;
float Game::WORLD_HEIGHT = 4.8;
float Game::SCALEX = Game::SCREEN_WIDTH/Game::WORLD_WIDTH;
float Game::SCALEY = Game::SCREEN_HEIGHT/Game::WORLD_HEIGHT;

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return;
    }

    initFrogPos = b2Vec2(WORLD_WIDTH/3.0,WORLD_HEIGHT/2.0);
    initPipePos = b2Vec2(2*WORLD_WIDTH,0.0);

    frog = std::make_unique<Frog>(initFrogPos, world);
    pipe = std::make_unique<Pipe>(initPipePos, world);
}

void Game::addConnection(Connection conn) {
    connection = conn;
}

const b2Vec2& Game::screen2world(const b2Vec2& screen_point) {
  static b2Vec2 world_point;
  world_point.x = screen_point.x/(float)(SCREEN_WIDTH/WORLD_WIDTH);
  world_point.y = SCREEN_HEIGHT/(float)(SCREEN_HEIGHT/WORLD_HEIGHT) - screen_point.y/(float)(SCREEN_HEIGHT/WORLD_HEIGHT);
  return world_point;
}

const b2Vec2& Game::world2screen(const b2Vec2& world_point) {
  static b2Vec2 screen_point;
  screen_point.x = world_point.x*(float)(SCREEN_WIDTH/WORLD_WIDTH);
  screen_point.y = (SCREEN_HEIGHT - world_point.y*(float)(SCREEN_HEIGHT/WORLD_HEIGHT));
  return screen_point;
}

int Game::connect() {
     std::cout << fmt::format("Connection {host}:{port}({uid})",
         fmt::arg("uid", connection.uid), fmt::arg("host", connection.host), fmt::arg("port", connection.port)) << std::endl;
     if (connection) {
         ipcon_create(&ipcon);
         rgb_led_button_create(&rlb, connection.uid.c_str(), &ipcon);

         // Connect to brickd
         if(ipcon_connect(&ipcon, connection.host.c_str(), connection.port) < 0) {
             std::cout << "Could not connect" << std::endl;
             return 1;
         }
         // Don't use device before ipcon is connected
         std::cout << "Connected!" << std::endl;

         // Register button state changed callback to function cb_button_state_changed
         rgb_led_button_register_callback(&rlb,
                                         RGB_LED_BUTTON_CALLBACK_BUTTON_STATE_CHANGED,
                                         (void (*)(void))cb_button_state_changed,
                                         (void *)frog->getBody());
     }
    return 0;
}

int Game::loop() {
    SDL_Window *window = SDL_CreateWindow("Flappy Frog",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Event event;


    bool quit = false;
    double elapsedTime = 1.0/60.0;
    while(!quit) {
        uint32_t startTime = SDL_GetTicks();
        while( SDL_PollEvent( &event ) != 0 )
        {
            if( event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
            else if (event.key.keysym.sym == SDLK_UP || event.type == SDL_FINGERDOWN)
            {
                frog->impulse();
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor( renderer, 120, 120, 230, 0 );
        SDL_RenderClear( renderer );

        b2Vec2 frog_screen_position = world2screen(frog->getPosition());
        std::cout << fmt::format("Body position Y coordinate: {pos}", fmt::arg("pos", frog_screen_position.y)) << std::endl;
        float color = remap(frog_screen_position.y, 400, 0, 0, 255);
        std::cout << fmt::format("Button color G value: {col}", fmt::arg("col", color)) << std::endl;

        //Set button color
        if (connection)
            rgb_led_button_set_color(&rlb, 200, color, 0);

        frog->render(renderer);
        pipe->render(renderer);

        SDL_RenderPresent( renderer );
        uint32_t currTime = SDL_GetTicks();
        elapsedTime = (currTime - startTime) / 1000.0; // Convert to seconds.
        world.update(elapsedTime);
        pipe->update(elapsedTime);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    SDL_Quit();
    return EXIT_SUCCESS;
}


Game::~Game() {
    if (connection) {
        rgb_led_button_destroy(&rlb);
        ipcon_destroy(&ipcon);
    }
}
