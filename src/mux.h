#ifndef MUX_H
#define MUX_H

#include "constants.h"

void setupMux()
{
    pinMode(MUX_S0, OUTPUT);
    pinMode(MUX_S1, OUTPUT);
    pinMode(MUX_S2, OUTPUT);
    pinMode(MUX_S3, OUTPUT);
    pinMode(MUX_L_SIG, INPUT_PULLUP);
    pinMode(MUX_R_SIG, INPUT_PULLUP);
}

void selectMuxChannel(int ch)
{
    digitalWrite(MUX_S0, bitRead(ch, 0));
    digitalWrite(MUX_S1, bitRead(ch, 1));
    digitalWrite(MUX_S2, bitRead(ch, 2));
    digitalWrite(MUX_S3, bitRead(ch, 3));
}

int readMuxDigital(int sig, int ch)
{
    selectMuxChannel(ch);
    delayMicroseconds(50);
    return digitalRead(sig);
}

int readMuxAnalog(int sig, int ch)
{
    selectMuxChannel(ch);
    delayMicroseconds(10);
    return analogRead(sig);
}

#endif