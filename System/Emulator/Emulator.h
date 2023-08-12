#ifndef GAMEBOYPLUS_EMULATOR_H
#define GAMEBOYPLUS_EMULATOR_H

#include "../Core/CPU/CPU.h"
#include "../Core/PPU/PPU.h"

#include <ctime>

class Emulator {
private:
    const int FPS = 60;
    const int CLOCKSPEED = 4194304;

    const float cyclesPerFrame = static_cast<float>(CLOCKSPEED) / static_cast<float>(FPS);

    CPU* cpu;
    PPU* ppu;
    clock_t* timer;

public:
    Emulator();
    ~Emulator();

    void start();
};


#endif //GAMEBOYPLUS_EMULATOR_H
