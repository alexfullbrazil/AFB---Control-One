#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ResponsiveAnalogRead.h>
#include "constants.h"
#include "leds.h"
#include "mux.h"
#include "pads.h"
#include "btns.h"
#include "pots.h"
#include "rots.h"
#include "midi.h"

void setup()
{
  Serial.begin(115200);
  setupLeds();
  setupMux();
  setupPads();
  setupBtns();
  setupPots();
  setupRots();
}

void loop()
{
  readPads();
  readBtns();
  readPots();
  readRots();
  handleMidiFeedback();
  updateFxBlink();
}
