//
// Created by leon on 8/6/23.
//

#ifndef GAMEBOYPLUS_EMULATOR_H
#define GAMEBOYPLUS_EMULATOR_H

#include "../Core/CPU/CPU.h"

class Emulator {
private:
    CPU* cpu;

public:
    Emulator();
    ~Emulator();

    void start();
};


#endif //GAMEBOYPLUS_EMULATOR_H
