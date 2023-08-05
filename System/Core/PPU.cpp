//
// Created by leon on 8/3/23.
//

#include "PPU.h"

#include <algorithm>
#include <SDL_ttf.h>
#include <fstream>

void PPU::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL failed to initialize" << std::endl;
        return;
    }
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_SetWindowSize(window, EMU_WIDTH, EMU_HEIGHT);
    SDL_SetWindowResizable(window, SDL_TRUE);

    frameBuffer = new uint8_t[HEIGHT * WIDTH * 3];  //RGB
    frameBufferA = new uint8_t[HEIGHT * WIDTH * 4]; //RGBA

    uint16_t tileMap, tileData;

    uint16_t temp = (*vram)[(0xFF40)];
    if (((temp >> 3) & 1) == 1) tileMap = 0x9C00;
    else tileMap = 0x9800;

    if (((temp >> 4) & 1) == 1) tileData = 0x8000;
    else tileData = 0x8800;

    int i, x, y;

}

PPU::PPU(std::vector<uint8_t> *vram) {
    this->vram = std::unique_ptr<std::vector<uint8_t>>(vram);
    this->init();
}

void PPU::draw() {
    for (size_t row = 0; row < HEIGHT; row++) {
        for (size_t column = 0; column < WIDTH; column++) {
        }
    }
}

void PPU::debug(int start, int end) {
    std::cout << "Printing VRAM Content: " << std::endl;
    for (int i = start; i < end; i++) {
        std::cout << static_cast<uint8_t>((*vram)[i]) << std::endl;
    }
}

void PPU::debugView() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Sprite Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          EMU_WIDTH, EMU_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the sprite
        renderTiles();

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void PPU::loadVRAM() {

    /*char *debug = new char[64];

    std::ifstream romFile(debugPath, std::ios::binary);
    if (!romFile) {
        std::cerr << "Error opening file" << std::endl;
    } else {
        romFile.read(debug, 64);
        romFile.close();


        for (size_t i = 0; i < 64; i++) {
            (*vram)[i] = static_cast<uint8_t>(debug[i]);
        }
        this->debug(0, 64);
    }
     **/
    const uint8_t testSprite[16] = {
            0x7C, 0x7C,
            0x00, 0xC6,
            0xC6, 0x00,
            0x00, 0xFE,
            0xC6, 0xC6,
            0x00, 0xC6,
            0xC6, 0x00,
            0x00, 0x00
    };
    for(size_t i = 0; i < sizeof(testSprite); i++) (*vram)[i] = testSprite[i];
}

void PPU::renderTiles() {

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_STREAMING, TILE_SIZE, TILE_SIZE);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);



    tileSet = std::vector<uint8_t>(0xFFF);

    int tileIndex = 0;

    int tileOffset = tileIndex * 16;

    uint8_t tileData[16];
    uint32_t pixels[TILE_SIZE * TILE_SIZE];

    for (size_t i = 0; i < TILE_SIZE; i++) {
        for (size_t j = 0; j < TILE_SIZE; j++) {
            uint8_t pixelColor1 = ((*vram)[i * 2] >> (7 - j)) & 1;
            uint8_t pixelColor2 = ((*vram)[i * 2 + 1] >> (7 - j)) & 1;
            uint8_t pixelColor = (pixelColor1 << 1) | pixelColor2;

            // You can have a color palette and set the appropriate color here based on the pixelColor value
            // For simplicity, we'll set the colors to black and white
            uint32_t color = (pixelColor == 0) ? 0xFFFFFFFF : 0xFF000000;

            pixels[i * TILE_SIZE + j] = color;
        }
    }
    void* pixelData;
    int pitch;
    SDL_LockTexture(texture, nullptr, &pixelData, &pitch);
    memcpy(pixelData, pixels, sizeof(pixels));
    SDL_UnlockTexture(texture);

    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_DestroyTexture(texture);
}

