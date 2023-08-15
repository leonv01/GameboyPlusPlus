#include <iostream>
#include "PPU.h"

PPU::PPU(SDL_Window *window) {
    this->window = window;
    window = SDL_CreateWindow(
            "GameboyPlusPlus",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH,
            HEIGHT,
            SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(
            window,
            0,
            0
    );
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

PPU::~PPU() {
    SDL_DestroyWindow(window);
}

void PPU::updatePPU() {

}

