#ifndef MIDI_H
#define MIDI_H

#include "constants.h"
#include "leds.h"

bool fxLActive[3] = {false, false, false};
bool fxRActive[3] = {false, false, false};
bool fxBlinkState = false;
unsigned long fxBlinkTime = 0;
const int FX_BLINK_MS = 400;

void updateFxBlink()
{
    if (millis() - fxBlinkTime < FX_BLINK_MS)
        return;
    fxBlinkTime = millis();
    fxBlinkState = !fxBlinkState;
    for (int i = 0; i < 3; i++)
    {
        if (fxLActive[i])
        {
            Color c = fxBlinkState ? amplifyColor(BTN_COLORS[i]) : BTN_COLORS[i];
            setLed(i, c.r, c.g, c.b);
        }
        if (fxRActive[i])
        {
            Color c = fxBlinkState ? amplifyColor(BTN_COLORS[i]) : BTN_COLORS[i];
            setLed(16 + i, c.r, c.g, c.b);
        }
    }
}

void setupMidi() {}

void handleMidiFeedback()
{
    while (usbMIDI.read())
    {
        byte type = usbMIDI.getType();
        // byte channel = usbMIDI.getChannel();
        byte data1 = usbMIDI.getData1();
        byte data2 = usbMIDI.getData2();

        // ── Note On/Off → Pads (cues) ─────────────────────────
        bool isOn = (type == usbMIDI.NoteOn && data2 > 0);
        bool isOff = (type == usbMIDI.NoteOff || (type == usbMIDI.NoteOn && data2 == 0));

        if (isOn || isOff)
        {
            // FX L: notas 52-54 → LEDs 0-2
            if (data1 >= BTN_L_FX_NOTE_START && data1 < BTN_L_FX_NOTE_START + 3)
            {
                int btn = data1 - BTN_L_FX_NOTE_START;
                fxLActive[btn] = isOn;
                if (!isOn)
                    setLed(btn, BTN_COLORS[btn].r, BTN_COLORS[btn].g, BTN_COLORS[btn].b);
            }
            // FX R: notas 55-57 → LEDs 16-18
            if (data1 >= BTN_R_FX_NOTE_START && data1 < BTN_R_FX_NOTE_START + 3)
            {
                int btn = data1 - BTN_R_FX_NOTE_START;
                fxRActive[btn] = isOn;
                if (!isOn)
                    setLed(16 + btn, BTN_COLORS[btn].r, BTN_COLORS[btn].g, BTN_COLORS[btn].b);
            }
            // Deck L: notas 36-43 → LEDs 8-15
            if (data1 >= PAD_L_NOTE_START && data1 < PAD_L_NOTE_START + 8)
            {
                int pad = data1 - PAD_L_NOTE_START;
                if (isOn)
                {
                    padLLedExternal[pad] = true;
                    setLed(8 + pad, CUE_COLORS[pad].r, CUE_COLORS[pad].g, CUE_COLORS[pad].b);
                }
                else
                {
                    padLLedExternal[pad] = false;
                    setLed(8 + pad, COLOR_IDLE.r, COLOR_IDLE.g, COLOR_IDLE.b);
                }
            }
            // Deck R: notas 44-51 → LEDs 24-31
            if (data1 >= PAD_R_NOTE_START && data1 < PAD_R_NOTE_START + 8)
            {
                int pad = data1 - PAD_R_NOTE_START;
                if (isOn)
                {
                    padRLedExternal[pad] = true;
                    setLed(24 + pad, CUE_COLORS[pad].r, CUE_COLORS[pad].g, CUE_COLORS[pad].b);
                }
                else
                {
                    padRLedExternal[pad] = false;
                    setLed(24 + pad, COLOR_IDLE.r, COLOR_IDLE.g, COLOR_IDLE.b);
                }
            }
        }
    }
}

#endif