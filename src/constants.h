#include <Arduino.h>

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DEBUG true

// ============================================================
// MULTIPLEXERS
// ============================================================
const int MUX_S0 = 7;
const int MUX_S1 = 6;
const int MUX_S2 = 5;
const int MUX_S3 = 4;
const int MUX_L_SIG = 27;
const int MUX_R_SIG = 23;

// Canais MUX L
const int PAD_L_1 = 0;
const int PAD_L_2 = 1;
const int PAD_L_3 = 2;
const int PAD_L_4 = 3;
const int PAD_L_5 = 4;
const int PAD_L_6 = 5;
const int PAD_L_7 = 6;
const int PAD_L_8 = 7;
const int BTN_L_1 = 8;
const int BTN_L_2 = 9;
const int BTN_L_3 = 10;
const int BTN_L_4 = 11;
const int BTN_L_5 = 12;
const int BTN_L_6 = 13;
const int BTN_L_7 = 14;
const int BTN_L_8 = 15;

// Canais MUX R
const int BTN_R_1 = 0;
const int BTN_R_2 = 1;
const int BTN_R_3 = 2;
const int BTN_R_4 = 3;
const int BTN_R_5 = 4;
const int BTN_R_6 = 5;
const int BTN_R_7 = 6;
const int BTN_R_8 = 7;
const int PAD_R_1 = 8;
const int PAD_R_2 = 9;
const int PAD_R_3 = 10;
const int PAD_R_4 = 11;
const int PAD_R_5 = 12;
const int PAD_R_6 = 13;
const int PAD_R_7 = 14;
const int PAD_R_8 = 15;

// ============================================================
// DIRETO NO TEENSY
// ============================================================
const int ROT_L_CLK = 0;
const int ROT_L_DT = 1;
const int ROT_L_BTN = 2;

const int ROT_R_CLK = 9;
const int ROT_R_DT = 10;
const int ROT_R_BTN = 11;

const int LED_DIN = 22;
const int LED_COUNT = 32;

const int POT_L_1 = 24;
const int POT_L_2 = 25;
const int POT_L_3 = 26;

const int POT_R_1 = 39;
const int POT_R_2 = 40;
const int POT_R_3 = 41;

// ============================================================
// MIDI
// ============================================================
const byte MIDI_CH = 1;

const byte PAD_L_NOTE_START = 36;
const byte PAD_R_NOTE_START = 44;

const byte BTN_L_CC_START = 20;
const byte BTN_R_CC_START = 28;

const byte POT_L_CC_START = 1;
const byte POT_R_CC_START = 4;

const byte BTN_L_FX_NOTE_START = 52; // FX L 1-3: notas 52-54
const byte BTN_R_FX_NOTE_START = 55; // FX R 1-3: notas 55-57

const byte ROT_L_CC = 7;
const byte ROT_R_CC = 8;
const byte ROT_L_BTN_CC = 9;
const byte ROT_R_BTN_CC = 10;

#endif