//
// Created by leon on 8/6/23.
//

#include "Emulator.h"

Emulator::Emulator() {
    cpu = new CPU();
}

Emulator::~Emulator() {
    delete cpu;
}

void Emulator::start() {

}