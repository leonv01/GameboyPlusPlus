#ifndef GAMEBOYPLUS_EMULATOR_H
#define GAMEBOYPLUS_EMULATOR_H

#include "../Core/CPU/CPU.h"
#include "../Core/PPU/PPU.h"
#include "../Core/Joypad/Joypad.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"

#include <chrono>

class Emulator {
private:
    const int FPS = 60;
    const int CLOCKSPEED = 4194304;

    const float cyclesPerFrame = static_cast<float>(CLOCKSPEED) / static_cast<float>(FPS);

    std::unique_ptr<CPU> cpu;
    std::unique_ptr<PPU> ppu;
    std::unique_ptr<Joypad> joypad;

    SDL_Window* window{};

public:
    Emulator();
    ~Emulator();

    void start();
    void loadROM(std::string path);
};


#endif //GAMEBOYPLUS_EMULATOR_H
