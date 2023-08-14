

#include "Emulator/Emulator.h"

int main(){
    Emulator emulator;
    emulator.loadROM("/home/leon/Documents/GameboyPlusPlus/GameROM/MortalKombat.gb");
    emulator.start();
    return 0;

}
