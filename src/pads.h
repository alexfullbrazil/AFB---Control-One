#ifndef PADS_H
#define PADS_H

#include "constants.h"
#include "leds.h"
#include "mux.h"

const int PAD_L_CHANNELS[] = {PAD_L_1, PAD_L_2, PAD_L_3, PAD_L_4, PAD_L_5, PAD_L_6, PAD_L_7, PAD_L_8};
const int PAD_R_CHANNELS[] = {PAD_R_1, PAD_R_2, PAD_R_3, PAD_R_4, PAD_R_5, PAD_R_6, PAD_R_7, PAD_R_8};

int padLState[8] = {}, padLPState[8] = {};
int padRState[8] = {}, padRPState[8] = {};

bool padLLedExternal[8] = {false, false, false, false, false, false, false, false};
bool padRLedExternal[8] = {false, false, false, false, false, false, false, false};

unsigned long padLDebounce[8] = {}, padRDebounce[8] = {};
const int PAD_DEBOUNCE_MS = 50;

void setupPads() {}

void readPads()
{
    for (int i = 0; i < 8; i++)
    {

        // Lado L
        padLState[i] = readMuxDigital(MUX_L_SIG, PAD_L_CHANNELS[i]);
        if (padLState[i] != padLPState[i] && (millis() - padLDebounce[i]) > PAD_DEBOUNCE_MS)
        {
            padLDebounce[i] = millis();
            if (padLState[i] == LOW)
            {
                usbMIDI.sendNoteOn(PAD_L_NOTE_START + i, 127, MIDI_CH);
                Color pressed = amplifyColor(padLLedExternal[i] ? CUE_COLORS[i] : COLOR_IDLE);
                setLed(8 + i, pressed.r, pressed.g, pressed.b);
                if (DEBUG)
                {
                    Serial.print("PAD_L_");
                    Serial.print(i + 1);
                    Serial.println(" ON");
                }
            }
            else
            {
                usbMIDI.sendNoteOff(PAD_L_NOTE_START + i, 0, MIDI_CH);
                if (padLLedExternal[i])
                {
                    setLed(8 + i, CUE_COLORS[i].r, CUE_COLORS[i].g, CUE_COLORS[i].b);
                }
                else
                {
                    setLed(8 + i, COLOR_IDLE.r, COLOR_IDLE.g, COLOR_IDLE.b);
                }
                if (DEBUG)
                {
                    Serial.print("PAD_L_");
                    Serial.print(i + 1);
                    Serial.println(" OFF");
                }
            }
            padLPState[i] = padLState[i];
        }

        // Lado R
        padRState[i] = readMuxDigital(MUX_R_SIG, PAD_R_CHANNELS[i]);
        if (padRState[i] != padRPState[i] && (millis() - padRDebounce[i]) > PAD_DEBOUNCE_MS)
        {
            padRDebounce[i] = millis();
            if (padRState[i] == LOW)
            {
                usbMIDI.sendNoteOn(PAD_R_NOTE_START + i, 127, MIDI_CH);
                Color pressed = amplifyColor(padRLedExternal[i] ? CUE_COLORS[i] : COLOR_IDLE);
                setLed(24 + i, pressed.r, pressed.g, pressed.b);
                if (DEBUG)
                {
                    Serial.print("PAD_R_");
                    Serial.print(i + 1);
                    Serial.println(" ON");
                }
            }
            else
            {
                usbMIDI.sendNoteOff(PAD_R_NOTE_START + i, 0, MIDI_CH);
                if (padRLedExternal[i])
                {
                    setLed(24 + i, CUE_COLORS[i].r, CUE_COLORS[i].g, CUE_COLORS[i].b);
                }
                else
                {
                    setLed(24 + i, COLOR_IDLE.r, COLOR_IDLE.g, COLOR_IDLE.b);
                }
                if (DEBUG)
                {
                    Serial.print("PAD_R_");
                    Serial.print(i + 1);
                    Serial.println(" OFF");
                }
            }
            padRPState[i] = padRState[i];
        }
    }
}

#endif