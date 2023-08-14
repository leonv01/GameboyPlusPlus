#ifndef GAMEBOYPLUS_JOYPAD_H
#define GAMEBOYPLUS_JOYPAD_H


#include <cstdint>
#include <memory>

class Joypad {
private:
    /*
     * Button Mapping
     */
    const uint8_t RightA    = 0x01; // Used as Right or A input (0 = Pressed)(Read Only)
    const uint8_t LeftB     = 0x02; // Used as Left or B input (0 = Pressed)(Read Only)
    const uint8_t UpSelect  = 0x04; // Used as Up or Select input (0 = Pressed)(Read Only)
    const uint8_t DownStart = 0x08; // Used as Down or Start input (0 = Pressed)(Read Only)
    const uint8_t Dir       = 0x10; // Used as Direction buttons (0 = Select)
    const uint8_t Action    = 0x20; // Used as Action buttons (0 = Select)

    uint8_t input;
    std::unique_ptr<uint8_t> memoryLocation;
public:
    explicit Joypad(uint8_t* memory);
    ~Joypad() = default;


};


#endif //GAMEBOYPLUS_JOYPAD_H
