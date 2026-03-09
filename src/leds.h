#ifndef LEDS_H
#define LEDS_H

#include <Adafruit_NeoPixel.h>
#include "constants.h"

Adafruit_NeoPixel leds(LED_COUNT, LED_DIN, NEO_GRB + NEO_KHZ800);

struct Color
{
    uint8_t r, g, b;
};

// 40% do brilho — pressed vai amplificar ao máximo
const Color CUE_COLORS[] = {
    {100, 0, 0},  // Cue 1 — Vermelho
    {100, 32, 0}, // Cue 2 — Laranja
    {0, 32, 100}, // Cue 3 — Azul
    {100, 80, 0}, // Cue 4 — Amarelo
    {0, 100, 0},  // Cue 5 — Verde
    {80, 0, 100}, // Cue 6 — Roxo claro
    {0, 80, 100}, // Cue 7 — Azul claro
    {40, 0, 100}  // Cue 8 — Roxo
};

// Array separado — mude as cores dos btns aqui sem afetar os pads
const Color BTN_COLORS[] = {
    {0, 50, 150}, // Btn 1 — Azul FX
    {0, 50, 150}, // Btn 2 — Azul FX
    {0, 50, 150}, // Btn 3 — Azul FX
    {100, 80, 0}, // Btn 4 — Amarelo
    {0, 100, 0},  // Btn 5 — Verde
    {80, 0, 100}, // Btn 6 — Roxo claro
    {0, 80, 100}, // Btn 7 — Azul claro
    {40, 0, 100}  // Btn 8 — Roxo
};

const Color COLOR_IDLE = {20, 20, 100};

// Amplifica qualquer cor ao máximo mantendo o matiz
Color amplifyColor(Color c)
{
    uint8_t maxVal = max(c.r, max(c.g, c.b));
    if (maxVal == 0)
        return c;
    float scale = 255.0f / maxVal;
    return {
        (uint8_t)min(255, (int)(c.r * scale)),
        (uint8_t)min(255, (int)(c.g * scale)),
        (uint8_t)min(255, (int)(c.b * scale))};
}

void setupLeds()
{
    leds.begin();
    leds.setBrightness(50);
    leds.clear();
    leds.show();
}

void setLed(int index, uint8_t r, uint8_t g, uint8_t b)
{
    leds.setPixelColor(index, leds.Color(r, g, b));
    leds.show();
}

void clearLeds()
{
    leds.clear();
    leds.show();
}

void startupAnimation()
{
    uint32_t colors[] = {
        leds.Color(255, 0, 100),
        leds.Color(0, 200, 255),
        leds.Color(255, 150, 0),
        leds.Color(100, 0, 255)};
    for (int c = 0; c < 4; c++)
    {
        for (int i = 0; i < LED_COUNT; i++)
            leds.setPixelColor(i, colors[c]);
        leds.show();
        delay(600);
    }
    for (int i = 0; i < LED_COUNT; i++)
        leds.setPixelColor(i, leds.Color(COLOR_IDLE.r, COLOR_IDLE.g, COLOR_IDLE.b));
    leds.show();
}

#endif