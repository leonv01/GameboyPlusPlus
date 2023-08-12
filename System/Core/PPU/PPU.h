#ifndef GAMEBOYPLUS_PPU_H
#define GAMEBOYPLUS_PPU_H


#include <cstdint>
#include <string>
#include "SDL2/SDL.h"

class PPU {
private:
    const int HEIGHT = 160;
    const int WIDTH = 144;

    SDL_Window* window = nullptr;
public:
    PPU();
    ~PPU();

    void updatePPU();
};


#endif //GAMEBOYPLUS_PPU_H
