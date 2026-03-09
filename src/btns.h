#ifndef BTNS_H
#define BTNS_H

#include "constants.h"
#include "leds.h"
#include "mux.h"

const int BTN_L_CHANNELS[] = {BTN_L_1, BTN_L_2, BTN_L_3, BTN_L_4, BTN_L_5, BTN_L_6, BTN_L_7, BTN_L_8};
const int BTN_R_CHANNELS[] = {BTN_R_1, BTN_R_2, BTN_R_3, BTN_R_4, BTN_R_5, BTN_R_6, BTN_R_7, BTN_R_8};

int btnLState[8] = {}, btnLPState[8] = {};
int btnRState[8] = {}, btnRPState[8] = {};
unsigned long btnLDebounce[8] = {}, btnRDebounce[8] = {};
const int BTN_DEBOUNCE_MS = 50;

void setupBtns()
{
    for (int i = 0; i < 8; i++)
    {
        setLed(i, BTN_COLORS[i].r, BTN_COLORS[i].g, BTN_COLORS[i].b);
        setLed(16 + i, BTN_COLORS[i].r, BTN_COLORS[i].g, BTN_COLORS[i].b);
    }
}

void readBtns()
{
    for (int i = 0; i < 8; i++)
    {
        // Lado L
        btnLState[i] = readMuxDigital(MUX_L_SIG, BTN_L_CHANNELS[i]);
        if (btnLState[i] != btnLPState[i] && (millis() - btnLDebounce[i]) > BTN_DEBOUNCE_MS)
        {
            btnLDebounce[i] = millis();
            if (btnLState[i] == LOW)
            {
                if (i < 3)
                    usbMIDI.sendNoteOn(BTN_L_FX_NOTE_START + i, 127, MIDI_CH);
                else
                {
                    usbMIDI.sendControlChange(BTN_L_CC_START + i, 127, MIDI_CH);
                    Color c = amplifyColor(BTN_COLORS[i]);
                    setLed(i, c.r, c.g, c.b);
                }
                if (DEBUG)
                {
                    Serial.print("BTN_L_");
                    Serial.print(i + 1);
                    Serial.println(" ON");
                }
            }
            else
            {
                if (i < 3)
                    usbMIDI.sendNoteOff(BTN_L_FX_NOTE_START + i, 0, MIDI_CH);
                else
                {
                    usbMIDI.sendControlChange(BTN_L_CC_START + i, 0, MIDI_CH);
                    setLed(i, BTN_COLORS[i].r, BTN_COLORS[i].g, BTN_COLORS[i].b);
                }
                if (DEBUG)
                {
                    Serial.print("BTN_L_");
                    Serial.print(i + 1);
                    Serial.println(" OFF");
                }
            }
            btnLPState[i] = btnLState[i];
        }

        // Lado R
        btnRState[i] = readMuxDigital(MUX_R_SIG, BTN_R_CHANNELS[i]);
        if (btnRState[i] != btnRPState[i] && (millis() - btnRDebounce[i]) > BTN_DEBOUNCE_MS)
        {
            btnRDebounce[i] = millis();
            if (btnRState[i] == LOW)
            {
                if (i < 3)
                    usbMIDI.sendNoteOn(BTN_R_FX_NOTE_START + i, 127, MIDI_CH);
                else
                {
                    usbMIDI.sendControlChange(BTN_R_CC_START + i, 127, MIDI_CH);
                    Color c = amplifyColor(BTN_COLORS[i]);
                    setLed(16 + i, c.r, c.g, c.b);
                }
                if (DEBUG)
                {
                    Serial.print("BTN_R_");
                    Serial.print(i + 1);
                    Serial.println(" ON");
                }
            }
            else
            {
                if (i < 3)
                    usbMIDI.sendNoteOff(BTN_R_FX_NOTE_START + i, 0, MIDI_CH);
                else
                {
                    usbMIDI.sendControlChange(BTN_R_CC_START + i, 0, MIDI_CH);
                    setLed(16 + i, BTN_COLORS[i].r, BTN_COLORS[i].g, BTN_COLORS[i].b);
                }
                if (DEBUG)
                {
                    Serial.print("BTN_R_");
                    Serial.print(i + 1);
                    Serial.println(" OFF");
                }
            }
            btnRPState[i] = btnRState[i];
        }
    }
}

#endif