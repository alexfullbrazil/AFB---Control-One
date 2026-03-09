#ifndef POTS_H
#define POTS_H

#include "constants.h"
#include <ResponsiveAnalogRead.h>

const int POT_L_PINS[] = {POT_L_1, POT_L_2, POT_L_3};
const int POT_R_PINS[] = {POT_R_1, POT_R_2, POT_R_3};

int potLCState[3] = {0}, potLPState[3] = {0}, midiLCState[3] = {0}, midiLPState[3] = {0};
int potRCState[3] = {0}, potRPState[3] = {0}, midiRCState[3] = {0}, midiRPState[3] = {0};

const int TIMEOUT = 300;
const int varThreshold = 25;
const float snapMultiplier = 0.02;
const int potMin = 10;
const int potMax = 1023;

unsigned long PTimeL[3] = {0}, PTimeR[3] = {0};

ResponsiveAnalogRead responsivePotL[3] = {
    ResponsiveAnalogRead(POT_L_1, true, snapMultiplier),
    ResponsiveAnalogRead(POT_L_2, true, snapMultiplier),
    ResponsiveAnalogRead(POT_L_3, true, snapMultiplier)};
ResponsiveAnalogRead responsivePotR[3] = {
    ResponsiveAnalogRead(POT_R_1, true, snapMultiplier),
    ResponsiveAnalogRead(POT_R_2, true, snapMultiplier),
    ResponsiveAnalogRead(POT_R_3, true, snapMultiplier)};

void setupPots()
{
    for (int i = 0; i < 3; i++)
    {
        responsivePotL[i].setAnalogResolution(1023);
        responsivePotR[i].setAnalogResolution(1023);
    }
}

void readPots()
{
    for (int i = 0; i < 3; i++)
    {
        // Lado L
        responsivePotL[i].update(analogRead(POT_L_PINS[i]));
        potLCState[i] = responsivePotL[i].getValue();
        midiLCState[i] = constrain(map(potLCState[i], potMin, potMax, 0, 127), 0, 127);
        if (abs(potLCState[i] - potLPState[i]) > varThreshold)
            PTimeL[i] = millis();
        if (millis() - PTimeL[i] < TIMEOUT && midiLPState[i] != midiLCState[i])
        {
            usbMIDI.sendControlChange(POT_L_CC_START + i, midiLCState[i], MIDI_CH);
            if (DEBUG)
            {
                Serial.print("POT_L_");
                Serial.print(i + 1);
                Serial.print(": ");
                Serial.println(midiLCState[i]);
            }
            potLPState[i] = potLCState[i];
            midiLPState[i] = midiLCState[i];
        }

        // Lado R
        responsivePotR[i].update(analogRead(POT_R_PINS[i]));
        potRCState[i] = responsivePotR[i].getValue();
        midiRCState[i] = constrain(map(potRCState[i], potMin, potMax, 0, 127), 0, 127);
        if (abs(potRCState[i] - potRPState[i]) > varThreshold)
            PTimeR[i] = millis();
        if (millis() - PTimeR[i] < TIMEOUT && midiRPState[i] != midiRCState[i])
        {
            usbMIDI.sendControlChange(POT_R_CC_START + i, midiRCState[i], MIDI_CH);
            if (DEBUG)
            {
                Serial.print("POT_R_");
                Serial.print(i + 1);
                Serial.print(": ");
                Serial.println(midiRCState[i]);
            }
            potRPState[i] = potRCState[i];
            midiRPState[i] = midiRCState[i];
        }
    }
}

#endif