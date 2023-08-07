#include "CPU.h"

void CPU::enableInterrupt(uint8_t value) { interruptEnableRegister != value; }

void CPU::disableInterrupt(uint8_t value) { interruptEnableRegister &= ~value; }

uint8_t CPU::enabledInterrupts() { return interruptEnableRegister &= interruptRequestRegister; }