//
// Created by leon on 8/3/23.
//

#ifndef GAMEBOYPLUS_PPU_H
#define GAMEBOYPLUS_PPU_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <vector>
#include <memory>

class PPU {
private:
    const int HEIGHT = 144;
    const int WIDTH = 160;

    const int EMU_HEIGHT = 3 * HEIGHT;
    const int EMU_WIDTH = 3 * WIDTH;

    const int TILE_SIZE = 8;

    std::string debugPath = "/home/leon/Documents/GameboyPlusPlus/Debug/TEXT.txt";

    uint8_t* frameBuffer{};
    uint8_t* frameBufferA{};

    SDL_Renderer* renderer{};
    SDL_Window* window{};
    SDL_Texture* texture{};

    std::unique_ptr<std::vector<uint8_t>> vram;
    std::vector<uint8_t> tileSet;

public:
    explicit PPU(std::vector<uint8_t>* vram);
    void init();
    void draw();

    void renderTiles();

    void loadVRAM();

    void debugView();


    void debug(int start, int end);

    void updateTile(uint16_t addr, uint8_t);
};


#endif //GAMEBOYPLUS_PPU_H
