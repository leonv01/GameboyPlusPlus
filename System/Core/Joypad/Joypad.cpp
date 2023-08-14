//
// Created by leon on 8/15/23.
//

#include "Joypad.h"

Joypad::Joypad(uint8_t *memory) {
    memoryLocation = std::unique_ptr<uint8_t>(memory);
}
