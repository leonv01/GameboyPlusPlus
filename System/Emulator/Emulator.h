//
// Created by leonv on 31/07/2023.
//

#ifndef GAMEBOYPLUS_EMULATOR_H
#define GAMEBOYPLUS_EMULATOR_H

#include "../Core/CPU.h"
#include "../Core/PPU.h"

#include <iostream>

class Emulator
{
private:
    const uint8_t framerate = 60;
    const uint32_t CLOCK_SPEED = 4194304;
    const uint32_t CYCLES_PER_FRAME = CLOCK_SPEED / framerate;
    int32_t cyclesRemaining{};

    CPU* cpu;
    PPU* ppu;

public:
    Emulator();
    ~Emulator();

    void debug();

    void initEmulator();
    void start();
    void restart();
    void poweroff();

    void saveGame();
    void loadGame();

};


#endif //GAMEBOYPLUS_EMULATOR_H
