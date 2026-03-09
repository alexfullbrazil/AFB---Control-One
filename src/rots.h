#ifndef ROTS_H
#define ROTS_H

#include "constants.h"

int rotLCLK = HIGH, rotLPCLK = HIGH, rotLBTN = HIGH, rotLPBTN = HIGH;
int rotRCLK = HIGH, rotRPCLK = HIGH, rotRBTN = HIGH, rotRPBTN = HIGH;

void setupRots()
{
    pinMode(ROT_L_CLK, INPUT_PULLUP);
    pinMode(ROT_L_DT, INPUT_PULLUP);
    pinMode(ROT_L_BTN, INPUT_PULLUP);
    pinMode(ROT_R_CLK, INPUT_PULLUP);
    pinMode(ROT_R_DT, INPUT_PULLUP);
    pinMode(ROT_R_BTN, INPUT_PULLUP);
}

void readRots()
{
    // ROT L
    rotLCLK = digitalRead(ROT_L_CLK);
    if (rotLCLK != rotLPCLK && rotLCLK == LOW)
    {
        if (digitalRead(ROT_L_DT) != rotLCLK)
        {
            usbMIDI.sendControlChange(ROT_L_CC, 65, MIDI_CH);
            if (DEBUG)
            {
                Serial.println("ROT_L: HORARIO");
            }
        }
        else
        {
            usbMIDI.sendControlChange(ROT_L_CC, 63, MIDI_CH);
            if (DEBUG)
            {
                Serial.println("ROT_L: ANTI-HORARIO");
            }
        }
    }
    rotLPCLK = rotLCLK;

    rotLBTN = digitalRead(ROT_L_BTN);
    if (rotLBTN != rotLPBTN)
    {
        if (rotLBTN == LOW)
        {
            usbMIDI.sendControlChange(ROT_L_BTN_CC, 127, MIDI_CH);
            if (DEBUG)
            {
                Serial.println("ROT_L: CLICK");
            }
        }
        else
        {
            usbMIDI.sendControlChange(ROT_L_BTN_CC, 0, MIDI_CH);
        }
        rotLPBTN = rotLBTN;
    }

    // ROT R
    rotRCLK = digitalRead(ROT_R_CLK);
    if (rotRCLK != rotRPCLK && rotRCLK == LOW)
    {
        if (digitalRead(ROT_R_DT) != rotRCLK)
        {
            usbMIDI.sendControlChange(ROT_R_CC, 65, MIDI_CH);
            if (DEBUG)
            {
                Serial.println("ROT_R: HORARIO");
            }
        }
        else
        {
            usbMIDI.sendControlChange(ROT_R_CC, 63, MIDI_CH);
            if (DEBUG)
            {
                Serial.println("ROT_R: ANTI-HORARIO");
            }
        }
    }
    rotRPCLK = rotRCLK;

    rotRBTN = digitalRead(ROT_R_BTN);
    if (rotRBTN != rotRPBTN)
    {
        if (rotRBTN == LOW)
        {
            usbMIDI.sendControlChange(ROT_R_BTN_CC, 127, MIDI_CH);
            if (DEBUG)
            {
                Serial.println("ROT_R: CLICK");
            }
        }
        else
        {
            usbMIDI.sendControlChange(ROT_R_BTN_CC, 0, MIDI_CH);
        }
        rotRPBTN = rotRBTN;
    }
}

#endif