#ifndef COFFEEBEAN_CONSTANTS_H
#define COFFEEBEAN_CONSTANTS_H

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;


enum Layer{
    LAYER_ONE = 1, // 0b00000001
    LAYER_TWO = 2, // 0000 0010
    LAYER_THREE = 4, // 0000 0100
    LAYER_FOUR = 8,
    LAYER_FIVE = 16,
    LAYER_SIX = 32,
    LAYER_SEVEN = 64,
    LAYER_EIGHT = 128 //1000 0000

};
const unsigned int NUM_LAYERS = 8;

//TODO(fhomolka): camera zoom and stuff
const float PIXELS_PER_METER = 32;
#endif